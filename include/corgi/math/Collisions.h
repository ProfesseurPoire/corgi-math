#pragma once

#include <corgi/math/Matrix.h>
#include <corgi/math/Ray.h>
#include <corgi/math/vec2.h>
#include <corgi/math/vec3.h>

namespace corgi::math
{
// TODO : Maybe really have a Triangle class with static function for this stuff
// I could at least put that and "point_in_triangle" there
vec3 get_triangle_normal(const vec3& a, const vec3& b, const vec3& c);

// Used by the sat
vec3 project_points(const vec3* points, size_t points_size, const vec3& axis);
vec2 project_points(const vec2*   points,
                    size_t        points_size,
                    const Matrix& mat,
                    const vec2&   axis);

bool intersect_with_collider(int                 offset,
                             int                 vertex_size,
                             const Matrix&       model_matrix,
                             const Matrix&       inverse_matrix,
                             const unsigned int* indexes,
                             int                 indexes_size,
                             const float*        vertices,
                             const vec3*         normals,
                             const Ray&          ray,
                             vec3&               intersection_point,
                             vec3&               intersection_normal);

// We also assume the vertices are GL_TRIANGLES
bool intersect_with_mesh(
    const unsigned int* indexes,
    int                 indexes_size,
    const float*        vertices,    // Mesh's vertices
    int    offset,         // offset for the position attribute inside the vertice list
    int    vertex_size,    // Size of 1 vertex, not in bytes but in float
    Matrix model_matrix,
    Ray    ray,
    vec3&  intersectionPoint,
    vec3&  intersectionNormal);

bool Overlap(float valmin1, float valmax1, float valmin2, float valmax2);

float GetOverlap(float valmin1, float valmax1, float valmin2, float valmax2);

bool intersect_2D(const vec2*   vertices_a,
                  unsigned int  vertices_a_size,
                  const vec2*   vertices_b,
                  unsigned int  vertices_b_size,
                  const Matrix& m1,
                  const Matrix& m2,
                  const vec2*   edges1,
                  unsigned int  edges_1_size,
                  const vec2*   edges2,
                  unsigned int  edges_2_size,
                  const Matrix& mat1,    // without translation
                  const Matrix& mat2);

bool intersect_3D(Matrix          model_matrix_a,
                  const unsigned* index1,
                  int             index1_size,
                  const float*    vertices_a,
                  int             vertex_size_a,
                  int             position_offset_a,
                  int             vertex_count_a,

                  Matrix          model_matrix_b,
                  const float*    vertices_b,
                  const unsigned* index2,
                  int             index_2_size,
                  int             vertex_size_b,
                  int             position_offset_b,
                  int             vertex_count_b);
}    // namespace corgi::math