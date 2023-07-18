#pragma once

#include <corgi/math/vec2.h>

namespace corgi
{
class vec3
{
public:
    // Static functions

    // TODO : Maybe make a Triangle class for that?
    /// Triangle is determined by points A B C and the P Point is within
    /// the triangle's plane
    static bool
    point_in_triangle(const vec3& A, const vec3& B, const vec3& C, const vec3& P);

    /*!
			* @brief  Project the point parameter to the axis parameter
			*/
    static vec3 project_on_axis(const vec3& point, const vec3& axis);

    // Find the intersection point between line segments AB and CD
    static bool segment_intersection(
        const vec3& a, const vec3& b, const vec3& c, const vec3& d, vec3& returnvec);

    /*!
		 * @brief	Compute the coefficients of the line ax+by+c=0
		 */
    static vec3 line_coefficients(const vec3& u, const vec3& v);

    // Not exactly sure where this was used :thinking:
    // I think this was mainly used for
    // Perlin noise generation so, maybe not that useful for now?
    // TODO : Create a texture using the whole perlin process and check if this
    // whole mid_point thing works
    //static vec3 mid_point(const vec3& start, const vec3& end, float displacement_value, int occurence)
    //{
    //	vec3 direction = end - start;

    //	// Find the middle point
    //	vec3 mid = start + direction / 2.0f;

    //	// We move the mid point by taking a random value

    //	float val = (displacement_value / occurence) * (((float)(rand() % 1000) / 1000.0f) * 2.0f - 1.0f);

    //	vec3 normal(-direction.y, direction.x, 0.0f);
    //	normal.normalize();
    //	return (mid + normal * val);
    //}

    /**
		 * @brief Returns the zero vector
		 * 
		 * @return vec3 Value is (0.f, 0.f, 0.f)
		 */
    static vec3 zero();

    /**
		 * @brief Returns the 1 vector
		 * 
		 * @return vec3 Value is (1.f, 1.f, 1.f)
		 */
    static vec3 one();

    /**
		 * @brief Returns the left unit vector
		 * 
		 * @return vec3 Value is (-1.f, 0.f, 0.f)
		 */
    static vec3 left();

    /**
		 * @brief Returns the right unit vector
		 * 
		 * @return vec3 Value is (1.f, 0.f, 0.f)
		 */
    static vec3 right();

    /**
		 * @brief Returns the up unit vector
		 * 
		 * @return vec3 Value is (0.f, 1.f, 0.f)
		 */
    static vec3 up();

    /**
     * @brief Returns the down unit vector
     * 
     * @return vec3 Value is (0.f, -1.f, 0.f)
     */
    static vec3 down();

    /**
	 * @brief Returns the forward unit vector
	 * 
	 * @return vec3 Value is (0.f, 0.f, -1.f)
	 */
    static vec3 forward();

    /**
     * @brief Returns the bacward unit vector
     * 
     * @return vec3 Value is (0.f, 0.f, 1.f)
     */
    static vec3 backward();

    //Constructors

    constexpr vec3(float p_x = 0.0F, float p_y = 0.0F, float p_z = 0.0F) noexcept
        : x(p_x)
        , y(p_y)
        , z(p_z)
    {
    }

    // Totally unsafe
    vec3(const float* a)
        : x(a[0])
        , y(a[1])
        , z(a[2])
    {
    }

    vec3(const vec2& v) noexcept
        : x(v.x)
        , y(v.y)
        , z(0.0f)
    {
    }
    vec3(const vec3& v) noexcept
        : x(v.x)
        , y(v.y)
        , z(v.z)
    {
    }
    vec3(vec3&& v) noexcept
        : x(v.x)
        , y(v.y)
        , z(v.z)
    {
    }

    // Comparison Operators

    bool operator<(const vec3& other) const noexcept;

    bool operator==(const vec3& v) const noexcept;
    bool operator!=(const vec3& v) const noexcept;

    bool equal(const vec3& v, float epsilon = 0) const noexcept;

    // Assignment Operators

    vec3& operator=(const vec3& v) noexcept;
    vec3& operator=(vec3&& v) noexcept;
    vec3& operator+=(const vec3& v) noexcept;
    vec3& operator-=(const vec3& v) noexcept;
    vec3& operator*=(const vec3& v) noexcept;
    vec3& operator*=(float n) noexcept;
    vec3& operator/=(float n) noexcept;

    // Arithmetics Operators

    vec3 operator+(const vec3& v) const noexcept;
    vec3 operator-(const vec3& v) const noexcept;
    vec3 operator*(const vec3& v) const noexcept;
    vec3 operator*(float n) const noexcept;
    vec3 operator/(float n) const noexcept;

    vec3 operator-() const noexcept;    // Unary operator

    // Functions

    [[nodiscard]] vec2 xy() const { return vec2(x, y); }

    [[nodiscard]] vec3 normalized() const;

    void normalize() noexcept;

    [[nodiscard]] float sqrt_length() const noexcept;

    [[nodiscard]] float length() const noexcept;

    /*!
		 * @brief  Compute the cross product of vectors \f$ \vec{v} \vec{u} \f$
		 */
    [[nodiscard]] vec3 cross(const vec3& v) const noexcept;

    [[nodiscard]] float dot(const vec3& v) const noexcept;

    // Variables

    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};
}    // namespace corgi
