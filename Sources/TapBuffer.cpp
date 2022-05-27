#include "TapBuffer.hpp"
#include "String.hpp"

using namespace godot;

TapBuffer::TapBuffer() { }

void TapBuffer::_register_methods()
{
    register_method("_ready",           &TapBuffer::_ready);
    register_method("_physics_process", &TapBuffer::_physics_process);
    register_method("check",            &TapBuffer::check_gdscript);
    register_method("get_depth",        &TapBuffer::get_depth);
    register_method("get_buffer",       &TapBuffer::get_buffer);

    register_property<TapBuffer, int>("depth", &TapBuffer::depth, 10, GODOT_METHOD_RPC_MODE_DISABLED, GODOT_PROPERTY_USAGE_EDITOR);
}

void TapBuffer::_init()
{
    this->input = Input::get_singleton();
}

void TapBuffer::_ready()
{
    this->buffer.resize(this->depth);
}

void TapBuffer::_physics_process(const float delta)
{
    int buttons = TapBufferState_None;

    if (input->is_action_just_pressed("ui_up")) buttons |= TapBufferState_Up;
    else if (input->is_action_just_pressed("ui_down")) buttons |= TapBufferState_Down;

    if (input->is_action_just_pressed("ui_left")) buttons |= TapBufferState_Left;
    else if (input->is_action_just_pressed("ui_right")) buttons |= TapBufferState_Right;

    this->buffer.push_back(buttons);
}

bool TapBuffer::check(TapBufferState state, int _depth) const
{
    CRASH_COND(_depth <= 0);

    if (this->depth < _depth)
    {
        _depth = this->depth;
    }

    for (int i = 0; i < _depth; i++)
    {
        /*Variant value = this->buffer.front();
        Variant::Type type = value.get_type();
        if (type == Variant::NIL) continue;

        CRASH_COND(value.get_type() != Variant::INT);
        if ((int)value == (int)state) return true;*/
    }

    return false;
}

int TapBuffer::get_depth() const
{
    return this->depth;
}

godot::Array TapBuffer::get_buffer() const
{
    return this->buffer;
}

bool TapBuffer::check_gdscript(int state, int depth) const
{
    return this->check((TapBufferState)state, depth);
}
