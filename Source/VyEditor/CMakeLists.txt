# ./Source/VyEditor - Editor Application

set(EDITOR_FILES
    EntryPoint.cpp

    Application.cpp
    Application.hpp

    # Editor.cpp
    # Editor.hpp

    # Context/Context.cpp
    # Context/Context.hpp

    # Layers/ImGuiLayer.cpp
    # Layers/ImGuiLayer.hpp
)

set(APP_NAME VyEngine)

add_executable(${APP_NAME} ${EDITOR_FILES})

target_link_libraries(${APP_NAME} PUBLIC VyEngineLib)

target_include_directories(${APP_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/VyEngine
    ${CMAKE_SOURCE_DIR}
)