#include "la.h"
#include <gtest/gtest.h>
#include <iostream>

TEST (la_tests, feq)
{
  ASSERT_FALSE (feq (1.0f, 1.001f));
  ASSERT_TRUE (feq (1.0f, 1.0f));
}

TEST (la_tests, radians) { ASSERT_FLOAT_EQ (radians (3.112f), 0.0543146463f); }

TEST (la_tests, identitym4)
{
  mat4_t m = identitym4 ();
  ASSERT_FLOAT_EQ (m.elem[0][0], 1.0f);
  ASSERT_FLOAT_EQ (m.elem[0][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[0][2], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[0][3], 0.0f);

  ASSERT_FLOAT_EQ (m.elem[1][0], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][1], 1.0f);
  ASSERT_FLOAT_EQ (m.elem[1][2], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][3], 0.0f);

  ASSERT_FLOAT_EQ (m.elem[2][0], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[2][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[2][2], 1.0f);
  ASSERT_FLOAT_EQ (m.elem[2][3], 0.0f);

  ASSERT_FLOAT_EQ (m.elem[3][0], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][2], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][3], 1.0f);
}

TEST (la_tests, normalizev3)
{
  vec3_t v = { .elem = { 5.0f, 2.0f, -3.0f } };
  v = normalizev3 (v);

  ASSERT_FLOAT_EQ (v.elem[0], 0.8111071056538127f);
  ASSERT_FLOAT_EQ (v.elem[1], 0.3244428422615251f);
  ASSERT_FLOAT_EQ (v.elem[2], -0.4866642633922876f);
  ASSERT_FLOAT_EQ (v.x, 0.8111071056538127f);
  ASSERT_FLOAT_EQ (v.y, 0.3244428422615251f);
  ASSERT_FLOAT_EQ (v.z, -0.4866642633922876f);
}

TEST (la_tests, crossv3)
{
  vec3_t v1 = { .elem = { 1.0f, 2.0f, 3.0f } };
  vec3_t v2 = { .elem = { 1.0f, 5.0f, 7.0f } };
  vec3_t res = crossv3 (v1, v2);
  ASSERT_FLOAT_EQ (res.x, -1.0f);
  ASSERT_FLOAT_EQ (res.y, -4.0f);
  ASSERT_FLOAT_EQ (res.z, 3.0f);
  ASSERT_FLOAT_EQ (res.elem[0], -1.0f);
  ASSERT_FLOAT_EQ (res.elem[1], -4.0f);
  ASSERT_FLOAT_EQ (res.elem[2], 3.0f);
}

TEST (la_tests, productm4)
{
  mat4_t m1 = { 0 };
  mat4_t m2 = { 0 };

  float x = 0.0f;
  for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
        {
          m1.elem[i][j] = x;
          m2.elem[i][j] = x;
          x += 1.0f;
        }
    }

  mat4_t result = productm4 (m1, m2);
  ASSERT_FLOAT_EQ (result.elem[0][0], 56.0f);
  ASSERT_FLOAT_EQ (result.elem[0][1], 62.0f);
  ASSERT_FLOAT_EQ (result.elem[0][2], 68.0f);
  ASSERT_FLOAT_EQ (result.elem[0][3], 74.0f);
  ASSERT_FLOAT_EQ (result.elem[1][0], 152.0f);
  ASSERT_FLOAT_EQ (result.elem[1][1], 174.0f);
  ASSERT_FLOAT_EQ (result.elem[1][2], 196.0f);
  ASSERT_FLOAT_EQ (result.elem[1][3], 218.0f);
  ASSERT_FLOAT_EQ (result.elem[2][0], 248.0f);
  ASSERT_FLOAT_EQ (result.elem[2][1], 286.0f);
  ASSERT_FLOAT_EQ (result.elem[2][2], 324.0f);
  ASSERT_FLOAT_EQ (result.elem[2][3], 362.0f);
  ASSERT_FLOAT_EQ (result.elem[3][0], 344.0f);
  ASSERT_FLOAT_EQ (result.elem[3][1], 398.0f);
  ASSERT_FLOAT_EQ (result.elem[3][2], 452.0f);
  ASSERT_FLOAT_EQ (result.elem[3][3], 506.0);
}

