#pragma once
#include "Math.h"
namespace GatesEngine
{
	namespace Math
	{
		struct Transform
		{
			Vector3 position;
			Vector3 rotation;
			Vector3 scale;

			Transform() :position({}), rotation({}), scale({}) {}
		};
	}
}