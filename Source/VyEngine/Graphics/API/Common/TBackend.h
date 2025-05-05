#pragma once

#include <cstdint>
#include "Graphics/Data/EPixel.h"
#include "Graphics/Data/ERender.h"
#include "Graphics/Driver/Driver.h"

namespace VyEngine::GFX::API
{
    /**
     *  Graphics Backend API Context Wrapper
     */
    template<class Context>
    class TBackend final
    {
    public:
        /// @brief Initializes the backend.
        /// @param isDebug Indicates whether to enable debug mode.
        void Init(bool isDebug);

        /// @brief Notifies the backend that a frame is about to be rendered
        void OnFrameStarted();

        /// @brief Notifies the backend that the current frame is finished
        /// @note This can be used for synchronization purposes, profiling, etc...
        void OnFrameCompleted();

        /// @brief Clears the specified buffers
        /// @param colorBuffer Clears the color buffer if true
        /// @param depthBuffer Clears the depth buffer if true
        /// @param stencilBuffer Clears the stencil buffer if true
        void ClearBuffers(bool colorBuffer, bool depthBuffer, bool stencilBuffer);

        /// @brief Reads pixels from the framebuffer.
        /// @param X The x-coordinate of the lower-left corner.
        /// @param Y The y-coordinate of the lower-left corner.
        /// @param width The width of the pixel rectangle.
        /// @param height The height of the pixel rectangle.
        /// @param format The format of the pixel data.
        /// @param type The data type of the pixel data.
        /// @param data The destination buffer to store pixel data.
        void ReadPixels(
            uint32_t X, uint32_t Y, 
            uint32_t width, uint32_t height, 
            Data::EPixelDataFormat format, Data::EPixelDataType type, 
            void* data
        );

        /// @brief Renders primitives from array data.
        /// @param primitiveMode Specifies the kind of primitives to render.
        /// @param indexCount The number of elements to render.
        void DrawElements(Data::EPrimitiveMode primitiveMode, uint32_t indexCount);
        
        /// @brief Renders multiple instances of a set of elements.
        /// @param primitiveMode Specifies the kind of primitives to render.
        /// @param indexCount The number of elements to render.
        /// @param instances The number of instances to render.
        void DrawElementsInstanced(Data::EPrimitiveMode primitiveMode, uint32_t indexCount, uint32_t instances);
        
        /// @brief Renders primitives from array data without indexing.
        /// @param primitiveMode Specifies the kind of primitives to render.
        /// @param vertexCount The number of vertices to render.
        void DrawArrays(Data::EPrimitiveMode primitiveMode, uint32_t vertexCount);
        
        /// @brief Renders multiple instances of a set of vertices.
        /// @param primitiveMode Specifies the kind of primitives to render.
        /// @param vertexCount The number of vertices to render.
        /// @param instances The number of instances to render.
        void DrawArraysInstanced(Data::EPrimitiveMode primitiveMode, uint32_t vertexCount, uint32_t instances);


        /// @brief Sets the clear color for the color buffer.
        void SetClearColor(float r, float g, float b, float a);

        /// @brief Specifies the rasterization mode.
        /// @param rasterizationMode The desired rasterization mode.
        void SetRasterizationMode(Data::ERasterizationMode rasterizationMode);

        /// @brief Sets the width for rasterized lines.
        /// @param width The width of rasterized lines.
        void SetRasterizationLinesWidth(float width);

        /// @brief Enables or disables a specific rendering capability.
        /// @param capability The rendering capability to modify.
        /// @param value True if enabled, false otherwise.
        void SetCapability(Data::ERenderingCapability capability, bool value);

        /// @brief Retrieves the status of a rendering capability.
        /// @param capability The rendering capability to query.
        /// @return True if enabled, false otherwise.
        bool GetCapability(Data::ERenderingCapability capability);

        /// @brief Sets the stencil test function and reference value.
        /// @param algorithm The comparison function to use.
        /// @param reference The reference value for the stencil test.
        /// @param mask A mask that is ANDed with both the reference value and the stored stencil value.
        void SetStencilAlgorithm(Data::EComparaisonAlgorithm algorithm, int32_t reference, uint32_t mask);

        /// @brief Sets the depth comparison function.
        /// @param algorithm The depth comparison function to use.
        void SetDepthAlgorithm(Data::EComparaisonAlgorithm algorithm);

        /// @brief Controls the writing of individual bits in the stencil planes.
        /// @param mask Specifies a mask to enable and disable writing of individual bits in the stencil planes.
        void SetStencilMask(uint32_t mask);

		/// @brief Sets stencil test actions depending on test outcomes.
		/// @param stencilFail Action to take when the stencil test fails.
		/// @param depthFail Action to take when the stencil test passes, but the depth test fails.
		/// @param bothPass Action to take when both the stencil test and depth test pass.
		void SetStencilOperations(Data::EOperation stencilFail, Data::EOperation depthFail, Data::EOperation bothPass);

        /// @brief Specifies whether front- or back-facing facets can be culled.
        /// @param cullFace Specifies the faces to cull.
        void SetCullFace(Data::ECullFace cullFace);

        /// @brief Enables or disables writing into the depth buffer.
        void SetDepthWriting(bool enable);

        /// @brief Enables or disables writing of frame buffer color components.
        void SetColorWriting(bool enableRed, bool enableGreen, bool enableBlue, bool enableAlpha);

        /// @brief Sets the viewport transformation parameters.
        void SetViewport(uint32_t X, uint32_t Y, uint32_t width, uint32_t height);

        /// @brief Retrieves the name of the graphics vendor.
        /// @return @return A string containing the vendor name.
        std::string GetVendor();

        /// @brief Retrieves the name of the graphics hardware.
        /// @return A string containing the hardware name.
        std::string GetHardware();

        /// @brief Retrieves the version of the graphics API in use.
        /// @return @return A string containing the API version.
        std::string GetVersion();

        /// @brief Retrieves the version of the shading language.
        /// @return A string containing the shading language version.
        std::string GetShadingLanguageVersion();

    private:
        Context m_Context;
    };
}