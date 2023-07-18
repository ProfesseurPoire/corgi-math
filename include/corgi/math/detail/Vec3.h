#pragma once

#include <corgi/math/MathUtils.h>
#include <corgi/math/detail/vec2.h>

namespace corgi {
	namespace detail {

			template <class ValueType>
			class vec3
			{
			public:

				// Static functions

				// TODO : Maybe make a Triangle class for that?
				/// Le triangle est d�termin� par les points A, B, C, le point P 
				/// appartient au plan du triangle
				static bool point_in_triangle(const vec3& A, const vec3& B, const vec3& C, const vec3& P)
				{
					// Le nom de l'algorithm : Barycentric Coordinates
					// L'objectif est en gros de caract�ris� un point dans le triangle � l'aide de 2 vecteurs
					// u et v. P = u*(C-A) + v*(B-A)
					// Le but est de d�termin� la valeur de u et de v en fonction du point P. si u et v > 0 et
					//u+v < 1, alors on se trouve dans le triangle
					vec3 u = B - A;
					vec3 v = C - A;
					vec3 w = P - A;

					// On fait le produit vectoriel 
					vec3 vCrossW = v.cross(w);
					vec3 vCrossU = v.cross(u);

					// On teste le signe de r
					if (vCrossW.dot(vCrossU) < 0)
						return false;

					vec3 uCrossW = u.cross(w);
					vec3 uCrossV = u.cross(v);

					if (uCrossW.dot(uCrossV) < 0)
						return false;

					float denom = uCrossV.length();
					float r = vCrossW.length() / denom;
					float t = uCrossW.length() / denom;

					return (r + t <= 1);
				}

				/*!
					* @brief  Project the point parameter to the axis parameter
					*/
				static constexpr vec3 project_on_axis(const vec3& point, const vec3& axis)
				{
					return axis.normalized() * point.dot(axis);
				}

				// Find the intersection point between line segments AB and CD
				static bool segment_intersection(const vec3& a, const vec3& b, const vec3& c, const vec3& d, vec3& returnvec)
				{
					// Dans un premier temps, on v�rifie que les vecteurs u et v de ab et cd ne sont pas colin�aire

					vec3 u = b - a;
					vec3 v = d - c;

					float determinant = u.x * v.y - v.x * u.y;

					// using an epsilon value
					if (determinant >= -0.01 && determinant <= -0.01)
						return false;

					// Si le d�terminant n'est pas �gal � 0, alors on cherche l'�quation des 2 droites AB et CD
					vec3 line1 = line_coefficients(a, b);
					vec3 line2 = line_coefficients(c, d);

					float xx = line1.y * line2.z - line2.y * line1.z;
					float yy = line2.x * line1.z - line1.x * line2.z;
					float ww = line1.x * line2.y - line2.x * line1.y;

					returnvec = vec3(xx / ww, yy / ww, 0.0f);

					float coefa = ((returnvec - a).length()) / u.length();
					float coefb = ((returnvec - c).length()) / v.length();

					if (coefa >= 0 && coefa <= 1)
						if (coefb >= 0 && coefb <= 1)
							return true;
					return false;
				}


				/*!
					* @brief	Compute the coefficients of the line ax+by+c=0
					*/
				static vec3 line_coefficients(const vec3& u, const vec3& v)
				{
					return vec3(v.y - u.y,
						-(v.x - u.x),
						-(u.x * v.y) + (v.x * u.y));
				}

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


			// Static variables

				static const vec3 zero;
				static const vec3 one;
				static const vec3 left;
				static const vec3 right;
				static const vec3 up;
				static const vec3 down;
				static const vec3 forward;
				static const vec3 backward;

				//Constructors

				
				vec3() = default;

				//  TODO : Real talk, would a move constructor be faster on the vector3 thingie?

				explicit constexpr vec3(ValueType x, ValueType y = 0, ValueType z = 0) noexcept
					: x(x), y(y), z(z) {};

				// Totally unsafe 
				vec3(const float* a) : x(a[0]), y(a[1]), z(a[2]) {}

				constexpr vec3(const vec2<ValueType>& v)noexcept : x(v.x), y(v.y), z(0.0f){}
				constexpr vec3(const vec3& v) noexcept : x(v.x), y(v.y), z(v.z) {}
				constexpr vec3(vec3&& v) noexcept : x(v.x), y(v.y), z(v.z) {}

			// Comparison Operators

				bool operator<(const vec3& other)const noexcept
				{
					return sqrt_length() < other.sqrt_length();
				}
				
				constexpr bool operator==(const vec3& v)const noexcept
				{
					return equal(v);
				}

				constexpr bool operator!=(const vec3& v)const noexcept
				{
					return !operator==(v);
				}
				
