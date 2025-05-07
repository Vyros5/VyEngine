# ./Source/VyEngine - Static Library

set(VY_GRAPHICS_FILES

    # Driver
    Graphics/Driver/Driver.cpp
    Graphics/Driver/Driver.h

    # Core
    Graphics/Core/Backend.h
    Graphics/Core/Buffer.h
    Graphics/Core/IndexBuffer.h
    Graphics/Core/VertexBuffer.h
    Graphics/Core/VertexArray.h
    Graphics/Core/ShaderProgram.h
    Graphics/Core/ShaderStage.h

    # Base Templates
    Graphics/API/Common/TBackend.h
    Graphics/API/Common/TBuffer.h
    Graphics/API/Common/TIndexBuffer.h
    Graphics/API/Common/TVertexBuffer.h
    Graphics/API/Common/TVertexArray.h
    Graphics/API/Common/TShaderStage.h
    Graphics/API/Common/TShaderProgram.h

    # OpenGL
    Graphics/API/OpenGL/GLBackend.cpp
    Graphics/API/OpenGL/GLBackend.hpp
    Graphics/API/OpenGL/GLBuffer.cpp
    Graphics/API/OpenGL/GLBuffer.hpp
    Graphics/API/OpenGL/GLEnumType.hpp
    Graphics/API/OpenGL/GLIndexBuffer.cpp
    Graphics/API/OpenGL/GLIndexBuffer.hpp
    Graphics/API/OpenGL/GLVertexBuffer.cpp
    Graphics/API/OpenGL/GLVertexBuffer.hpp
    Graphics/API/OpenGL/GLShaderStage.cpp
    Graphics/API/OpenGL/GLShaderStage.hpp
    Graphics/API/OpenGL/GLShaderProgram.cpp
    Graphics/API/OpenGL/GLShaderProgram.hpp
    Graphics/API/OpenGL/GLVertexArray.cpp
    Graphics/API/OpenGL/GLVertexArray.hpp

    # Structs
    Graphics/Data/ShaderResults.h
    Graphics/Data/UniformInfo.h
    Graphics/Data/VertexAttrib.h

    # Enums
    Graphics/Data/EData.h
    Graphics/Data/EPixel.h
    Graphics/Data/EModel.h
    Graphics/Data/EBuffer.h
    Graphics/Data/ERender.h
    Graphics/Data/EShader.h
)

set(VY_RENDER_FILES
    Render/Device/Device.cpp
    Render/Device/Device.h
    Render/Device/DeviceConfig.h

)


set(VY_WINDOW_FILES
    Window/Window.cpp
    Window/Window.h

    Window/Input/InputDef.h
    Window/Input/IInputEventCallbacks.h

    Window/Data/ECursor.h
    Window/Data/EInput.h
    Window/Data/WindowData.h

    Window/Config/WindowConfig.h
)


set(VY_APP_FILES
    Engine/Engine.cpp
    Engine/Engine.h

    App/App.cpp
    App/App.h
    App/MainLoop.cpp

    Engine/Configuration/Startup.cpp
    Engine/Configuration/Startup.h
    Engine/Configuration/SubSystem.h
)


set(ENGINE_FILES

    Core/Base.h

    defines.h
    
    Core/Context.cpp
    Core/Context.h
    
    Core/Object/Object.cpp
    Core/Object/Object.h

    ${VY_APP_FILES}
    ${VY_GRAPHICS_FILES}
    ${VY_RENDER_FILES}
    ${VY_WINDOW_FILES}

    Event/Event.h
    Event/Event.inl

    Utils/EnumMapper.hpp

    Support/Logger/Logger.cpp
    Support/Logger/Logger.h
    Support/Logger/LogDef.h
)

set(LIBRARY_NAME VyEngineLib)
add_library(${LIBRARY_NAME} STATIC ${ENGINE_FILES})

set(ENGINE_INCLUDE_DIRS
    ${glfw_SOURCE_DIR}/include
    ${spdlog_SOURCE_DIR}/include
    ${assimp_SOURCE_DIR}/include
    ${glm_SOURCE_DIR}

    ${VENDOR_DIR}/stb
    ${VENDOR_DIR}/imgui
    ${VENDOR_DIR}/tinyxml2
    ${VENDOR_DIR}/glad/include
)

target_include_directories(${LIBRARY_NAME}
    PUBLIC
    ${CMAKE_SOURCE_DIR}         # ./Source/
    ${CMAKE_CURRENT_SOURCE_DIR} # ./Source/VyEngine/
    ${ENGINE_INCLUDE_DIRS}
)

target_precompile_headers(${LIBRARY_NAME} PRIVATE EnginePCH.h)

set(VENDOR_LIBS
    glfw
    glad
    spdlog
    imgui
    assimp
)

target_link_libraries(${LIBRARY_NAME} PUBLIC ${VENDOR_LIBS})

if(MSVC)
    message(STATUS "[Compile Options: MSVC]")
    target_compile_options(${LIBRARY_NAME} PUBLIC
        /utf-8  # 
        /W4     # 
        /MP     # multithreaded build
        /WX     # warnings as errors
        /ZI     # program database for edit and continue
        /wd4244 # conversion from 'a' to 'T', possible loss of data
        /wd4267 # conversion from 'size_t' to 'int', possible loss of data
        /wd4245 # conversion from 'int' to 'const size_t', signed/unsigned mismatch
        /wd4100 # unreferenced formal parameter
        /wd4458 # declaration of 'var' hides class member
        /wd4101 # 'var': unreferenced local variable
        /wd4388 # 'token' : signed/unsigned mismatch
        /wd4018 # '>': signed/unsigned mismatch
        /D_DISABLE_CONSTEXPR_MUTEX_CONSTRUCTOR
    )
else()
    message(STATUS "[Compile Options: Other]")
    target_compile_options(${LIBRARY_NAME} PUBLIC 
        -Wall 
        -Wextra 
        -Wpedantic
    )
endif()