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

#include "la.h"

#include <float.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

/**
 * ----------------------------------------------------------------------------
 */
int
la_feq (float f1, float f2)
{
  return fabs (f1 - f2) < FLT_EPSILON;
}

/**
 * ----------------------------------------------------------------------------
 */
void
la_printm4 (const la_mat4 m)
{
  printf ("{ ");
  for (int i = 0; i < 4; i++)
    {
      printf ("{ %f %f %f %f } ", m.elem[i][0], m.elem[i][1], m.elem[i][2],
              m.elem[i][3]);
    }
  printf ("}\n");
}

/**
 * ----------------------------------------------------------------------------
 */
void
la_printvn (const float *v, size_t n)
{
  printf ("{ ");
  for (size_t i = 0; i < n; i++)
    {
      printf ("%f ", v[i]);
    }
  printf ("}\n");
}

/**
 * ----------------------------------------------------------------------------
 */
float
la_radians (const float degrees)
{
  return (degrees * M_PI) / 180.0f;
}

/**
 * ----------------------------------------------------------------------------
 */
la_mat4
la_identitym4 (void)
{
  la_mat4 i = { .elem = { { 1.0f, 0.0f, 0.0f, 0.0f },
                       { 0.0f, 1.0f, 0.0f, 0.0f },
                       { 0.0f, 0.0f, 1.0f, 0.0f },
                       { 0.0f, 0.0f, 0.0f, 1.0f } } };
  return i;
}

/**
 * ----------------------------------------------------------------------------
 */
la_vec3
la_normalizev3 (const la_vec3 v)
{
  float l = sqrt (la_dotv3 (v, v));
  la_vec3 n = { .elem = { v.elem[0] / l, v.elem[1] / l, v.elem[2] / l } };
  return n;
}

/**
 * ----------------------------------------------------------------------------
 */
float
la_dotvn (const float *v1, const float *v2, size_t n)
{
  float res = 0.0f;
  for (size_t i = 0; i < n; i++)
    {
      res += v1[i] * v2[i];
    }
  return res;
}

/**
 * ----------------------------------------------------------------------------
 */
float
la_dotv3 (const la_vec3 v1, const la_vec3 v2)
{
  return la_dotvn (v1.elem, v2.elem, 3);
}

/**
 * ----------------------------------------------------------------------------
 */
int
la_cmpv3 (const la_vec3 v1, const la_vec3 v2)
{
  for (int i = 0; i < 3; i++)
    {
      if (fabs (v1.elem[i] - v2.elem[i]) > FLT_EPSILON)
        {
          return 0;
        }
    }
  return 1;
}

/**
 * ----------------------------------------------------------------------------
 */
int
la_cmpv2 (const la_vec2 v1, const la_vec2 v2)
{
  for (int i = 0; i < 2; i++)
    {
      if (fabs (v1.elem[i] - v2.elem[i]) > FLT_EPSILON)
        {
          return 0;
        }
    }
  return 1;
}

/**
 * ----------------------------------------------------------------------------
 */
float
la_dotv4 (const la_vec4 v1, const la_vec4 v2)
{
  return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w);
}
/**
 * ----------------------------------------------------------------------------
 */
la_vec3
la_crossv3 (const struct la_vec3 v1, const struct la_vec3 v2)
{
  struct la_vec3 r
      = { { { (v1.y * v2.z) - (v1.z * v2.y), (v1.z * v2.x) - (v1.x * v2.z),
              (v1.x * v2.y) - (v1.y * v2.x) } } };
  return r;
}

/**
 * ----------------------------------------------------------------------------
 */
la_mat4
la_productm4 (const la_mat4 m1, const la_mat4 m2)
{
  la_mat4 r = { 0 };
  for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
        {
          for (size_t k = 0; k < 4; k++)
            {
              r.elem[i][k] += m1.elem[i][j] * m2.elem[j][k];
            }
        }
    }
  return r;
}

/**
 * ----------------------------------------------------------------------------
 */
la_vec4
la_productm4v4 (const la_mat4 m, const la_vec4 v)
{
  la_vec4 res = { 0 };
  for (size_t i = 0; i < 4; i++)
    {
      for (size_t j = 0; j < 4; j++)
        {
          res.elem[i] += m.elem[i][j] * v.elem[j];
        }
    }
  return res;
}

/**
 * ----------------------------------------------------------------------------
 */
la_mat4
la_perspective (const float fov, const float aspect_ratio, const float near,
             const float far)
{
  const float t = tan (fov / 2.0f);

  la_mat4 mat = { 0 };
  mat.elem[0][0] = 1.0f / (aspect_ratio * t);
  mat.elem[1][1] = 1.0f / t;
  mat.elem[2][2] = -(far + near) / (far - near);
  mat.elem[2][3] = -1.0f;
  mat.elem[3][2] = -(2.0f * far * near) / (far - near);
  return mat;
}

