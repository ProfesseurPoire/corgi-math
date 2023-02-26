#pragma once

#include <ostream>
#include <string>

namespace corgi
{
    struct vec4
    {
        constexpr explicit vec4(float x = 0.0F, float y = 0.0F, float z = 0.0F, float w = 0.0F) noexcept : x(x), y(y), z(z), w(w) {}

        float x;
        float y;
        float z;
        float w;

        [[nodiscard]] bool operator==(const vec4 &other) const noexcept
        {
            return x == other.x && y == other.y && z == other.z && w == other.w;
        }

        [[nodiscard]] bool operator!=(const vec4 &other) const noexcept
        {
            return !(*this == other);
        }

        [[nodiscard]] vec4 operator-(const vec4 &other) const noexcept
        {
            return vec4(x - other.x, y - other.y, z - other.z, w - other.w);
        }

        [[nodiscard]] vec4 operator+(const vec4 &other) const noexcept
        {
            return vec4(x + other.x, y + other.y, z + other.z, w + other.w);
        }

        [[nodiscard]] vec4 operator*(const vec4 &other) const noexcept
        {
            return vec4(x * other.x, y * other.y, z * other.z, w * other.w);
        }

        [[nodiscard]] static constexpr vec4 one() noexcept
        {
            return vec4{1.0F, 1.0F, 1.0F, 1.0F};
        }

        [[nodiscard]] static constexpr vec4 zero() noexcept
        {
            return vec4(0.0F, 0.0f, 0.0F, 0.0F);
        }

        [[nodiscard]] static constexpr vec4 right() noexcept
        {
            return vec4(1.0F, 0.0F, 0.0F, 0.0F);
        }

        [[nodiscard]] static constexpr vec4 up() noexcept
        {
            return vec4(0.0F, 1.0F, 0.0F, 1.0F);
        }

        [[nodiscard]] static constexpr vec4 down() noexcept
        {
            return vec4(0.0F, -1.0F, 0.0F, 1.0F);
        }

        [[nodiscard]] static constexpr vec4 forward() noexcept
        {
            return vec4(0.0F, 0.0F, 1.0F, 1.0F);
        }

        /*!
         * @brief lexicographical  comparison for sorting only
         */
        int lexicographical_comp(const vec4 &other) const noexcept
        {
            if (x < other.x)
                return -1;

            if (x > other.x)
                return 1;

            if (y < other.y)
                return -1;

            if (y > other.y)
                return 1;

            if (z < other.z)
                return -1;

            if (z > other.z)
                return 1;

            if (w < other.w)
                return -1;

            if (w > other.w)
                return 1;

            return 0;
        }
    };

    static inline std::ostream &operator<<(std::ostream &o, const corgi::vec4 &v)
    {
        return o << "{ x : " << v.x << " ; y = " << v.y << " ; z = " << v.z << " ; w = " << v.w << "}";
    }
}
