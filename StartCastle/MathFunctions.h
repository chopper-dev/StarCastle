struct Mat3 {
	double d[9];
};
struct Vec3 {
	double x, y, z;
};
struct Vec2 {
	double x, y;
};
Mat3 Mat3Rotate(float rad) {
	Mat3 rotate;

	//x' = x * cos(alfa) - y * sin(alfa)
	//y' = x * sin(alfa) + y * cos(alfa)

	rotate.d[0] = cos(rad);
	rotate.d[1] = sin(rad);
	rotate.d[2] = 0;
	rotate.d[3] = -sin(rad);
	rotate.d[4] = cos(rad);
	rotate.d[5] = 0;
	rotate.d[6] = 0;
	rotate.d[7] = 0;
	rotate.d[8] = 1;
	return rotate;
}
Mat3 Mat3Identity() {
	Mat3 identity;
	identity.d[0] = 1;
	identity.d[1] = 0;
	identity.d[2] = 0;
	identity.d[3] = 0;
	identity.d[4] = 1;
	identity.d[5] = 0;
	identity.d[6] = 0;
	identity.d[7] = 0;
	identity.d[8] = 1;
	return identity;
}
Mat3 Mat3Rotate(float sin, float cos) {
	Mat3 rotate;

	rotate.d[0] = cos;
	rotate.d[1] = sin;
	rotate.d[2] = 0;
	rotate.d[3] = -sin;
	rotate.d[4] = cos;
	rotate.d[5] = 0;
	rotate.d[6] = 0;
	rotate.d[7] = 0;
	rotate.d[8] = 1;
	return rotate;
}
Mat3 Mat3Scale(float scale_x, float scale_y) {
	Mat3 result;
	result.d[0] = scale_x;
	result.d[1] = 0;
	result.d[2] = 0;
	result.d[3] = 0;
	result.d[4] = scale_y;
	result.d[5] = 0;
	result.d[6] = 0;
	result.d[7] = 0;
	result.d[8] = 1;
	return result;
}
Mat3 Mat3Translate(float translate_x, float translate_y) {
	Mat3 result;
	result.d[0] = 1;
	result.d[1] = 0;
	result.d[2] = 0;
	result.d[3] = 0;
	result.d[4] = 1;
	result.d[5] = 0;
	result.d[6] = translate_x;
	result.d[7] = translate_y;
	result.d[8] = 1;
	return result;
}
Mat3 Mat3TranslateScale(float scale_x, float scale_y, float translate_x, float translate_y) {
	Mat3 result;
	result.d[0] = scale_x;
	result.d[1] = 0;
	result.d[2] = 0;
	result.d[3] = 0;
	result.d[4] = scale_y;
	result.d[5] = 0;
	result.d[6] = translate_x;
	result.d[7] = translate_y;
	result.d[8] = 1;
	return result;
}
Vec3 Mat3MultiplyVec3(Mat3 mat, Vec3 vec) {
	Vec3 result;
	result.x = (mat.d[0] * vec.x) + (mat.d[3] * vec.y) + (mat.d[6] * vec.z);
	result.y = (mat.d[1] * vec.x) + (mat.d[4] * vec.y) + (mat.d[7] * vec.z);
	result.z = (mat.d[2] * vec.x) + (mat.d[5] * vec.y) + (mat.d[8] * vec.z);
	return result;
}
Vec2 Mat3MultiplyVec2(Mat3 mat, Vec2 vec) {
	Vec2 result;
	result.x = (mat.d[0] * vec.x) + (mat.d[3] * vec.y) + mat.d[6];
	result.y = (mat.d[1] * vec.x) + (mat.d[4] * vec.y) + mat.d[7];
	return result;
}
Mat3 Mat3MultiplyMat3(Mat3 mat1, Mat3 mat2) {
	Mat3 result;
	result.d[0] = (mat1.d[0] * mat2.d[0]) + (mat1.d[3] * mat2.d[1]) + (mat1.d[6] * mat2.d[2]);
	result.d[3] = (mat1.d[0] * mat2.d[3]) + (mat1.d[3] * mat2.d[4]) + (mat1.d[6] * mat2.d[5]);
	result.d[6] = (mat1.d[0] * mat2.d[6]) + (mat1.d[3] * mat2.d[7]) + (mat1.d[6] * mat2.d[8]);

	result.d[1] = (mat1.d[1] * mat2.d[0]) + (mat1.d[4] * mat2.d[1]) + (mat1.d[7] * mat2.d[2]);
	result.d[4] = (mat1.d[1] * mat2.d[3]) + (mat1.d[4] * mat2.d[4]) + (mat1.d[7] * mat2.d[5]);
	result.d[7] = (mat1.d[1] * mat2.d[6]) + (mat1.d[4] * mat2.d[7]) + (mat1.d[7] * mat2.d[8]);

	result.d[2] = (mat1.d[2] * mat2.d[0]) + (mat1.d[5] * mat2.d[1]) + (mat1.d[8] * mat2.d[2]);
	result.d[5] = (mat1.d[2] * mat2.d[3]) + (mat1.d[5] * mat2.d[4]) + (mat1.d[8] * mat2.d[5]);
	result.d[8] = (mat1.d[2] * mat2.d[6]) + (mat1.d[5] * mat2.d[7]) + (mat1.d[8] * mat2.d[8]);

	return result;
}