TEST (la_tests, productm4v4)
{
  mat4_t m = { 0 };

  float x = 0.0f;
  for (int i = 0; i < 4; i++)
    {
      for (int j = 0; j < 4; j++)
        {
          m.elem[i][j] = x;
          x += 1.0f;
        }
    }

  vec4_t vec = { .elem = { 1.0f, 2.0f, 3.0f, 4.0f } };
  vec4_t result = productm4v4 (m, vec);
  ASSERT_FLOAT_EQ (result.elem[0], 20.0f);
  ASSERT_FLOAT_EQ (result.elem[1], 60.0f);
  ASSERT_FLOAT_EQ (result.elem[2], 100.0f);
  ASSERT_FLOAT_EQ (result.elem[3], 140.0f);
  ASSERT_FLOAT_EQ (result.x, 20.0f);
  ASSERT_FLOAT_EQ (result.y, 60.0f);
  ASSERT_FLOAT_EQ (result.z, 100.0f);
  ASSERT_FLOAT_EQ (result.w, 140.0f);
}

TEST (la_tests, dotv3)
{
  vec3_t v1 = { .elem = { 1.0f, -3.2f, 0.0f } };
  vec3_t v2 = { .elem = { 5.4f, 3.2f, -5.0f } };
  ASSERT_FLOAT_EQ (dotv3 (v1, v2), -4.84f);
}

TEST (la_tests, dotv4)
{
  vec4_t v1 = { .elem = { 1.0f, -3.2f, 0.0f, 1.0f } };
  vec4_t v2 = { .elem = { 5.4f, 3.2f, -5.0f, -0.5f } };
  ASSERT_FLOAT_EQ (dotv4 (v1, v2), -5.34f);
}

TEST (la_tests, perspective)
{
  mat4_t m = perspective (radians (45.0f), (800.0f / 600.0f), 0.1f, 100.0f);

  ASSERT_FLOAT_EQ (m.elem[0][0], 1.81066f);
  ASSERT_FLOAT_EQ (m.elem[0][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[0][2], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[0][3], 0.0f);

  ASSERT_FLOAT_EQ (m.elem[1][0], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][1], 2.4142134f);
  ASSERT_FLOAT_EQ (m.elem[1][2], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][3], 0.0f);

  ASSERT_FLOAT_EQ (m.elem[2][0], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[2][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[2][2], -1.002002f);
  ASSERT_FLOAT_EQ (m.elem[2][3], -1.0f);

  ASSERT_FLOAT_EQ (m.elem[3][0], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][2], -0.2002002f);
  ASSERT_FLOAT_EQ (m.elem[3][3], 0.0f);
}

TEST (la_tests, orthographic)
{
  mat4_t m = orthographic (0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

  ASSERT_FLOAT_EQ (m.elem[0][0], 0.0025f);
  ASSERT_FLOAT_EQ (m.elem[0][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[0][2], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[0][3], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][0], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][1], -0.0033333334f);
  ASSERT_FLOAT_EQ (m.elem[1][2], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][3], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[2][0], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[2][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[2][2], -1.0f);
  ASSERT_FLOAT_EQ (m.elem[2][3], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][0], -1.0f);
  ASSERT_FLOAT_EQ (m.elem[3][1], 1.0f);
  ASSERT_FLOAT_EQ (m.elem[3][2], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][3], 1.0f);
}

TEST (la_tests, translate)
{
  mat4_t m = identitym4 ();
  vec3_t v = { .elem = { 0.1f, 0.1f, 0.1f } };
  m = translate (m, v);

  ASSERT_FLOAT_EQ (m.elem[3][0], 0.1f);
  ASSERT_FLOAT_EQ (m.elem[3][1], 0.1f);
  ASSERT_FLOAT_EQ (m.elem[3][2], 0.1f);
}

