# VyEngine\runtime\CMakeLists.txt

add_library(Event)

set(VY_EVENT_SOURCES
    event_manager.cpp
)

set(VY_EVENT_HEADERS
    event_manager.hpp
    event_handler.hpp
    event.hpp
)

set(VY_EVENTS
    events/app_event.hpp
    events/key_event.hpp
)

target_sources(Event
    PRIVATE
        ${VY_EVENT_SOURCES}
    PUBLIC
        ${VY_EVENT_HEADERS}
        ${VY_EVENTS}
)

target_include_directories(Event 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/events
        ${CMAKE_CURRENT_SOURCE_DIR}
)

message(STATUS "\n[Event: Linked Libraries]\n")