#pragma once

#include <sstream>
#include <string>

#include <fmt/format.h>

#include "VyLib/vy_core.hpp"
#include "VyLib/vy_crc32.hpp"

// https://denyskryvytskyi.github.io/event-system

namespace VyEngine
{
    class Event
    {
    public:

        virtual ~Event() = default;
        virtual uint32_t GetEventType() const = 0;
        virtual std::string ToString() const { return std::to_string(GetEventType()); };

        bool isHandled { false };
    };

    #define EVENT_TYPE(event_type)             \
        static uint32_t GetStaticEventType()   \
        {                                      \
            return CRC32(event_type);          \
        }                                      \
        uint32_t GetEventType() const override \
        {                                      \
            return GetStaticEventType();       \
        }                                      \

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}