#include "Core/VyObject/VyObject.h"

#include <cassert>

namespace VyEngine
{
    VyObject::VyObject(Context* context) : m_Context(context)
    {
        assert(m_Context);
    }

    VyObject::~VyObject()
    {
        
    }

    
}