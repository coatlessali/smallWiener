#pragma once

#include <Godot.hpp>

#include <Array.hpp>
#include <Input.hpp>
#include <Node.hpp>

enum TapBufferState
{
    TapBufferState_None  =      0,
    TapBufferState_Up    = 1 << 0,
    TapBufferState_Down  = 1 << 1,
    TapBufferState_Left  = 1 << 2,
    TapBufferState_Right = 1 << 3
};

class TapBuffer : public godot::Node
{
    GODOT_CLASS(TapBuffer, godot::Node);

protected:
    // Engine
    godot::Input* input  = nullptr;

    // Public properties
    int           depth  = 10;

    // Private properties
    godot::Array  buffer { };

private:
    bool check_gdscript(int state, int depth) const;

public:
    TapBuffer();
    static void _register_methods();

    void _init();
    void _ready();
    void _physics_process(const float delta);

    bool         check     (TapBufferState state, int depth) const;
    int          get_depth ()                                const;
    godot::Array get_buffer()                                const;
};
