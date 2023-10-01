cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(edu_gl)

set(CMAKE_CXX_STANDARD 20)


find_package(glfw3 REQUIRED)
add_subdirectory("vendor/Glad")


add_executable(israel israel.cpp
        ShaderLoader.h
        ShaderLoader.cpp)
target_link_libraries(israel
        PUBLIC glfw
        PUBLIC Glad)

function(copy_shaders_to_target_dir target)
    add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "$<TARGET_PROPERTY:${target},SOURCE_DIR>/shaders"
            "$<TARGET_PROPERTY:${target},BINARY_DIR>/shaders"
    )
endfunction()

copy_shaders_to_target_dir(israel)