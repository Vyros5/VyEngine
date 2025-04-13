# VyEngine\runtime\VyLib\CMakeLists.txt

add_library(VyLib)

set(VYLIB_SOURCES
    vy_file.cpp

    logger/vy_logger.cpp
    logger/vy_platform.cpp
)

set(VYLIB_HEADERS
    vy_file.hpp

    logger/vy_logger.hpp
    logger/vy_platform.hpp
    logger/vy_log_data.hpp
    logger/vy_log_settings.hpp
)

target_sources(VyLib
    PRIVATE
        ${VYLIB_SOURCES}
)

target_include_directories(VyLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/logger
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_compile_definitions(VyLib PRIVATE CXX_STANDARD 17)