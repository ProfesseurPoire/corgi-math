#pragma once

namespace corgi
{

/*!
 * @brief	Represents a mathematical 2 dimensional vector. Mainly used
 *			for geometric operations
 *
 *			Template parameter can only be of arithmetic type
 */
class vec2
{
public:
    /*!
     *	@brief	Returns a random vector with the given length
     */
    static vec2 random(float length = 1.0f);

    /*
		 * @brief	Make sure parameter u's length is between min and max
		 *			values. If not, returns multiply the current normalized
		 *			vector with either min or max, depending on which is the
		 *			closest
		 */
    static vec2 clamp(const vec2& u, float min, float max);

    /*!
		* @brief	Returns a point located on the [u,v] line segment
		*			This function returns the result of the following equation :
		*			\f$  \vec{u} + (\vec{u}-\vec{v}) times{ValueType} \f$
		*
		* @param u  First point of the line segment [u,v]
		* @param v	Second point of the line segment [u,v]
		* @param t  Parameter used to locate a point on the [u,v] line segment.
		*			Clamped to the [0.0f;1.0f] range
		*/
    static vec2 lerp(const vec2& u, const vec2& v, const float t) noexcept;

    /**
		 * @brief Returns the zero vector 
		 * 
		 * @return vec2 Value is (0.f, 0.f)
		 */
    static vec2 zero();

    /**
		 * @brief Returns the one vector
		 * 
		 * @return vec2 Value is (1.f, 1.f)
		 */
    static vec2 one();

    /**
		 * @brief Returns the left unit vector
		 * 
		 * @return vec2 Value is (-1.f, 0.f)
		 */
    static vec2 left();

    /**
		 * @brief Returns the right unit vector
		 * 
		 * @return vec2 Value is (1.f, 0.f)
		 */
    static vec2 right();

    /**
		 * @brief Returns the up unit vector
		 * 
		 * @return vec2 Value is (0.f, 1.f)
		 */
    static vec2 up();

    /**
		 * @brief Returns the down unit vector
		 * 
		 * @return vec2 Value is (0.f, -1.f)
		 */
    static vec2 down();

    //Constructors

    ~vec2() = default;

    vec2(float x = 0.0F, float y = 0.0f);

    vec2(const vec2& v)     = default;
    vec2(vec2&& v) noexcept = default;

    // Assignment Operators

    bool operator<(const vec2& other) const noexcept;

    vec2& operator=(const vec2& v);
    vec2& operator=(vec2&& v) noexcept;
    vec2& operator+=(const vec2& v) noexcept;
    vec2& operator-=(const vec2& v) noexcept;
    vec2& operator*=(const vec2& v) noexcept;
    vec2& operator*=(float n) noexcept;
    vec2& operator/=(float n) noexcept;

    // Comparison Operators

    bool operator==(const vec2& v) const noexcept;
    bool operator!=(const vec2& v) const noexcept;

    // Arithmetic Operators

    vec2 operator+(const vec2& v) const noexcept;
    vec2 operator-(const vec2& v) const noexcept;
    vec2 operator*(const vec2& v) const noexcept;
    vec2 operator*(float n) const noexcept;
    vec2 operator/(float n) const noexcept;
    vec2 operator-() const noexcept;    // Unary operator

    // Functions

    /*
		 * @brief	Returns the current vector with a length equals to 1.0f
		 *			Returns a zero vector if the vector could not be
		 *			normalized
		 */
    [[nodiscard]] vec2 normalized() const;

    static bool segment_intersect(vec2 a, vec2 b, vec2 c, vec2 d, vec2& intersection);

    /*!
		 * @brief      Returns the dot product of two vectors
		 *
		 * ### Definition
		 *
		 * The dot product of vectors u and v is defined by the following equation :
		 * \f$ u.v = ||\vec{u}||\times||\vec{v}||\cos(\theta) \f$
		 *
		 * But it can also be computed using this equation :
		 * \f$  ((u_x \times v_x) + (u_y \times v_y)) \f$
		 *
		 * ### Properties
		 *
		 * - **Co-linearity** If the the dot product absolute value between the u and v vectors
		 * is equals to the product of their length, that means u and v are collinear
		 * \f$ |\vec{u}.\vec{v}| = v\times u \f$
		 *
		 * - **Orthogonality** Two vectors are orthogonal if their dot product is equal to zero.
		 * - **Angle** We can use the dot product equation to find the angle between u and v
		 * ( This is actually what is done in the "angle" static function )
		 * \f$  \cos(\theta) = \frac{\vec{u}.\vec{v}}{ ||\vec{u}||\times||\vec{v}|| } \f$
		 */
    [[nodiscard]] float dot(const vec2& v) const noexcept;

    /*!
		 * @brief	Returns true if u and v are orthogonal
		 *
		 *			Use the dot product under the hood. If the dot product
		 *			is equals to zero, u and v are orthogonal
		 */
    [[nodiscard]] bool are_orthogonal(const vec2& v) const noexcept;

    /*!
		* @brief	Returns the angle between u and v
		*
		*			The angle is returned in radian, used the dot product
		*			to find the angle. Use the following equation . This method will assume
		*			that both u and v start at the same origin
		*			\f$  \cos(\theta) = \frac{\vec{u}.\vec{v}}{ ||\vec{u}||\times||\vec{v}|| } \f$
		*/
    [[nodiscard]] float angle(const vec2& v) const;

    /*!
		* @brief	Returns true if u and v are collinear
		*/
    [[nodiscard]] bool are_collinear(const vec2& v) const noexcept;

    /*!
		 * @brief   Converts the vector in an array
		 *
		 * @return  Returns a pointer to the first value of the vector
		 */
    float* array() noexcept;

    /*!
		 * @brief   Converts the vector to a C array
		 *
		 * @return  Returns a const pointer to the first vector value
		 */
    [[nodiscard]] const float* array() const noexcept;

    /*!
		* @brief	Returns the length without performing the sqrt operation
		*			Use this function when you only need to know which vector is longer.
		*			By avoiding the sqrt operation, you save up precious CPU cycles
		*/
    [[nodiscard]] float sqrt_length() const noexcept;

    /*!
		 * @brief      Returns the length of the vector
		 * @return float \f$ \sqrt{x^2 + y^2} \f$
		 */
    [[nodiscard]] float length() const noexcept;

    /*!
		* @brief	Normalize the current vector
		*
		*			Reduce the vector's length to 1. Keep it's direction. A warning
		*			though, if the length of the vector is equal to zero, the method will return false
		*			\f$ (u_x / l, u_y / l) \f$
		*/
    void normalize();

    /*!
		 * @brief   Returns a vector "v" orthogonal to "u"
		 *
		 *			This function returns the result of the following equation :
		 *			 \f$ v = (-u_y, u_x) \f$
		 */
    [[nodiscard]] vec2 orthogonal_vector(const vec2& u) const noexcept;

    /*!
		 * @brief Returns a vector "v" orthogonal to "u"
		 * This function returns the result of the following equation :
		 * \f$ v = (-u_y, u_x) \f$
		 */
    [[nodiscard]] vec2 orthogonal_vector() const noexcept;

    [[nodiscard]] float angle() const noexcept;

    /*!
		 * @brief	Returns a random vector of the same length with it's angle in between
		 *			the angle parameter
		 *
		 *			Warning : this might not be the most optimized thing to do since it
		 *			* by length and sometime you don't need that
		 */
    [[nodiscard]] vec2 range(float range_angle) const;

    //[[nodiscard]] vec2 range_angle(ValueType min_angle, Value)

    // Variables

    float x = 0.0f;
    float y = 0.0f;
};
}    // namespace corgi
