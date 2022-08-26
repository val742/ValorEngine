// Valor engine by Valores M.
// Written to handle GL Mathematics
#ifndef SKMATH_H
#define SKMATH_H
#include <vector>

float PI = 3.14159265f;

template<class skMath>
struct Vect3 {
	skMath x, y, z;
	Vect3(skMath x, skMath y, skMath z) : x(x), y(y), z(z) {}
	Vect3() {}
	Vect3<skMath>& operator=(Vect3<skMath> other) {
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	};
	static float lengthVect(Vect3<skMath> vect) {
		skMath length = sqrt((vect.x * vect.x) + (vect.y * vect.y) + (vect.z * vect.z));
		return length;
	};
};
template<class skMath>
struct Vect4 {
	skMath x, y, z, w;
	Vect4(skMath x, skMath y, skMath z, skMath w): x(x), y(y), z(z), w(w){}
	Vect4() {}
	Vect4<skMath>& operator=(Vect4<skMath> other) {
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		this->w = other.w;
		return *this;
	}
};
template<class skMath>
struct Mat4x4 {
	Vect4<skMath> row1, row2, row3, row4;
	Mat4x4() {
		row1 = Vect4<skMath>(1.0f, 0.0f, 0.0f, 0.0f);
		row2 = Vect4<skMath>(0.0f, 1.0f, 0.0f, 0.0f);
		row3 = Vect4<skMath>(0.0f, 0.0f, 1.0f, 0.0f);
		row4 = Vect4<skMath>(0.0f, 0.0f, 0.0f, 1.0f);
	}
	Mat4x4(const Mat4x4<skMath>& other) {
		this->row1 = other.row1;
		this->row2 = other.row2;
		this->row3 = other.row3;
		this->row4 = other.row4;
	}
	static Mat4x4<skMath> identityMatrix() {
		return Mat4x4<skMath>(
			Vect4<skMath>(1.0f, 0.0f, 0.0f, 0.0f),
			Vect4<skMath>(0.0f, 1.0f, 0.0f, 0.0f),
			Vect4<skMath>(0.0f, 0.0f, 1.0f, 0.0f),
			Vect4<skMath>(0.0f, 0.0f, 0.0f, 1.0f));
	}
	Mat4x4(Vect4<skMath> r1, Vect4<skMath> r2, Vect4<skMath> r3, Vect4<skMath> r4) {
		this->row1 = r1;
		this->row2 = r2;
		this->row3 = r3;
		this->row4 = r4;
	}
	static skMath toRad(GLfloat angle) {
		return angle * (PI / 180.0f);
	}
	static Mat4x4<skMath> perspective(GLfloat FoV, GLfloat aspectR, GLfloat near, GLfloat far) {
		skMath fn = far + near;
		skMath f_n = far - near;
		skMath t = 1.0f / (tan(toRad(FoV))) / 2.0f;

		return Mat4x4<skMath>(
			Vect4<skMath>(t / aspectR, 0.0f, 0.0f, 0.0f),
			Vect4<skMath>(0.0f, t, 0.0f, 0.0f),
			Vect4<skMath>(0.0f, 0.0f, -fn / f_n, -1.0f),
			Vect4<skMath>(0.0f, 0.0f, -2.0f * far * near / f_n, 0.0f));
	}
	static Mat4x4<skMath> addMat4(Mat4x4<skMath> mat1, Mat4x4<skMath> mat2) {
		Mat4x4<skMath> addedMat;
		addedMat.row1 = Vect4<skMath>(mat1.row1.x + mat2.row1.x, mat1.row1.y + mat2.row1.y, mat1.row1.z + mat2.row1.z, mat1.row1.w + mat2.row1.w);
		addedMat.row2 = Vect4<skMath>(mat1.row2.x + mat2.row2.x, mat1.row2.y + mat2.row2.y, mat1.row2.z + mat2.row2.z, mat1.row2.w + mat2.row2.w);
		addedMat.row3 = Vect4<skMath>(mat1.row3.x + mat2.row3.x, mat1.row3.y + mat2.row3.y, mat1.row3.z + mat2.row3.z, mat1.row3.w + mat2.row3.w);
		addedMat.row4 = Vect4<skMath>(mat1.row4.x + mat2.row4.x, mat1.row4.y + mat2.row4.y, mat1.row4.z + mat2.row4.z, mat1.row4.w + mat2.row4.w);
		return addedMat;
	}
	static Mat4x4<skMath> multMat4(Mat4x4<skMath>& mat1, Mat4x4<skMath>& mat2) {
		Mat4x4<skMath> result;
		result.row1.x = mat1.row1.x * mat2.row1.x + mat1.row1.y * mat2.row2.x + mat1.row1.z * mat2.row3.x + mat1.row1.w * mat2.row4.x;
		result.row1.y = mat1.row1.x * mat2.row1.y + mat1.row1.y * mat2.row2.y + mat1.row1.z * mat2.row3.y + mat1.row1.w * mat2.row4.y;
		result.row1.z = mat1.row1.x * mat2.row1.z + mat1.row1.y * mat2.row2.z + mat1.row1.z * mat2.row3.z + mat1.row1.w * mat2.row4.z;
		result.row1.w = mat1.row1.x * mat2.row1.w + mat1.row1.y * mat2.row2.w + mat1.row1.z * mat2.row3.w + mat1.row1.w * mat2.row4.w;
		result.row2.x = mat1.row2.x * mat2.row1.x + mat1.row2.y * mat2.row2.x + mat1.row2.z * mat2.row3.x + mat1.row2.w * mat2.row4.x;
		result.row2.y = mat1.row2.x * mat2.row1.y + mat1.row2.y * mat2.row2.y + mat1.row2.z * mat2.row3.y + mat1.row2.w * mat2.row4.y;
		result.row2.z = mat1.row2.x * mat2.row1.z + mat1.row2.y * mat2.row2.z + mat1.row2.z * mat2.row3.z + mat1.row2.w * mat2.row4.z;
		result.row2.w = mat1.row2.x * mat2.row1.w + mat1.row2.y * mat2.row2.w + mat1.row2.z * mat2.row3.w + mat1.row2.w * mat2.row4.w;
		result.row3.x = mat1.row3.x * mat2.row1.x + mat1.row3.y * mat2.row2.x + mat1.row3.z * mat2.row3.x + mat1.row3.w * mat2.row4.x;
		result.row3.y = mat1.row3.x * mat2.row1.y + mat1.row3.y * mat2.row2.y + mat1.row3.z * mat2.row3.y + mat1.row3.w * mat2.row4.y;
		result.row3.z = mat1.row3.x * mat2.row1.z + mat1.row3.y * mat2.row2.z + mat1.row3.z * mat2.row3.z + mat1.row3.w * mat2.row4.z;
		result.row3.w = mat1.row3.x * mat2.row1.w + mat1.row3.y * mat2.row2.w + mat1.row3.z * mat2.row3.w + mat1.row3.w * mat2.row4.w;
		result.row4.x = mat1.row4.x * mat2.row1.x + mat1.row4.y * mat2.row2.x + mat1.row4.z * mat2.row3.x + mat1.row4.w * mat2.row4.x;
		result.row4.y = mat1.row4.x * mat2.row1.y + mat1.row4.y * mat2.row2.y + mat1.row4.z * mat2.row3.y + mat1.row4.w * mat2.row4.y;
		result.row4.z = mat1.row4.x * mat2.row1.z + mat1.row4.y * mat2.row2.z + mat1.row4.z * mat2.row3.z + mat1.row4.w * mat2.row4.z;
		result.row4.w = mat1.row4.x * mat2.row1.w + mat1.row4.y * mat2.row2.w + mat1.row4.z * mat2.row3.w + mat1.row4.w * mat2.row4.w;

		return result;
	}
	static Mat4x4<skMath> scalingMat4(Mat4x4<skMath>& mat1, Vect4<skMath> scaleVec) {
		Mat4x4<skMath> tmp(mat1);
		tmp.row1.x *= scaleVec.x;
		tmp.row2.y *= scaleVec.y;
		tmp.row3.z *= scaleVec.z;
		return tmp;
	}
	static Mat4x4<skMath> translateMat4(Mat4x4<skMath>& mat1, Vect3<skMath> translateVec) {
		Mat4x4<skMath> temp(mat1);
		temp.row1.x += translateVec.x;
		temp.row2.y += translateVec.y;
		temp.row3.z += translateVec.z;
		return temp;
	}
	static Mat4x4<skMath> rotateMat4(Mat4x4<skMath>& mat1, GLfloat angle, Vect3<skMath> axisToRotate) {

		float theta = angle * (PI / 180.0f);

		Mat4x4<skMath> x_rotate = {
			Vect4<skMath>(axisToRotate.x, 0.0f, 0.0f, 0.0f),
			Vect4<skMath>(0.0f, cosf(theta) * axisToRotate.y, -sin(theta) * axisToRotate.z, 0.0f),
			Vect4<skMath>(0.0f, sin(theta) * axisToRotate.y, cosf(theta) * axisToRotate.z, 0.0f),
			Vect4<skMath>(0.0f, 0.0f, 0.0f, 1.0f)
		};
		Mat4x4<skMath> y_rotate = {
			Vect4<skMath>(cosf(theta) * axisToRotate.x, 0.0f, sin(theta) * axisToRotate.z, 0.0f),
			Vect4<skMath>(0.0f, axisToRotate.y, 0.0f, 0.0f),
			Vect4<skMath>(-sin(theta) * axisToRotate.x, 0.0f, cosf(theta) * axisToRotate.z, 0.0f),
			Vect4<skMath>(0.0f, 0.0f, 0.0f, 1.0f)
		};
		Mat4x4<skMath> z_rotate = {
			Vect4<skMath>(cosf(theta) * axisToRotate.x, -sin(theta) * axisToRotate.y, 0.0f, 0.0f),
			Vect4<skMath>(sin(theta) * axisToRotate.x, cosf(theta) * axisToRotate.y, 0.0f, 0.0f),
			Vect4<skMath>(0.0f, 0.0f, axisToRotate.z, 0.0f),
			Vect4<skMath>(0.0f, 0.0f, 0.0f, 1.0f)
		};
	}
	std::vector<skMath> getRawData() const {
		return{
			row1.x,row1.y,row1.z,row1.w,
			row2.x,row2.y,row2.z,row2.w,
			row3.x,row3.y,row3.z,row3.w,
			row4.x,row4.y,row4.z,row4.w
		};
	}
};

