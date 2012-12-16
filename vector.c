#include "vector.h"

#include <math.h>

float DegToRad(float deg) {
	return deg*((float)PI/180.0f);
}
vec2 vec2_neg(vec2 a) {
	vec2 ret = {-a.x, -a.y};
	return ret;
}
vec2 vec2_add(vec2 a, vec2 b) {
	vec2 ret = {a.x + b.x, a.y + b.y};
	return ret;
}
vec2 vec2_sub(vec2 a, vec2 b) {
	return vec2_add(a, vec2_neg(b));
}
vec2 vec2_mul(vec2 a, float val) {
	vec2 ret = {a.x *val, a.y * val};
	return ret;
}
vec2 vec2_div(vec2 a, float val) {
	return vec2_mul(a, 1/val);
}
float vec2_len(vec2 a) {
	return (float)sqrt(a.x * a.x + a.y * a.y);
}
vec2 vec2_norm(vec2 a) {
	float len = vec2_len(a);
	vec2 ret = {a.x * 1/len, a.y * 1/len};
	return ret;
}
float vec2_dot(vec2 a, vec2 b) {
	vec2 an = vec2_norm(a);
	vec2 bn = vec2_norm(b);
	return an.x * bn.x + an.y * bn.y;
}
vec2 vec2_rot(vec2 a, float angle) {

	vec2 ret;
	angle = DegToRad(angle);

	ret.x = (float)(cos(angle) * a.x - sin(angle) * a.y);
	ret.y = (float)(sin(angle) * a.x + cos(angle) * a.y);
	return ret;
}