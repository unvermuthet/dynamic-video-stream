#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>

void initialize(ModuleInitializationLevel p_level) {
	switch (p_level) {
		case MODULE_INITIALIZATION_LEVEL_SCENE: {
		} break;
	}
}

void uninitialize(ModuleInitializationLevel p_level) {
	switch (p_level) {
		case MODULE_INITIALIZATION_LEVEL_SCENE: {
		} break;
	}
}

extern "C" {
// Initialization
GDExtensionBool GDE_EXPORT texture_size_changed_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize);
	init_obj.register_terminator(uninitialize);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
	return init_obj.init();
}
}