/**
 * ----------------------------------------------------------------------------
 */
la_mat4
la_orthographic (const float left, const float right, const float bottom,
              const float top, const float near, const float far)
{
  la_mat4 mat = la_identitym4 ();
  mat.elem[0][0] = 2.0f / (right - left);
  mat.elem[1][1] = 2.0f / (top - bottom);
  mat.elem[2][2] = -2.0f / (far - near);
  mat.elem[3][0] = -(right + left) / (right - left);
  mat.elem[3][1] = -(top + bottom) / (top - bottom);
  mat.elem[3][2] = -(far + near) / (far - near);
  return mat;
}

/**
 * ----------------------------------------------------------------------------
 */
la_mat4
la_look_at (const la_vec3 eye, const la_vec3 ctr, const la_vec3 up)
{
  la_vec3 f = { { { ctr.elem[0] - eye.elem[0], ctr.elem[1] - eye.elem[1],
                 ctr.elem[2] - eye.elem[2] } } };

  f = la_normalizev3 (f);
  la_vec3 s = la_normalizev3 (la_crossv3 (f, up));
  la_vec3 u = la_crossv3 (s, f);

  la_mat4 mat = la_identitym4 ();

  mat.elem[0][0] = s.elem[0];
  mat.elem[1][0] = s.elem[1];
  mat.elem[2][0] = s.elem[2];

  mat.elem[0][1] = u.elem[0];
  mat.elem[1][1] = u.elem[1];
  mat.elem[2][1] = u.elem[2];

  mat.elem[0][2] = -f.elem[0];
  mat.elem[1][2] = -f.elem[1];
  mat.elem[2][2] = -f.elem[2];

  mat.elem[3][0] = -la_dotv3 (s, eye);
  mat.elem[3][1] = -la_dotv3 (u, eye);
  mat.elem[3][2] = la_dotv3 (f, eye);
  return mat;
}

/**
 * ----------------------------------------------------------------------------
 */
la_mat4
la_translate (const la_mat4 m, const la_vec3 v)
{
  la_mat4 res = m;
  res.elem[3][0] += v.elem[0];
  res.elem[3][1] += v.elem[1];
  res.elem[3][2] += v.elem[2];
  return res;
}

/**
 * ----------------------------------------------------------------------------
 */
la_mat4
la_rotate (const la_mat4 m, const la_vec3 axis, const float rads)
{
  const float c = cos (rads);
  const float s = sin (rads);

  la_vec3 a = la_normalizev3 (axis);

  la_mat4 rot = { 0 };
  rot.elem[0][0] = c + (1.0f - c) * a.elem[0] * a.elem[0];
  rot.elem[0][1] = (1.0f - c) * a.elem[0] * a.elem[1] + s * a.elem[2];
  rot.elem[0][2] = (1.0f - c) * a.elem[0] * a.elem[2] - s * a.elem[1];

  rot.elem[1][0] = (1.0f - c) * a.elem[1] * a.elem[0] - s * a.elem[2];
  rot.elem[1][1] = c + (1.0f - c) * a.elem[1] * a.elem[1];
  rot.elem[1][2] = (1.0f - c) * a.elem[1] * a.elem[2] + s * a.elem[0];

  rot.elem[2][0] = (1.0f - c) * a.elem[2] * a.elem[0] + s * a.elem[1];
  rot.elem[2][1] = (1.0f - c) * a.elem[2] * a.elem[1] - s * a.elem[0];
  rot.elem[2][2] = c + (1.0f - c) * a.elem[2] * a.elem[2];

  rot.elem[3][3] = 1.0f;

  // rot.elem[3][0] = m.elem[3][0];
  // rot.elem[3][1] = m.elem[3][1];
  // rot.elem[3][2] = m.elem[3][2];
  // rot.elem[3][3] = m.elem[3][3];

  return la_productm4 (m, rot);
}

/**
 * ----------------------------------------------------------------------------
 */
la_mat4
la_scale (const la_mat4 m, const la_vec3 v)
{
  la_mat4 sm = la_identitym4 ();
  sm.elem[0][0] = v.elem[0];
  sm.elem[1][1] = v.elem[1];
  sm.elem[2][2] = v.elem[2];
  sm.elem[3][0] = m.elem[3][0];
  sm.elem[3][1] = m.elem[3][1];
  sm.elem[3][2] = m.elem[3][2];
  sm.elem[3][3] = m.elem[3][3];

  return la_productm4 (m, sm);
}
