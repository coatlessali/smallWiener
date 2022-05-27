#include "PlayerCharacter.hpp"
#include "Math.hpp"
#include "Vector2.hpp"

#include <cmath>

using namespace std;
using namespace godot;
using namespace godot::Math;

PlayerCharacter::PlayerCharacter() { }

void PlayerCharacter::_register_methods()
{
    register_method("_ready",           &PlayerCharacter::_ready);
    register_method("_process",         &PlayerCharacter::_process);
    register_method("_physics_process", &PlayerCharacter::_physics_process);
    register_method("update_animation", &PlayerCharacter::update_animation);

    register_property<PlayerCharacter, float>("gravity",    &PlayerCharacter::gravity,    167.f);
    register_property<PlayerCharacter, float>("jump_speed", &PlayerCharacter::jump_speed, 500.f);
}

void PlayerCharacter::_init()
{
    this->input = Input::get_singleton();
}

void PlayerCharacter::_ready()
{
    this->animation = this->get_node<AnimationPlayer>("Animation");
    CRASH_COND(this->animation == nullptr);

    this->trail = this->get_node<Particles2D>("Trail");
    CRASH_COND(this->trail == nullptr);

    this->sprite = this->get_node<Sprite>("Sprite");
    CRASH_COND(this->sprite == nullptr);

    this->tap_buffer = this->get_node<TapBuffer>("TapBuffer");
    CRASH_COND(this->tap_buffer == nullptr);
}

void PlayerCharacter::update_animation(const float delta)
{
    this->trail->set_emitting(fabs(this->velocity.x) > 400);

    if (this->state == PlayerCharacterState::Walljumping)
    {
        //looking_forwards = this->velocity.x > 0.f;
    }
    else if (this->input_directional)
    {
        looking_forwards = this->input->is_action_pressed("ui_right") - this->input->is_action_pressed("ui_left") > 0.f; // BUG: the wallslide animation doesn't really respect the direction we're looking at right now
    }

    this->sprite->set_flip_h(!looking_forwards);

    godot::String animation_state("Idle");
    switch (this->state)
    {
    case PlayerCharacterState::Idle:
        break;

    case PlayerCharacterState::Walking:
        animation_state = "Walking";
        break;

    case PlayerCharacterState::Sliding:
        animation_state = "Sliding";
        break;

    case PlayerCharacterState::Jumping:
        animation_state = "Jumping";
        break;

    case PlayerCharacterState::Falling:
        animation_state = "Falling";
        break;

    case PlayerCharacterState::Wallsliding:
        animation_state = "Wallslide";
        break;

    case PlayerCharacterState::Walljumping:
        animation_state = this->velocity.x > 0 ? "WalljumpR" : this->velocity.x < 0 ? "WalljumpL" : "Wallslide";
        break;

    default:
        CRASH_COND(true);
        return;
    }

    this->animation->play(animation_state);
}

void PlayerCharacter::_process(const float delta)
{
    float movement_axis_value = this->input->is_action_pressed("ui_right") - this->input->is_action_pressed("ui_left");
    this->input_directional   = fabs(movement_axis_value) != 0.f;

    this->update_animation(delta);

    if (this->state == PlayerCharacterState::Sliding)
    {
        this->friction = this->input_directional ? 0.01f : 0.035f;
    }
    else
    {
        this->friction = 0.6f;
    }

    switch (this->state)
    {
    case PlayerCharacterState::Jumping:
    case PlayerCharacterState::Falling:
        if (!((movement_axis_value > 0.f && this->velocity.x > 0.f) || (movement_axis_value < 0.f && this->velocity.x < 0.f)))
        {
            if (this->speed == 360.f * 1.5f)
            {
                this->speed = 360.f;
            }
        }

        break;

    case PlayerCharacterState::Sprinting:
        this->speed = 360.f * 1.5f;
        break;

    default:
        this->speed = 360.f;
        break;
    }
}

