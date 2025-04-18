#pragma once

#include "VyLib/vy_core.hpp"
#include "event/events/app_event.hpp"
#include "VyLib/vy_logger.hpp"

namespace VyEngine
{
    struct LayerUpdateMeta
    {
        float mTimeStep;
        float mNowTime;
    };


    class Layer
    {
    public:
        Layer(const std::string& layerName = "Layer") { mLayerName = layerName; };
        virtual ~Layer() {};

        virtual void OnCreate() = 0;
        virtual void OnDestroy() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnRender() = 0;
        virtual void OnProcessInput() = 0;

        inline const std::string& GetName() const { return mLayerName; }

    protected:
        std::string mLayerName;

    };
}