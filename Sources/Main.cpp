#include <Godot.hpp>

#include "PlayerCharacter.hpp"
#include "TapBuffer.hpp"

/*
// NOTE: this is code that'll be useful once gdextension will be properly implemented in Godot.

void smallWiener_init(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<PlayerCharacter>();
}

void smallWiener_uninit(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) return;
}


extern "C" GDN_EXPORT GDNativeBool smallWiener_startup(const GDNativeInterface* _interface, const GDNativeExtensionClassLibraryPtr library, GDNativeInitialization* initialization)
{
    godot::GDExtensionBinding::InitObject init_object(_interface, library, initialization);

    init_object.register_initializer(smallWiener_init);
	init_object.register_terminator(smallWiener_uninit);
	init_object.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

    return init_object.init();
}
*/

extern "C"
{

GDN_EXPORT void gdnative_init(godot_gdnative_init_options *o)
{
	godot::Godot::gdnative_init(o);
}

GDN_EXPORT void gdnative_terminate(godot_gdnative_terminate_options *o)
{
	godot::Godot::gdnative_terminate(o);
}

GDN_EXPORT void nativescript_init(void* handle)
{
	godot::Godot::nativescript_init(handle);

	godot::register_class<PlayerCharacter>();
    godot::register_class<TapBuffer>();
}

}