template <class skMath>
struct Quaternion {
	Vect4<skMath> q;
	Vect3<skMath> p;
	Quaternion() {
		q = Vect4<skMath>(0.0f, 0.0f, 0.0f, 1.0f);
		p = Vect3<skMath>(0.0f, 0.0f, 0.0f);
	}
	Quaternion(const Quaternion<skMath>& other) {
		this->q = other.q;
		this->p = other.p;
	}
	static skMath squ(skMath s) {
		skMath a = s * s;
		return a;
	}
	static Quaternion<skMath> mult(Quaternion<skMath>& q1) {
		Quaternion<skMath> temp;
		temp.q.w = 1;
		temp.q.x = (q1.p.x * squ(q1.q.w) + q1.p.x * squ(q1.q.x) - q1.p.x * squ(q1.q.y) - q1.p.x * squ(q1.q.z)) + ((2 * q1.p.y) * q1.q.x * q1.q.y - (2 * q1.p.y) * q1.q.w * q1.q.z) + ((2 * q1.p.z) * q1.q.w * q1.q.y + (2 * q1.p.z) * q1.q.x * q1.q.z);
		temp.q.y = ((2 * q1.p.x) * q1.q.w * q1.q.z + (2 * q1.p.x) * q1.q.x * q1.q.y) + (q1.p.y * squ(q1.q.w) - q1.p.y * squ(q1.q.x) + q1.p.y * squ(q1.q.y) - q1.p.y * squ(q1.q.z)) + ((2 * q1.p.z) * q1.q.y * q1.q.z + (2 * q1.p.z) * q1.q.w * q1.q.x);
		temp.q.z = ((2 * q1.p.x) * q1.q.x * q1.q.z - (2 * q1.p.x) * q1.q.w * q1.q.y) + ((2 * q1.p.y) * q1.q.w * q1.q.x + (2 * q1.p.y) * q1.q.y * q1.q.z) + (q1.p.z * squ(q1.q.w) - q1.p.z * squ(q1.q.x) - q1.p.z * squ(q1.q.y) + q1.p.z * squ(q1.q.z));

		return temp;
	}
	static Quaternion<skMath> normalize(Vect4<skMath>& q1) {
		float m = sqrt(squ(q1.w) + squ(q1.x) + squ(q1.y) + squ(q1.z));
		q1.w = m;
		q1.x = m;
		q1.y = m;
		q1.z = m;
		return q1;
	}
	static Mat4x4<skMath> scalar(Mat4x4<skMath>& mat1, skMath scNum) {
		Mat4x4<skMath> tmp(mat1);
		tmp.row1.x *= scNum;
		tmp.row1.y *= scNum;
		tmp.row1.z *= scNum;

		tmp.row2.x *= scNum;
		tmp.row2.y *= scNum;
		tmp.row2.z *= scNum;

		tmp.row3.z *= scNum;
		tmp.row3.y *= scNum;
		tmp.row3.z *= scNum;
		return tmp;
	}
	static Mat4x4<skMath> quatToMat(Quaternion<skMath>& rotA) {
		float x1 = squ(rotA.q.w) + squ(rotA.q.x) - 0.5f;
		float x2 = rotA.q.x * rotA.q.y - rotA.q.w * rotA.q.z;
		float x3 = rotA.q.w * rotA.q.y + rotA.q.x * rotA.q.z;

		float y1 = rotA.q.w * rotA.q.z + rotA.q.x * rotA.q.y;
		float y2 = squ(rotA.q.w) + squ(rotA.q.y) - 0.5f;
		float y3 = rotA.q.y * rotA.q.z - rotA.q.w * rotA.q.x;

		float z1 = rotA.q.x * rotA.q.z - rotA.q.w * rotA.q.y;
		float z2 = rotA.q.w * rotA.q.x + rotA.q.y * rotA.q.z;
		float z3 = squ(rotA.q.w) + squ(rotA.q.z) - 0.5f;
		// may need *2
		Mat4x4<skMath> rotM = {
			Vect4<skMath>(x1,   x2,   x3, 0.0f),
			Vect4<skMath>(y1,   y2,   y3, 0.0f),
			Vect4<skMath>(z1,   z2,   z3, 0.0f),
			Vect4<skMath>(0.0f, 0.0f, 0.0f, 1.0f)
		};
		return rotM;
	}
	static Quaternion<skMath> matToQuat(Mat4x4<skMath>& mat1) {
		Quaternion<skMath> temp;
		float trcM = (4 * squ(mat1.row4.w)) - 1;
		temp.q.w = sqrt((trcM + 1) / 4);
		temp.q.x = sqrt(mat1.row1.x / 2) + ((1 - trcM) / 4);
		temp.q.y = sqrt(mat1.row2.y / 2) + ((1 - trcM) / 4);
		temp.q.z = sqrt(mat1.row3.z / 2) + ((1 - trcM) / 4);
		return temp;
	}
	static Quaternion<skMath> eAngToQuat(Vect3<skMath> axis, GLfloat angle) {
		Quaternion<skMath> temp;
		if (axis.x != 0.0f) {
			angle *= axis.x;
			temp.p.x = cosf(angle / 2) + sinf(angle / 2);
		}
		if (axis.y != 0.0f){
			angle *= axis.y;
			temp.p.y = cosf(angle / 2) + sin(angle / 2);
		}
		if (axis.z != 0.0f) {
			angle *= axis.z;
			temp.p.z = cosf(angle / 2) + sin(angle / 2);
		}
		return temp;
	}
	static Mat4x4<skMath> rotate(Mat4x4<skMath>& mat1, GLfloat rAngle, Vect3<skMath> rotA) {
		rAngle = rAngle * (PI / 180.0f);
		Mat4x4<skMath> mat = Mat4x4<skMath>::identityMatrix();
		Quaternion<skMath> q = matToQuat(mat);
		Quaternion<skMath> p = eAngToQuat(rotA, rAngle);
		
		q.p = p.p;
		q = mult(q);
		Mat4x4<skMath> fMat = quatToMat(q);
		fMat = Mat4x4<skMath>::multMat4(mat1, fMat);
		return fMat;
	}
};
#endif // !SKMATH_H