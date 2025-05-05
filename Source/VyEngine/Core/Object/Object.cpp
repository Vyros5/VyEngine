#include "Core/Object/Object.h"

#include <cassert>

namespace VyEngine
{
    Object::Object(Context* context) : 
        m_Context(context)
    {
        assert(m_Context);
    }

    Object::~Object()
    {

    }

    
}