#include <corgi/math/MathUtils.h>
#include <corgi/math/Random.h>
#include <corgi/math/vec2.h>

using namespace corgi;

// TODO :	I should check which is faster
//			Taking 2 random values and normalizing
//			Or getting 1 random value and using cos/sin/tan
vec2 vec2::random(const float length)
{
    const float angle = random::range(-math::pi, math::pi);
    return vec2(math::cos(angle) * length, math::sin(angle) * length);
}

vec2 vec2::clamp(const vec2& u, float min, float max)
{
    if(u.length() < min)
        return u.normalized() * min;

    if(u.length() > max)
        return u.normalized() * max;

    return u;
}

vec2::vec2(float p_x, float p_y)
    : x(p_x)
    , y(p_y) {};

bool vec2::operator<(const vec2& other) const noexcept
{
    return sqrt_length() < other.sqrt_length();
}

vec2& vec2::operator=(const vec2& v)
{
    x = v.x;
    y = v.y;
    return *this;
}

vec2& vec2::operator=(vec2&& v) noexcept
{
    x = v.x;
    y = v.y;
    return *this;
}

vec2& vec2::operator+=(const vec2& v) noexcept
{
    x += v.x;
    y += v.y;
    return *this;
}

vec2& vec2::operator-=(const vec2& v) noexcept
{
    x -= v.x;
    y -= v.y;
    return *this;
}

vec2& vec2::operator*=(const vec2& v) noexcept
{
    x *= v.x;
    y *= v.y;
    return *this;
}

vec2& vec2::operator*=(const float n) noexcept
{
    x *= n;
    y *= n;
    return *this;
}

vec2& vec2::operator/=(const float n) noexcept
{
    x /= n;
    y /= n;
    return *this;
}

bool vec2::operator==(const vec2& v) const noexcept
{
    return (x == v.x && y == v.y);
}

bool vec2::operator!=(const vec2& v) const noexcept
{
    return !operator==(v);
}

vec2 vec2::operator+(const vec2& v) const noexcept
{
    return vec2(x + v.x, y + v.y);
}

vec2 vec2::operator-(const vec2& v) const noexcept
{
    return vec2(x - v.x, y - v.y);
}

vec2 vec2::operator*(const vec2& v) const noexcept
{
    return vec2(x * v.x, y * v.y);
}

vec2 vec2::operator*(const float n) const noexcept
{
    return vec2(x * n, y * n);
}

vec2 vec2::operator/(const float n) const noexcept
{
    return vec2(x / n, y / n);
}

vec2 vec2::operator-() const noexcept    // Unary operator
{
    return vec2(-x, -y);
}

[[nodiscard]] vec2 vec2::normalized() const
{
    float l = length();
    if(l == 0)
        return vec2();

    return vec2(x / l, y / l);
    //return (*this * math::inverse_sqrt(dot(*this))); Not precise enough
}

vec2 vec2::lerp(const vec2& u, const vec2& v, const float t) noexcept
{
    return u + ((v - u) * t);
}

bool vec2::segment_intersect(vec2 a, vec2 b, vec2 c, vec2 d, vec2& intersection)
{
    // First we need to make sure that AB and CD aren't collinear
    vec2 ab = b - a;
    vec2 cd = d - c;

    // if the dot product equals 0, it means a and b are parallel
    // In that case, no collision can ever happen

    const auto determinant = (ab.x * cd.y) - (ab.y * cd.x);

    if(determinant == 0.0f)
        return false;

    // We get the vector's equation
    vec2 cc = c - a;

    auto t = (cc.x * cd.y - cc.y * cd.x) / determinant;

    if(t < 0 || t > 1)
        return false;    // The segments doesn't intersect

    auto u = (cc.x * ab.y - cc.y * ab.x) / determinant;

    if(u < 0 || u > 1)
        return false;    // The segments doesn't intersect

    intersection = a + ab * t;
    return true;
}

float vec2::dot(const vec2& v) const noexcept
{
    return x * v.x + y * v.y;
}

bool vec2::are_orthogonal(const vec2& v) const noexcept
{
    return dot(v) == 0;
}

float vec2::angle(const vec2& v) const
{
    return math::acosf(this->dot(v) / (this->length() * v.length()));
}

bool vec2::are_collinear(const vec2& v) const noexcept
{
    return (x * v.y - v.x * y == 0.0f);
}

float* vec2::array() noexcept
{
    return &x;
}

const float* vec2::array() const noexcept
{
    return &x;
}

float vec2::sqrt_length() const noexcept
{
    return (y * y) + (x * x);
}

void vec2::normalize()
{
    float l = length();
    if(l == 0.0f)
    {
        x = 0.0f;
        y = 0.0f;
        return;
    }

    x = x / l;
    y = y / l;

    //*this *= math::inverse_sqrt(dot(*this));
}

float vec2::length() const noexcept
{
    return math::sqrtf(sqrt_length());
}

vec2 vec2::orthogonal_vector(const vec2& u) const noexcept
{
    return vec2(-u.y, u.x);
}

vec2 vec2::orthogonal_vector() const noexcept
{
    return vec2(-y, x).normalized();
}

float vec2::angle() const noexcept
{
    vec2  normal = normalized();
    float angle  = math::asin(normal.y);

    if(normal.x < 0 && normal.y > 0.0f)
        angle = math::atan(1.0f) * 4.0f - angle;

    if(normal.x < 0 && normal.y < 0.0f)
        angle = -(math::atan(1.0f) * 4.0f) - angle;

    return angle;
}

vec2 vec2::range(float range_angle) const
{
    float current_angle = angle();
    current_angle += random::range(-range_angle, range_angle);

    float a = math::sin(current_angle) * length();
    return vec2(math::cos(current_angle), a);
}

vec2 vec2::zero()
{
    return vec2(0.f, 0.f);
}

vec2 vec2::one()
{
    return vec2(1.f, 1.f);
}

vec2 vec2::left()
{
    return vec2(-1.f, 0.f);
}

vec2 vec2::right()
{
    return vec2(1.f, 0.f);
}

vec2 vec2::up()
{
    return vec2(0.0f, 1.0f);
}

vec2 vec2::down()
{
    return vec2(0.0f, -1.0f);
}
