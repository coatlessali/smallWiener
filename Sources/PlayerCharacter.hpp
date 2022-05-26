#pragma once

#include <Godot.hpp>

#include "TapBuffer.hpp"

#include <AnimationPlayer.hpp>
#include <Input.hpp>
#include <KinematicBody2D.hpp>
#include <Particles2D.hpp>
#include <Sprite.hpp>
#include <Vector2.hpp>

enum class PlayerCharacterState
{
    Idle,
    Walking,
    Sprinting,
    Sliding,
    Jumping,
    Falling,
    Wallsliding,
    Walljumping
};

class PlayerCharacter : public godot::KinematicBody2D
{
    GODOT_CLASS(PlayerCharacter, godot::KinematicBody2D);

protected:
    // Engine
    godot::Input*           input             = nullptr;

    // Nodes
    TapBuffer*              tap_buffer        = nullptr;
    godot::AnimationPlayer* animation         = nullptr;
    godot::Particles2D*     trail             = nullptr;
    godot::Sprite*          sprite            = nullptr;

    // Public properties
    float                   gravity           = 167.f;
    float                   jump_speed        = 500.f;

    // Private properties
    float                   acceleration      = 0.3f;
    float                   friction          = 0.3f;
    bool                    input_directional = false;
    bool                    looking_forwards  = true;
    float                   speed             = 360.f;
    PlayerCharacterState    state             = PlayerCharacterState::Idle;
    godot::Vector2          velocity          = godot::Vector2::ZERO;


public:
    PlayerCharacter();
    static void _register_methods();

    void _init();
    void _ready();
    void _process(const float delta);
    void _physics_process(const float delta);

    void update_animation(const float delta);
};
