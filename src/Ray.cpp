#include <corgi/math/Ray.h>

namespace corgi
{
	Ray::Ray(const vec3& a, const vec3& b)
	{
		direction = (b - a).normalized();
		direction.normalize();
		start = a;
		length = (b - a).length();
	}

	Ray::Ray(const vec3& start, const vec3& direction, float length)
		: direction(direction), start(start), length(length)
	{}
}
