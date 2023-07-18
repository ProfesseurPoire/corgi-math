#pragma once

#include <corgi/math/vec2.h>
#include <corgi/math/vec3.h>

namespace corgi 
{
	class Transform;

	/*
	 * @brief	Represents a line or line segment. Mainly use for collision
	 *			detection, with Raycast classes
	 *			
	 *			A ray is made of a starting point, a direction vector and a length
	 */
	class Ray
	{
	public:

		Ray() = default;

		/*!
		 * @brief	Builds a new ray by using a and b coordinates as points of the line
		 *			segment AB
		 * 
		 * @param a Coordinates of the first point of the line segment AB
		 * @param b Coordinates of the second point of the line segment AB
		 */
		Ray(const vec3& a, const vec3& b);

		/*!
		 * @brief	Builds a new ray going from @p start to @p direction of 
		 *			@p length
		 */
		Ray(const vec3& start, const vec3& direction, float length);

		vec3 direction;
		vec3 start;
		float length{0.0f};
	};

	// We keep it an aggregate type because it's simpler that way
	struct Ray2D
	{
		vec2 direction;
		vec2 start;
		float length{ 0.0f };
	};
}
