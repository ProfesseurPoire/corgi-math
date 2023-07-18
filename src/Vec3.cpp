#include <corgi/math/MathUtils.h>
#include <corgi/math/vec3.h>

using namespace corgi;

bool vec3::point_in_triangle(const vec3& A, const vec3& B, const vec3& C, const vec3& P)
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
    if(vCrossW.dot(vCrossU) < 0)
        return false;

    vec3 uCrossW = u.cross(w);
    vec3 uCrossV = u.cross(v);

    if(uCrossW.dot(uCrossV) < 0)
        return false;

    float denom = uCrossV.length();
    float r     = vCrossW.length() / denom;
    float t     = uCrossW.length() / denom;

    return (r + t <= 1);
}

vec3 vec3::project_on_axis(const vec3& point, const vec3& axis)
{
    return axis.normalized() * point.dot(axis);
}

bool segment_intersection(
    const vec3& a, const vec3& b, const vec3& c, const vec3& d, vec3& returnvec)
{
    // Dans un premier temps, on v�rifie que les vecteurs u et v de ab et cd ne sont pas colin�aire

    vec3 u = b - a;
    vec3 v = d - c;

    float determinant = u.x * v.y - v.x * u.y;

    // using an epsilon value
    if(determinant >= -0.01 && determinant <= -0.01)
        return false;

    // Si le d�terminant n'est pas �gal � 0, alors on cherche l'�quation des 2 droites AB et CD
    vec3 line1 = vec3::line_coefficients(a, b);
    vec3 line2 = vec3::line_coefficients(c, d);

    float xx = line1.y * line2.z - line2.y * line1.z;
    float yy = line2.x * line1.z - line1.x * line2.z;
    float ww = line1.x * line2.y - line2.x * line1.y;

    returnvec = vec3(xx / ww, yy / ww, 0.0f);

    float coefa = ((returnvec - a).length()) / u.length();
    float coefb = ((returnvec - c).length()) / v.length();

    if(coefa >= 0 && coefa <= 1)
        if(coefb >= 0 && coefb <= 1)
            return true;
    return false;
}

vec3 vec3::line_coefficients(const vec3& u, const vec3& v)
{
    return vec3(v.y - u.y, -(v.x - u.x), -(u.x * v.y) + (v.x * u.y));
}

bool vec3::operator<(const vec3& other) const noexcept
{
    return sqrt_length() < other.sqrt_length();
}

bool vec3::operator==(const vec3& v) const noexcept
{
    return equal(v);
}

bool vec3::operator!=(const vec3& v) const noexcept
{
    return !operator==(v);
}

bool vec3::equal(const vec3& v, float epsilon) const noexcept
{
    return x >= v.x - epsilon && x <= v.x + epsilon && y >= v.y - epsilon &&
           y <= v.y + epsilon && z >= v.z - epsilon && z <= v.z + epsilon;
}

vec3& vec3::operator=(const vec3& v) noexcept
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

vec3& vec3::operator=(vec3&& v) noexcept
{
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}

vec3& vec3::operator+=(const vec3& v) noexcept
{
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

vec3& vec3::operator-=(const vec3& v) noexcept
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

vec3& vec3::operator*=(const vec3& v) noexcept
{
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

vec3& vec3::operator*=(const float n) noexcept
{
    x *= n;
    y *= n;
    z *= n;
    return *this;
}

vec3& vec3::operator/=(const float n) noexcept
{
    x /= n;
    y /= n;
    z /= n;
    return *this;
}

vec3 vec3::operator+(const vec3& v) const noexcept
{
    return vec3(x + v.x, y + v.y, z + v.z);
}

vec3 vec3::operator-(const vec3& v) const noexcept
{
    return vec3(x - v.x, y - v.y, z - v.z);
}

vec3 vec3::operator*(const vec3& v) const noexcept
{
    return vec3(x * v.x, y * v.y, z * v.z);
}

vec3 vec3::operator*(const float n) const noexcept
{
    return vec3(x * n, y * n, z * n);
}

vec3 vec3::operator/(const float n) const noexcept
{
    return vec3(x / n, y / n, z / n);
}

vec3 vec3::operator-() const noexcept    // Unary operator
{
    return vec3(-x, -y, -z);
}

[[nodiscard]] vec3 vec3::normalized() const
{
    float l = length();

    if(l == 0)
        return vec3();

    return vec3(x / l, y / l, z / l);

    // the length thing actually goes slightly faster than
    // the inverse sqrt tricks ... wth?
    //return *this * math::inverse_sqrt(dot(*this));
}

void vec3::normalize() noexcept
{
    *this *= math::inverse_sqrt(dot(*this));
}

float vec3::sqrt_length() const noexcept
{
    return ((x * x) + (y * y) + (z * z));
}

float vec3::length() const noexcept
{
    return math::sqrtf(sqrt_length());
}

[[nodiscard]] vec3 vec3::cross(const vec3& v) const noexcept
{
    return vec3((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
}

[[nodiscard]] float vec3::dot(const vec3& v) const noexcept
{
    return (x * v.x) + (y * v.y) + (z * v.z);
}

vec3 vec3::zero()
{
    return vec3(0.f, 0.f, 0.f);
};
vec3 vec3::one()
{
    return vec3(1.f, 1.f, 1.f);
};
vec3 vec3::left()
{
    return vec3(-1.f, 0.f, 0.f);
};
vec3 vec3::right()
{
    return vec3(1.f, 0.f, 0.f);
};
vec3 vec3::up()
{
    return vec3(0.f, 1.f, 0.f);
};
vec3 vec3::down()
{
    return vec3(0.f, -1.f, 0.f);
};
vec3 vec3::forward()
{
    return vec3(0.f, 0.f, -1.f);
};
vec3 vec3::backward()
{
    return vec3(0.f, 0.f, 1.f);
};