TEST (la_tests, rotate1)
{
  mat4_t m = identitym4 ();
  vec3_t v = { .elem = { 0.0f, 1.0f, 0.0f } };
  m = rotate (m, v, radians (30.0f));

  ASSERT_FLOAT_EQ (m.elem[0][0], 0.86602539f);
  ASSERT_FLOAT_EQ (m.elem[0][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[0][2], -0.5f);
  ASSERT_FLOAT_EQ (m.elem[0][3], 0.0f);

  ASSERT_FLOAT_EQ (m.elem[1][0], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][1], 1.0f);
  ASSERT_FLOAT_EQ (m.elem[1][2], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][3], 0.0f);

  ASSERT_FLOAT_EQ (m.elem[2][0], 0.5f);
  ASSERT_FLOAT_EQ (m.elem[2][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[2][2], 0.86602539f);
  ASSERT_FLOAT_EQ (m.elem[2][3], 0.0f);

  ASSERT_FLOAT_EQ (m.elem[3][0], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][2], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][3], 1.0f);
}

TEST (la_tests, rotate2)
{
  vec4_t a = { .elem = { 1.0f, 0.0f, 0.0f, 1.0f } };
  vec3_t axis = { .elem = { 0.0f, 0.0f, 1.0f } };

  mat4_t rot = identitym4 ();
  rot = rotate (rot, axis, radians (90.0f));
  vec4_t res = productm4v4 (rot, a);

  // TODO: why is the error bad for elem[0] ?
  ASSERT_NEAR (res.elem[0], 0.0f, 0.000001);
  ASSERT_FLOAT_EQ (res.elem[1], -1.0f);
  ASSERT_FLOAT_EQ (res.elem[2], 0.0f);
  ASSERT_FLOAT_EQ (res.elem[3], 1.0f);
  ASSERT_NEAR (res.x, 0.0f, 0.000001);
  ASSERT_FLOAT_EQ (res.y, -1.0f);
  ASSERT_FLOAT_EQ (res.z, 0.0f);
  ASSERT_FLOAT_EQ (res.w, 1.0f);
}

TEST (la_tests, look_at)
{
  vec3_t eye = { .elem = { 3.0f, 3.0f, 3.0f } };
  vec3_t ctr = { .elem = { 1.0f, 0.0f, 1.0f } };
  vec3_t c = { .elem = { eye.x + ctr.x, eye.y + ctr.y, eye.z + ctr.z } };
  vec3_t up = { .elem = { 0.0f, 1.0f, 0.0f } };
  mat4_t m = look_at (eye, c, up);
  ASSERT_FLOAT_EQ (m.elem[0][0], -0.707107f);
  ASSERT_FLOAT_EQ (m.elem[0][1], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[0][2], -0.707107f);
  ASSERT_FLOAT_EQ (m.elem[0][3], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][0], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][1], 1.0f);
  ASSERT_FLOAT_EQ (m.elem[1][2], -0.0f);
  ASSERT_FLOAT_EQ (m.elem[1][3], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[2][0], 0.707107f);
  ASSERT_FLOAT_EQ (m.elem[2][1], -0.0f);
  ASSERT_FLOAT_EQ (m.elem[2][2], -0.707107f);
  ASSERT_FLOAT_EQ (m.elem[2][3], 0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][0], -0.0f);
  ASSERT_FLOAT_EQ (m.elem[3][1], -3.0f);
  ASSERT_FLOAT_EQ (m.elem[3][2], 4.24264f);
  ASSERT_FLOAT_EQ (m.elem[3][3], 1.0f);
}

TEST (la_tests, scale)
{
  mat4_t m = { 0 };
  m.elem[0][2] = 1.032f;
  m.elem[2][1] = 0.032f;
  m.elem[3][0] = 1.0f;
  m.elem[3][2] = 0.888f;
  vec3_t v = { .elem = { 0.0f, 2.0f, 3.0f } };

  mat4_t result = scale (m, v);

  ASSERT_FLOAT_EQ (result.elem[0][0], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[0][1], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[0][2], 3.096000f);
  ASSERT_FLOAT_EQ (result.elem[0][3], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[1][0], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[1][1], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[1][2], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[1][3], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[2][0], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[2][1], 0.064000f);
  ASSERT_FLOAT_EQ (result.elem[2][2], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[2][3], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[3][0], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[3][1], 0.000000f);
  ASSERT_FLOAT_EQ (result.elem[3][2], 2.664000f);
  ASSERT_FLOAT_EQ (result.elem[3][3], 0.000000f);
}