void PlayerCharacter::_physics_process(const float delta)
{
    this->state       = fabs(this->velocity.x) > 10.f ? PlayerCharacterState::Walking : PlayerCharacterState::Idle;
    this->velocity.y += this->gravity * delta;

    switch (this->state)
    {
    case PlayerCharacterState::Walljumping:
        this->velocity.x = lerp(this->velocity.x, 0, this->friction / 32.f);
        break;

    case PlayerCharacterState::Sliding:
        if (fabs(this->velocity.x) < 30.f)
        {
            this->velocity.x = 0.f;
            this->state      = PlayerCharacterState::Idle;
        }
        else if (this->input->is_action_just_released("ui_down"))
        {
            this->state = this->velocity.x != 0.f ? PlayerCharacterState::Walking : PlayerCharacterState::Idle;
        }

        velocity.x = lerp(velocity.x, 0, friction);
        break;

    default:
        float user_force = this->input->is_action_pressed("ui_right") - this->input->is_action_pressed("ui_left");
        this->velocity.x = user_force != 0.f ? lerp(this->velocity.x, this->speed * user_force, this->acceleration) : lerp(this->velocity.x, 0, this->friction);

        if (fabs(this->velocity.x) <= 20.f)
        {
            this->velocity.x = 0.f;
            this->state      = PlayerCharacterState::Idle;
        }
        else if (velocity.x != 0.f && this->input->is_action_just_pressed("ui_down"))
        {
            this->velocity.x *= 1.25;
            this->state       = PlayerCharacterState::Sliding;
        }
        else if (fabs(this->velocity.x) < 30.f && this->input->is_action_just_pressed("ui_down"))
        {
            // NOTE: this was supposed to transition to crouching
        }
        else if (this->velocity.x != 0.f && this->state != PlayerCharacterState::Sprinting)
        {
            this->state = PlayerCharacterState::Walking;
        }

        if (!this->is_on_floor()) break;

        if (this->input->is_action_pressed("ui_down"))
        {
            if (velocity.x == 0)
            {
                // NOTE: this is using renderer variables for physics functions, DON'T do this (also, uh, what the fuck is this supposed to do? lol)
                this->velocity.x = this->sprite->is_flipped_h() ? 50.f : -50.f;
            }

            this->velocity.x *= 1.25f;
            this->state       = PlayerCharacterState::Sliding;
        }

        if (this->input->is_action_just_pressed("ui_up"))
        {
            this->velocity.y = -this->jump_speed;
            this->state      = PlayerCharacterState::Jumping;
        }

        if ((this->input->is_action_just_pressed("ui_right") && this->tap_buffer->check(TapBufferState_Right, 10)) ||
            (this->input->is_action_just_pressed("ui_left")  && this->tap_buffer->check(TapBufferState_Left, 10)))
        {
            this->state = PlayerCharacterState::Sprinting;
            WARN_PRINT("TAP BUFFER HIT"); // TODO: remove this once the buffer works properly
        }

        break;
    }

    if (!this->is_on_floor())
    {
        // if Input.get_action_strength("ui_left") + Input.get_action_strength("ui_right") != 0:
        if (this->is_on_wall())
        {
            this->state = PlayerCharacterState::Wallsliding;
            if (this->input->is_action_just_pressed("ui_up"))
            {
                this->velocity.x = (this->sprite->is_flipped_h() ? 1.f : -1.f) * (speed) * 1.75f;
                this->velocity.y = -jump_speed * 0.8f;

                this->state      = PlayerCharacterState::Walljumping;
            }
        }
        else
        {
            if (this->velocity.y < 0.f && this->state != PlayerCharacterState::Walljumping)
            {
                this->state = PlayerCharacterState::Jumping;
                if (this->input->is_action_just_released("ui_up"))
                {
                    velocity.y /= 2.f;
                }
            }
            else
            {
                this->state = PlayerCharacterState::Falling;
            }
        }
    }

    this->velocity = this->move_and_slide(this->velocity, Vector2::UP);

    this->update_animation(delta);
}
