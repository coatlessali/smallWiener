include(FindPackageHandleStandardArgs)

if(SMALLWIENER_USE_SUBMODULE_GODOTCPP)
    find_library(GODOTCPP_LIBRARY REQUIRED
        NAMES
        libgodot-cpp.windows.debug.64
        libgodot-cpp.windows.release.64

        libgodot-cpp.osx.debug.64
        libgodot-cpp.osx.release.64

        libgodot-cpp.linux.debug.64
        libgodot-cpp.linux.release.64

        PATHS
        ${THIRDPARTY_FOLDER}/godot-cpp/bin/
    )

    find_path(GODOTCPP_INCLUDE_DIR REQUIRED NAMES
        include/core/Godot.hpp
        include/gen/Reference.hpp
        godot-headers/gdnative_api_struct.gen.h
        godot-headers/gdnative/gdnative.h

        PATHS ${THIRDPARTY_FOLDER}/godot-cpp
    )
else() # using system godot-cpp (intended mainly for Linux)
    find_library(GODOTCPP_LIBRARY REQUIRED NAMES godot-cpp)

    find_path(GODOTCPP_INCLUDE_DIR REQUIRED NAMES
        godot/core/Godot.hpp
        godot/gen/Reference.hpp
        gdnative_api_struct.gen.h
        gdnative/gdnative.h
    )
endif()

find_package_handle_standard_args(godot-cpp DEFAULT_MSG GODOTCPP_LIBRARY GODOTCPP_INCLUDE_DIR)

if(NOT GODOTCPP_FOUND)
    set(GODOTCPP_LIBRARIES ${GODOTCPP_LIBRARY})

    if(SMALLWIENER_USE_SUBMODULE_GODOTCPP)
        set(GODOTCPP_INCLUDE_DIRS ${GODOTCPP_INCLUDE_DIR}/include;${GODOTCPP_INCLUDE_DIR}/include/core;${GODOTCPP_INCLUDE_DIR}/include/gen;${GODOTCPP_INCLUDE_DIR}/godot-headers/)
    else()
        set(GODOTCPP_INCLUDE_DIRS ${GODOTCPP_INCLUDE_DIR}/godot;${GODOTCPP_INCLUDE_DIR}/godot/core;${GODOTCPP_INCLUDE_DIR}/godot/gen;${GODOTCPP_INCLUDE_DIR}/gdnative)
    endif()
else()
    message(FATAL_ERROR "Failed to find godot-cpp.")
endif()

mark_as_advanced(GODOTCPP_LIBRARY GODOTCPP_INCLUDE_DIR)
