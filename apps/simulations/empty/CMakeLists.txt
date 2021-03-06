# simulation cmakelists.txt
cmake_minimum_required(VERSION 2.8)

include(${CMAKE_CURRENT_LIST_DIR}/../../../lib/CMakelists.txt) # roxlu cmake
include(${roxlu_base_dir}/apps/external/CMakelists.txt) # External (glfw)
include(${roxlu_addons_dir}/Buttons/CMakelists.txt) # Buttons addon

set(simulation_base ${CMAKE_CURRENT_LIST_DIR}/)
set(simulation_install_dir ${simulation_base}bin/)
set(simulation_include_dir ${simulation_base}src/)
set(CMAKE_INSTALL_PREFIX ${simulation_install_dir})
set(CMAKE_EXE_LINKER_FLAGS ${roxlu_linker_flags})

set(simulation_libs
  ${roxlu_addon_libs}
  ${glfw_libs}
)

get_filename_component(simulation_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

file(GLOB_RECURSE simulation_sources src/*.cpp)
set(compile_sources 
  ${simulation_sources}
  ${glfw_wrapper_sources}
  ${roxlu_sources}
  ${roxlu_addon_sources}
)

include_directories(
  ${glfw_include_dir} 
  ${external_include_dir}
  ${simulation_include_dir}
  ${roxlu_include_dirs}
)

# Executable
add_executable(${simulation_name} ${compile_sources})
target_link_libraries(${simulation_name} ${simulation_libs})

# Installation 
install(TARGETS ${simulation_name} DESTINATION ${simulation_install_dir})

