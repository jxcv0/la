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

/* LA_IMPLEMENTATION not required here as we are linking with static library
 * built with cmake */
#include <gtest/gtest.h>

#include <iostream>

#include "la.h"

TEST(la_tests, la_feq) {
  ASSERT_FALSE(la_feq(1.0f, 1.001f));
  ASSERT_TRUE(la_feq(1.0f, 1.0f));
}

TEST(la_tests, la_radians) {
  ASSERT_FLOAT_EQ(la_radians(3.112f), 0.0543146463f);
}

TEST(la_tests, la_identitym4) {
  la_mat4 m = la_identitym4();
  ASSERT_FLOAT_EQ(m.elem[0][0], 1.0f);
  ASSERT_FLOAT_EQ(m.elem[0][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[0][2], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[0][3], 0.0f);

  ASSERT_FLOAT_EQ(m.elem[1][0], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][1], 1.0f);
  ASSERT_FLOAT_EQ(m.elem[1][2], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][3], 0.0f);

  ASSERT_FLOAT_EQ(m.elem[2][0], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[2][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[2][2], 1.0f);
  ASSERT_FLOAT_EQ(m.elem[2][3], 0.0f);

  ASSERT_FLOAT_EQ(m.elem[3][0], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][2], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][3], 1.0f);
}

TEST(la_tests, la_normalizev3) {
  la_vec3 v = {.elem = {5.0f, 2.0f, -3.0f}};
  v = la_normalizev3(v);

  ASSERT_FLOAT_EQ(v.elem[0], 0.8111071056538127f);
  ASSERT_FLOAT_EQ(v.elem[1], 0.3244428422615251f);
  ASSERT_FLOAT_EQ(v.elem[2], -0.4866642633922876f);
  ASSERT_FLOAT_EQ(v.x, 0.8111071056538127f);
  ASSERT_FLOAT_EQ(v.y, 0.3244428422615251f);
  ASSERT_FLOAT_EQ(v.z, -0.4866642633922876f);
}

TEST(la_tests, la_crossv3) {
  la_vec3 v1 = {.elem = {1.0f, 2.0f, 3.0f}};
  la_vec3 v2 = {.elem = {1.0f, 5.0f, 7.0f}};
  la_vec3 res = la_crossv3(v1, v2);
  ASSERT_FLOAT_EQ(res.x, -1.0f);
  ASSERT_FLOAT_EQ(res.y, -4.0f);
  ASSERT_FLOAT_EQ(res.z, 3.0f);
  ASSERT_FLOAT_EQ(res.elem[0], -1.0f);
  ASSERT_FLOAT_EQ(res.elem[1], -4.0f);
  ASSERT_FLOAT_EQ(res.elem[2], 3.0f);
}

TEST(la_tests, la_productm4) {
  la_mat4 m1 = {0};
  la_mat4 m2 = {0};

  float x = 0.0f;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m1.elem[i][j] = x;
      m2.elem[i][j] = x;
      x += 1.0f;
    }
  }

  la_mat4 result = la_productm4(m1, m2);
  ASSERT_FLOAT_EQ(result.elem[0][0], 56.0f);
  ASSERT_FLOAT_EQ(result.elem[0][1], 62.0f);
  ASSERT_FLOAT_EQ(result.elem[0][2], 68.0f);
  ASSERT_FLOAT_EQ(result.elem[0][3], 74.0f);
  ASSERT_FLOAT_EQ(result.elem[1][0], 152.0f);
  ASSERT_FLOAT_EQ(result.elem[1][1], 174.0f);
  ASSERT_FLOAT_EQ(result.elem[1][2], 196.0f);
  ASSERT_FLOAT_EQ(result.elem[1][3], 218.0f);
  ASSERT_FLOAT_EQ(result.elem[2][0], 248.0f);
  ASSERT_FLOAT_EQ(result.elem[2][1], 286.0f);
  ASSERT_FLOAT_EQ(result.elem[2][2], 324.0f);
  ASSERT_FLOAT_EQ(result.elem[2][3], 362.0f);
  ASSERT_FLOAT_EQ(result.elem[3][0], 344.0f);
  ASSERT_FLOAT_EQ(result.elem[3][1], 398.0f);
  ASSERT_FLOAT_EQ(result.elem[3][2], 452.0f);
  ASSERT_FLOAT_EQ(result.elem[3][3], 506.0);
}

