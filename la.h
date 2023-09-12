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

int la_feq (float f1, float f2);

typedef struct la_mat4
{
  float elem[4][4];
} la_mat4;

typedef struct la_vec4
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
} la_vec4;

typedef la_vec4 la_quat;

typedef struct la_vec3
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
} la_vec3;

typedef struct la_vec2
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
} la_vec2;

/**
 * @brief Print a matrix to stdout.
 *
 * @param m The matrix to print.
 */
void la_printm4 (const la_mat4 m);

/**
 * @brief Print the contents of a vector.
 *
 * @param v The elements of the vector.
 * @param n The number of dimensions of the vector.
 */
void la_printvn (const float *v, size_t n);

/**
 * @brief Convert an angle from degrees to radians. Not exact.
 *
 * @param degrees The angle in degrees.
 * @return A floating point representing the angle in radians.
 */
float la_radians (const float degrees);

/**
 * @brief Make a la_mat4 into an identity matrix.
 *
 * @param m The la_mat4.
 */
la_mat4 la_identitym4 (void);

/**
 * @brief Normalize a la_vec3.
 *
 * @param vec The la_vec3 to normalize.
 * @return A normalized vec.
 */
la_vec3 la_normalizev3 (const la_vec3 vec);

/**
 * @brief Get the dot product of 2 la_vec3's.
 *
 * @param v1 The first la_vec3.
 * @param v2 The second la_vec3.
 * @return The dot product of v1 and v2.
 */
float la_dotv3 (const la_vec3 v1, const la_vec3 v2);

/**
 * @brief Compare 2 la_vec3s
 * @param v1
 * @param v2
 * @return 1 if the vectors are the same, otherwise 0.
 */
int la_cmpv3 (const la_vec3 v1, const la_vec3 v2);

/**
 * @brief Compare 2 la_vec2s
 * @param v1
 * @param v2
 * @return 1 if the vectors are the same, otherwise 0.
 */
int la_cmpv2 (const la_vec2 v1, const la_vec2 v2);

/**
 * @brief Get the dot product of 2 la_vec4's
 *
 * @param v1 The first la_vec4.
 * @param v2 The second la_vec4.
 * @return The dot product of v1 and v2.
 */
float la_dotv4 (const la_vec4 v1, const la_vec4 v2);

/**
 * @brief Cross 2 la_vec3's.
 *
 * @param v1 The first la_vec3.
 * @param v2 The second la_vec3.
 * @return The cross product of v1 and v2.
 */
la_vec3 la_crossv3 (const la_vec3 v1, const la_vec3 v2);

/**
 * @brief Get the product of 2 4 x 4 matrices
 *
 * @param m1 The first la_mat4.
 * @param m2 The second la_mat4.
 * @return The product of m1 and m2.
 */
la_mat4 la_productm4 (const la_mat4 m1, const la_mat4 m2);

/**
 * @brief Get the product of a 4x4 matrix and a la_vec4.
 *
 * @param m The matrix.
 * @param v The vector.
 * @return The product of m and v
 */
la_vec4 la_productm4v4 (const la_mat4 m, const la_vec4 v);

/**
 * @brief Create a perspective matrix.
 *
 */
la_mat4 la_perspective (const float fov, const float aspect_ratio, const float near,
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
 * @return la_mat4
 */
la_mat4 la_orthographic (const float left, const float right, const float bottom,
                   const float top, const float near, const float far);

/**
 * @brief Create a view matrix.
 *
 * @param eye The direction of the view.
 * @param ctr The position of the view.
 * @param up The up direction of the view.
 * @return A view matrix.
 */
la_mat4 la_look_at (const la_vec3 eye, const la_vec3 ctr, const la_vec3 up);

/**
 * @brief Translate a la_mat4 by a la_vec3.
 *
 * @param m The matrix to translate.
 * @param v The translation vector.
 * @return The translated matrix.
 */
la_mat4 la_translate (const la_mat4 m, const la_vec3 v);

/**
 * @brief Rotate a matrix about and axis (using unit quaternion).
 *
 * @param m The matrix to apply the rotation to.
 * @param axis The axis of the rotation.
 * @param rads The rotation angle in radians.
 * @return The rotated matrix.
 */
la_mat4 la_rotate (const la_mat4 m, const la_vec3 axis, const float rads);

/**
 * @brief Scale a transformation matrix by a vector v.
 *
 * @param m The matrix to transform.
 * @param v The scaling vector.
 * @return The scaled matrix.
 */
la_mat4 la_scale (const la_mat4 m, const la_vec3 v);

#ifdef __cplusplus
}
#endif

#endif // LA_H_
