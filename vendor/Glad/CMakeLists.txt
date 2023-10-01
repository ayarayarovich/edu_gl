cmake_minimum_required(VERSION 3.20)

add_library(Glad STATIC
        "src/gl.c"
        )

target_include_directories(Glad PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
        )