				constexpr bool equal(const vec3& v, ValueType epsilon= 0) const noexcept
				{
					return
						x >= v.x - epsilon && x <= v.x + epsilon &&
						y >= v.y - epsilon && y <= v.y + epsilon &&
						z >= v.z - epsilon && z <= v.z + epsilon;
				}

			// Assignment Operators

				constexpr vec3& operator=(const vec3& v) noexcept
				{
					x = v.x;
					y = v.y;
					z = v.z;
					return *this;
				}

				constexpr vec3& operator=(vec3&& v) noexcept
				{
					x = v.x;
					y = v.y;
					z = v.z;
					return *this;
				}

				constexpr vec3& operator+=(const vec3& v) noexcept
				{
					x += v.x;
					y += v.y;
					z += v.z;
					return  *this;
				}

				constexpr vec3& operator-=(const vec3& v) noexcept
				{
					x -= v.x;
					y -= v.y;
					z -= v.z;
					return *this;
				}

				constexpr vec3& operator*=(const vec3& v) noexcept
				{
					x *= v.x;
					y *= v.y;
					z *= v.z;
					return *this;
				}

				constexpr vec3& operator*=(const ValueType n) noexcept
				{
					x *= n;
					y *= n;
					z *= n;
					return *this;
				}

				constexpr vec3& operator/=(const ValueType n) noexcept
				{
					x /= n;
					y /= n;
					z /= n;
					return *this;
				}

			// Arithmetics Operators

				constexpr vec3 operator+(const vec3& v)const noexcept
				{
					return vec3(x + v.x, y + v.y, z+v.z);
				}

				constexpr vec3 operator-(const vec3& v)const noexcept
				{
					return vec3(x - v.x, y - v.y, z-v.z);
				}

				constexpr vec3 operator*(const vec3& v)const noexcept
				{
					return vec3(x * v.x, y * v.y, z* v.z);
				}

				constexpr vec3 operator*(const ValueType n) const noexcept
				{
					return vec3(x * n, y * n, z*n);
				}

				constexpr vec3 operator/(const ValueType n) const noexcept
				{
					return vec3(x / n, y / n, z/n);
				}

				constexpr vec3 operator-()const noexcept  // Unary operator
				{
					return vec3(-x, -y, -z);
				}

			// Functions

				
				
				// Returns a vec2 using the vec3's x and y value
				[[nodiscard]] vec2<ValueType> xy()const{return vec2<ValueType>(x, y);}

				[[nodiscard]] vec3 normalized()const
				{
					float l = length();

					if (l == 0)
						return vec3();

					return vec3(x / l, y / l, z/l);

					// the length thing actually goes slightly faster than
					// the inverse sqrt tricks ... wth?
					//return *this * math::inverse_sqrt(dot(*this));
				}

				void normalize() noexcept
				{
					*this *= math::inverse_sqrt(dot(*this));
				}

				[[nodiscard]] constexpr ValueType sqrt_length()const noexcept
				{
					return((x * x) + (y * y) + (z * z));
				}

				[[nodiscard]] ValueType length()const noexcept
				{
					return math::sqrtf(sqrt_length());
				}

				/*!
					* @brief  Compute the cross product of vectors $\f \vec{v} \vec{u} $\f
					*/
				[[nodiscard]] constexpr vec3 cross(const vec3& v)const noexcept
				{
					return vec3
					(
						(y * v.z) - (z * v.y),
						(z * v.x) - (x * v.z),
						(x * v.y) - (y * v.x)
					);
				}

				[[nodiscard]] constexpr ValueType dot(const vec3& v) const noexcept
				{
					return (x * v.x) + (y * v.y) + (z * v.z);
				}

				// Variables

				ValueType x = ValueType();
				ValueType y = ValueType();
				ValueType z = ValueType();
			};


			template<class ValueType> const vec3<ValueType> vec3<ValueType>::zero(+0, +0, +0);
			template<class ValueType> const vec3<ValueType> vec3<ValueType>::one(+1, +1, +1);
			template<class ValueType> const vec3<ValueType> vec3<ValueType>::left(-1, +0, +0);
			template<class ValueType> const vec3<ValueType> vec3<ValueType>::right(+1, +0, +0);
			template<class ValueType> const vec3<ValueType> vec3<ValueType>::up(+0, +1, +0);
			template<class ValueType> const vec3<ValueType> vec3<ValueType>::down(+0, -1, +0);
			template<class ValueType> const vec3<ValueType> vec3<ValueType>::forward( +0, +0, +1);
			template<class ValueType> const vec3<ValueType> vec3<ValueType>::backward(+0, +0, -1);
		}
	}
