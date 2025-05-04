#include "Support/Assert.h"

#include <cassert>

void VyEngine::Support::Assertion::Assert(bool condition, const std::string& message)
{
    assert(condition && message.c_str());
}