TEST(la_tests, la_productm4v4) {
  la_mat4 m = {0};

  float x = 0.0f;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      m.elem[i][j] = x;
      x += 1.0f;
    }
  }

  la_vec4 vec = {.elem = {1.0f, 2.0f, 3.0f, 4.0f}};
  la_vec4 result = la_productm4v4(m, vec);
  ASSERT_FLOAT_EQ(result.elem[0], 20.0f);
  ASSERT_FLOAT_EQ(result.elem[1], 60.0f);
  ASSERT_FLOAT_EQ(result.elem[2], 100.0f);
  ASSERT_FLOAT_EQ(result.elem[3], 140.0f);
  ASSERT_FLOAT_EQ(result.x, 20.0f);
  ASSERT_FLOAT_EQ(result.y, 60.0f);
  ASSERT_FLOAT_EQ(result.z, 100.0f);
  ASSERT_FLOAT_EQ(result.w, 140.0f);
}

TEST(la_tests, la_dotv3) {
  la_vec3 v1 = {.elem = {1.0f, -3.2f, 0.0f}};
  la_vec3 v2 = {.elem = {5.4f, 3.2f, -5.0f}};
  ASSERT_FLOAT_EQ(la_dotv3(v1, v2), -4.84f);
}

TEST(la_tests, la_dotv4) {
  la_vec4 v1 = {.elem = {1.0f, -3.2f, 0.0f, 1.0f}};
  la_vec4 v2 = {.elem = {5.4f, 3.2f, -5.0f, -0.5f}};
  ASSERT_FLOAT_EQ(la_dotv4(v1, v2), -5.34f);
}

TEST(la_tests, la_perspective) {
  la_mat4 m =
      la_perspective(la_radians(45.0f), (800.0f / 600.0f), 0.1f, 100.0f);

  ASSERT_FLOAT_EQ(m.elem[0][0], 1.81066f);
  ASSERT_FLOAT_EQ(m.elem[0][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[0][2], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[0][3], 0.0f);

  ASSERT_FLOAT_EQ(m.elem[1][0], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][1], 2.4142134f);
  ASSERT_FLOAT_EQ(m.elem[1][2], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][3], 0.0f);

  ASSERT_FLOAT_EQ(m.elem[2][0], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[2][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[2][2], -1.002002f);
  ASSERT_FLOAT_EQ(m.elem[2][3], -1.0f);

  ASSERT_FLOAT_EQ(m.elem[3][0], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][2], -0.2002002f);
  ASSERT_FLOAT_EQ(m.elem[3][3], 0.0f);
}

TEST(la_tests, la_orthographic) {
  la_mat4 m = la_orthographic(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

  ASSERT_FLOAT_EQ(m.elem[0][0], 0.0025f);
  ASSERT_FLOAT_EQ(m.elem[0][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[0][2], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[0][3], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][0], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][1], -0.0033333334f);
  ASSERT_FLOAT_EQ(m.elem[1][2], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][3], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[2][0], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[2][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[2][2], -1.0f);
  ASSERT_FLOAT_EQ(m.elem[2][3], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][0], -1.0f);
  ASSERT_FLOAT_EQ(m.elem[3][1], 1.0f);
  ASSERT_FLOAT_EQ(m.elem[3][2], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][3], 1.0f);
}

TEST(la_tests, la_translate) {
  la_mat4 m = la_identitym4();
  la_vec3 v = {.elem = {0.1f, 0.1f, 0.1f}};
  m = la_translate(m, v);

  ASSERT_FLOAT_EQ(m.elem[3][0], 0.1f);
  ASSERT_FLOAT_EQ(m.elem[3][1], 0.1f);
  ASSERT_FLOAT_EQ(m.elem[3][2], 0.1f);
}

