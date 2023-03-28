#include "Havoc/Utils/PlatformUtils.h"

#include <GLFW/glfw3.h>

namespace Havoc
{
	float Time::GetTime()
	{
		return glfwGetTime();
	}
}