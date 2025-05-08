# ./Source/Editor - Editor Application

set(EDITOR_FILES
    EntryPoint.cpp

    Editor/EditorApp.cpp
    Editor/EditorApp.h

    Editor/Editor.cpp
    Editor/Editor.h
)

set(APP_NAME VyEngine)

add_executable(${APP_NAME} ${EDITOR_FILES})

target_link_libraries(${APP_NAME} PUBLIC VyEngineLib)

target_include_directories(${APP_NAME} PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/VyEngine
    ${CMAKE_SOURCE_DIR}
)