TEST(la_tests, rotate1) {
  la_mat4 m = la_identitym4();
  la_vec3 v = {.elem = {0.0f, 1.0f, 0.0f}};
  m = la_rotate(m, v, la_radians(30.0f));

  ASSERT_FLOAT_EQ(m.elem[0][0], 0.86602539f);
  ASSERT_FLOAT_EQ(m.elem[0][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[0][2], -0.5f);
  ASSERT_FLOAT_EQ(m.elem[0][3], 0.0f);

  ASSERT_FLOAT_EQ(m.elem[1][0], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][1], 1.0f);
  ASSERT_FLOAT_EQ(m.elem[1][2], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][3], 0.0f);

  ASSERT_FLOAT_EQ(m.elem[2][0], 0.5f);
  ASSERT_FLOAT_EQ(m.elem[2][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[2][2], 0.86602539f);
  ASSERT_FLOAT_EQ(m.elem[2][3], 0.0f);

  ASSERT_FLOAT_EQ(m.elem[3][0], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][2], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][3], 1.0f);
}

TEST(la_tests, rotate2) {
  la_vec4 a = {.elem = {1.0f, 0.0f, 0.0f, 1.0f}};
  la_vec3 axis = {.elem = {0.0f, 0.0f, 1.0f}};

  la_mat4 rot = la_identitym4();
  rot = la_rotate(rot, axis, la_radians(90.0f));
  la_vec4 res = la_productm4v4(rot, a);

  // TODO: why is the error bad for elem[0] ?
  ASSERT_NEAR(res.elem[0], 0.0f, 0.000001);
  ASSERT_FLOAT_EQ(res.elem[1], -1.0f);
  ASSERT_FLOAT_EQ(res.elem[2], 0.0f);
  ASSERT_FLOAT_EQ(res.elem[3], 1.0f);
  ASSERT_NEAR(res.x, 0.0f, 0.000001);
  ASSERT_FLOAT_EQ(res.y, -1.0f);
  ASSERT_FLOAT_EQ(res.z, 0.0f);
  ASSERT_FLOAT_EQ(res.w, 1.0f);
}

TEST(la_tests, la_look_at) {
  la_vec3 eye = {.elem = {3.0f, 3.0f, 3.0f}};
  la_vec3 ctr = {.elem = {1.0f, 0.0f, 1.0f}};
  la_vec3 c = {.elem = {eye.x + ctr.x, eye.y + ctr.y, eye.z + ctr.z}};
  la_vec3 up = {.elem = {0.0f, 1.0f, 0.0f}};
  la_mat4 m = la_look_at(eye, c, up);
  ASSERT_FLOAT_EQ(m.elem[0][0], -0.707107f);
  ASSERT_FLOAT_EQ(m.elem[0][1], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[0][2], -0.707107f);
  ASSERT_FLOAT_EQ(m.elem[0][3], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][0], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][1], 1.0f);
  ASSERT_FLOAT_EQ(m.elem[1][2], -0.0f);
  ASSERT_FLOAT_EQ(m.elem[1][3], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[2][0], 0.707107f);
  ASSERT_FLOAT_EQ(m.elem[2][1], -0.0f);
  ASSERT_FLOAT_EQ(m.elem[2][2], -0.707107f);
  ASSERT_FLOAT_EQ(m.elem[2][3], 0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][0], -0.0f);
  ASSERT_FLOAT_EQ(m.elem[3][1], -3.0f);
  ASSERT_FLOAT_EQ(m.elem[3][2], 4.24264f);
  ASSERT_FLOAT_EQ(m.elem[3][3], 1.0f);
}

TEST(la_tests, la_scale) {
  la_mat4 m = {0};
  m.elem[0][2] = 1.032f;
  m.elem[2][1] = 0.032f;
  m.elem[3][0] = 1.0f;
  m.elem[3][2] = 0.888f;
  la_vec3 v = {.elem = {0.0f, 2.0f, 3.0f}};

  la_mat4 result = la_scale(m, v);

  ASSERT_FLOAT_EQ(result.elem[0][0], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[0][1], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[0][2], 3.096000f);
  ASSERT_FLOAT_EQ(result.elem[0][3], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[1][0], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[1][1], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[1][2], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[1][3], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[2][0], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[2][1], 0.064000f);
  ASSERT_FLOAT_EQ(result.elem[2][2], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[2][3], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[3][0], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[3][1], 0.000000f);
  ASSERT_FLOAT_EQ(result.elem[3][2], 2.664000f);
  ASSERT_FLOAT_EQ(result.elem[3][3], 0.000000f);
}
