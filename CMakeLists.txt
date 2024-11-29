cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

set(CMAKE_SYSTEM_VERSION 10.0 CACHE STRING "" FORCE)

project(proxy C CXX)

################################################################################
# Set target arch type if empty. Visual studio solution generator provides it.
################################################################################
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "x86")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86"))
    message(FATAL_ERROR "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Global configuration types
################################################################################
set(CMAKE_CONFIGURATION_TYPES
    "debug"
    "release"
    CACHE STRING "" FORCE
)

################################################################################
# Global compiler options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_C_FLAGS "")
    set(CMAKE_C_FLAGS_DEBUG "")
    set(CMAKE_C_FLAGS_RELEASE "")
    set(CMAKE_CXX_FLAGS "")
    set(CMAKE_CXX_FLAGS_DEBUG "")
    set(CMAKE_CXX_FLAGS_RELEASE "")
endif()

################################################################################
# Global linker options
################################################################################
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

################################################################################
# Nuget packages function stub.
################################################################################
function(use_package TARGET PACKAGE VERSION)
    message(WARNING "No implementation of use_package. Create yours. "
                    "Package \"${PACKAGE}\" with version \"${VERSION}\" "
                    "for target \"${TARGET}\" is ignored!")
endfunction()

################################################################################
# Common utils
################################################################################
include(cmake/utils.cmake)

################################################################################
# Additional Global Settings(add specific info there)
################################################################################
include(cmake/GlobalSettingsInclude.cmake OPTIONAL)

################################################################################
# Use solution folders feature
################################################################################
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

################################################################################
# Sub-projects
################################################################################



























set(PROJECT_NAME proxy)

################################################################################
# Source groups
################################################################################
set(Headers
    "include/addresses.h"
    "include/bitbuf.h"
    "include/bytes.h"
    "include/common.h"
    "include/hooks.h"
    "include/interfaces.h"
    "include/interfaces/client_state.h"
    "include/interfaces/cvar.h"
    "include/interfaces/engine.h"
    "include/interfaces/game_console.h"
    "include/messages.h"
    "include/modules.h"
    "include/patches.h"
    "include/proxy.h"
    "include/util.h"
    "include/versions.h"
    "lib/google/protobuf/compiler/code_generator.h"
    "lib/google/protobuf/compiler/command_line_interface.h"
    "lib/google/protobuf/compiler/cpp/cpp_generator.h"
    "lib/google/protobuf/compiler/importer.h"
    "lib/google/protobuf/compiler/java/java_generator.h"
    "lib/google/protobuf/compiler/parser.h"
    "lib/google/protobuf/compiler/plugin.h"
    "lib/google/protobuf/compiler/python/python_generator.h"
    "lib/google/protobuf/descriptor.h"
    "lib/google/protobuf/descriptor.pb.h"
    "lib/google/protobuf/descriptor_database.h"
    "lib/google/protobuf/dynamic_message.h"
    "lib/google/protobuf/extension_set.h"
    "lib/google/protobuf/generated_enum_reflection.h"
    "lib/google/protobuf/generated_message_reflection.h"
    "lib/google/protobuf/generated_message_util.h"
    "lib/google/protobuf/io/coded_stream.h"
    "lib/google/protobuf/io/gzip_stream.h"
    "lib/google/protobuf/io/printer.h"
    "lib/google/protobuf/io/tokenizer.h"
    "lib/google/protobuf/io/zero_copy_stream.h"
    "lib/google/protobuf/io/zero_copy_stream_impl.h"
    "lib/google/protobuf/io/zero_copy_stream_impl_lite.h"
    "lib/google/protobuf/message.h"
    "lib/google/protobuf/message_lite.h"
    "lib/google/protobuf/reflection_ops.h"
    "lib/google/protobuf/repeated_field.h"
    "lib/google/protobuf/service.h"
    "lib/google/protobuf/stubs/atomicops.h"
    "lib/google/protobuf/stubs/atomicops_internals_x86_msvc.h"
    "lib/google/protobuf/stubs/common.h"
    "lib/google/protobuf/stubs/once.h"
    "lib/google/protobuf/stubs/platform_macros.h"
    "lib/google/protobuf/stubs/template_util.h"
    "lib/google/protobuf/stubs/type_traits.h"
    "lib/google/protobuf/text_format.h"
    "lib/google/protobuf/unknown_field_set.h"
    "lib/google/protobuf/wire_format.h"
    "lib/google/protobuf/wire_format_lite.h"
    "lib/google/protobuf/wire_format_lite_inl.h"
    "lib/netmessages/netmessages.pb.h"
)
source_group("Headers" FILES ${Headers})

set(Sources
    "lib/netmessages/netmessages.pb.cc"
    "lib/safetyhook/safetyhook.cpp"
    "lib/zydis/Zydis.c"
    "main.cpp"
    "src/hooks.cpp"
    "src/messages.cpp"
    "src/patches.cpp"
    "src/plugin.cpp"
    "src/proxy.cpp"
)
source_group("Sources" FILES ${Sources})

set(ALL_FILES
    ${Headers}
    ${Sources}
)

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} SHARED ${ALL_FILES})

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE clientversionchanger)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VS_GLOBAL_KEYWORD "Win32Proj"
)
################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    TARGET_NAME_RELEASE "${PROJECT_NAME}"
)
################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES
    INTERPROCEDURAL_OPTIMIZATION_RELEASE "TRUE"
)
################################################################################
# MSVC runtime library
################################################################################
get_property(MSVC_RUNTIME_LIBRARY_DEFAULT TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY)
string(CONCAT "MSVC_RUNTIME_LIBRARY_STR"
    MultiThreadedDLL
)
set_target_properties(${PROJECT_NAME} PROPERTIES MSVC_RUNTIME_LIBRARY ${MSVC_RUNTIME_LIBRARY_STR})

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:release>:"
        "GOOGLE_PROTOBUF_NO_RTTI;"
        "_HAS_EXCEPTIONS=0"
    ">"
    "WIN32;"
    "NDEBUG;"
    "_CONSOLE;"
    "UNICODE;"
    "_UNICODE"
)

################################################################################
# Compile and link options
################################################################################
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:debug>:
            /Od;
            /sdl;
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        >
        $<$<CONFIG:release>:
            /GL;
            /O1;
            /Ob2;
            /Oi;
            /sdl-;
            /arch:SSE2;
            /Gy-;
            /fp:except-;
            /Zp8;
            /GR-
        >
        /permissive-;
        /MP;
        /std:c++latest;
        /W3;
        ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
        /GS-
    )
    target_link_options(${PROJECT_NAME} PRIVATE
        $<$<CONFIG:debug>:
            /DEBUG;
            /INCREMENTAL:NO
        >
        $<$<CONFIG:release>:
            /MANIFEST:NO;
            /SAFESEH:NO;
            /OPT:REF;
            /LTCG;
            /OPT:ICF;
            /NOIMPLIB;
            /NOEXP;
            /EMITTOOLVERSIONINFO:NO;
            /EMITPOGOPHASEINFO;
            /MERGE:.pdata=.text;
            /MERGE:.rdata=.text
        >
        /SUBSYSTEM:CONSOLE
    )
endif()

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "$<$<CONFIG:release>:"
        "$(CoreLibraryDependencies)"
    ">"
)

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/lib")
target_link_libraries(${PROJECT_NAME} PUBLIC "${ADDITIONAL_LIBRARY_DEPENDENCIES}")