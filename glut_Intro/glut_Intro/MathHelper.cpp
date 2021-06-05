#include "MathHelper.h"

namespace MathHelper
{
	float convertToRad(const float& degree)
	{
		return degree * (PI/180.0);
	}

	double convertToRad(const double& degree)
	{
		return degree * (PI/180.0);
	}
}
