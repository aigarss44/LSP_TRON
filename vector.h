#pragma once

typedef struct vec2 {
	float x, y;
} vec2;

#define PI 3.14159265358979323846

float DegToRad(float deg);
vec2 vec2_neg(vec2 a);
vec2 vec2_add(vec2 a, vec2 b);
vec2 vec2_sub(vec2 a, vec2 b);
vec2 vec2_mul(vec2 a, float val);
vec2 vec2_div(vec2 a, float val);
float vec2_len(vec2 a);
vec2 vec2_norm(vec2 a);
float vec2_dot(vec2 a, vec2 b);
vec2 vec2_rot(vec2 a, float angle);
