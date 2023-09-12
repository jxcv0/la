/*
 * MIT License
 *
 * Copyright (c) 2023 Jacob Micoud

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#ifndef LA_H_
#define LA_H_

#include <math.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int feq (float f1, float f2);

typedef struct mat4
{
  float elem[4][4];
} mat4;

typedef struct vec4
{
  union
  {
    struct
    {
      float x;
      float y;
      float z;
      float w;
    };
    float elem[4];
  };
} vec4;

typedef vec4 quat;

typedef struct vec3
{
  union
  {
    struct
    {
      float x;
      float y;
      float z;
    };
    float elem[3];
  };
} vec3;

typedef struct vec2
{
  union
  {
    struct
    {
      float x;
      float y;
    };
    float elem[2];
  };
} vec2;

/**
 * @brief Print a matrix to stdout.
 *
 * @param m The matrix to print.
 */
void printm4 (const mat4 m);

/**
 * @brief Print the contents of a vector.
 *
 * @param v The elements of the vector.
 * @param n The number of dimensions of the vector.
 */
void printvn (const float *v, size_t n);

/**
 * @brief Convert an angle from degrees to radians. Not exact.
 *
 * @param degrees The angle in degrees.
 * @return A floating point representing the angle in radians.
 */
float radians (const float degrees);

/**
 * @brief Make a mat4 into an identity matrix.
 *
 * @param m The mat4.
 */
mat4 identitym4 (void);

/**
 * @brief Normalize a vec3.
 *
 * @param vec The vec3 to normalize.
 * @return A normalized vec.
 */
vec3 normalizev3 (const vec3 vec);

/**
 * @brief Get the dot product of 2 vec3's.
 *
 * @param v1 The first vec3.
 * @param v2 The second vec3.
 * @return The dot product of v1 and v2.
 */
float dotv3 (const vec3 v1, const vec3 v2);

/**
 * @brief Compare 2 vec3s
 * @param v1
 * @param v2
 * @return 1 if the vectors are the same, otherwise 0.
 */
int cmpv3 (const vec3 v1, const vec3 v2);

/**
 * @brief Compare 2 vec2s
 * @param v1
 * @param v2
 * @return 1 if the vectors are the same, otherwise 0.
 */
int cmpv2 (const vec2 v1, const vec2 v2);

/**
 * @brief Get the dot product of 2 vec4's
 *
 * @param v1 The first vec4.
 * @param v2 The second vec4.
 * @return The dot product of v1 and v2.
 */
float dotv4 (const vec4 v1, const vec4 v2);

/**
 * @brief Cross 2 vec3's.
 *
 * @param v1 The first vec3.
 * @param v2 The second vec3.
 * @return The cross product of v1 and v2.
 */
vec3 crossv3 (const vec3 v1, const vec3 v2);

/**
 * @brief Get the product of 2 4 x 4 matrices
 *
 * @param m1 The first mat4.
 * @param m2 The second mat4.
 * @return The product of m1 and m2.
 */
mat4 productm4 (const mat4 m1, const mat4 m2);

/**
 * @brief Get the product of a 4x4 matrix and a vec4.
 *
 * @param m The matrix.
 * @param v The vector.
 * @return The product of m and v
 */
vec4 productm4v4 (const mat4 m, const vec4 v);

/**
 * @brief Create a perspective matrix.
 *
 */
mat4 perspective (const float fov, const float aspect_ratio, const float near,
                  const float far);

/**
 * @brief Create an orthographic projection matrix.
 *
 * @param left
 * @param right
 * @param bottom
 * @param top
 * @param near Normalised device coordinate -1.
 * @param far Normalised device coordinate +1.
 *
 * @return mat4
 */
mat4 orthographic (const float left, const float right, const float bottom,
                   const float top, const float near, const float far);

/**
 * @brief Create a view matrix.
 *
 * @param eye The direction of the view.
 * @param ctr The position of the view.
 * @param up The up direction of the view.
 * @return A view matrix.
 */
mat4 look_at (const vec3 eye, const vec3 ctr, const vec3 up);

/**
 * @brief Translate a mat4 by a vec3.
 *
 * @param m The matrix to translate.
 * @param v The translation vector.
 * @return The translated matrix.
 */
mat4 translate (const mat4 m, const vec3 v);

/**
 * @brief Rotate a matrix about and axis (using unit quaternion).
 *
 * @param m The matrix to apply the rotation to.
 * @param axis The axis of the rotation.
 * @param rads The rotation angle in radians.
 * @return The rotated matrix.
 */
mat4 rotate (const mat4 m, const vec3 axis, const float rads);

/**
 * @brief Scale a transformation matrix by a vector v.
 *
 * @param m The matrix to transform.
 * @param v The scaling vector.
 * @return The scaled matrix.
 */
mat4 scale (const mat4 m, const vec3 v);

#ifdef __cplusplus
}
#endif

#endif // LA_H_
