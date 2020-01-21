#include "Matrix3.h"

	// Constructor 1 create a zero matrix
	Matrix3::Matrix3()
	{
		A11 = 0.0;
		A12 = 0.0;
		A13 = 0.0;
		A21 = 0.0;
		A22 = 0.0;
		A23 = 0.0;
		A31 = 0.0;
		A32 = 0.0;
		A33 = 0.0;
	}

	// Constructor 2
	Matrix3::Matrix3(Vector3 Row1, Vector3 Row2, Vector3 Row3)
	{  // To allow 3 rows of vectors to be declared as a matrix
		A11 = Row1.x;
		A12 = Row1.y;
		A13 = Row1.z;
		A21 = Row2.x;
		A22 = Row2.y;
		A23 = Row2.z;
		A31 = Row3.x;
		A32 = Row3.y;
		A33 = Row3.z;
	}
	// Constructor 3
	Matrix3::Matrix3(double _A11, double _A12, double _A13,
		double _A21, double _A22, double _A23,
		double _A31, double _A32, double _A33)
	{// to allow nine double values
		A11 = _A11;
		A12 = _A12;
		A13 = _A13;
		A21 = _A21;
		A22 = _A22;
		A23 = _A23;
		A31 = _A31;
		A32 = _A32;
		A33 = _A33;
	}

	Vector3 Matrix3::operator *(Vector3 V1) const
	{// An overloaded operator * to return the  product of the matrix by a vector
		return { A11 * V1.x + A12 * V1.y + A13 * V1.z,
			A21 * V1.x + A22 * V1.y + A23 * V1.z,
			A31 * V1.x + A32 * V1.y + A33 * V1.z };
	}

	Matrix3 Matrix3::Transpose(Matrix3 M1) const
	{// a method to transpose a given matrix
		return  Matrix3(M1.A11, M1.A21, M1.A31,
			M1.A12, M1.A22, M1.A32,
			M1.A13, M1.A23, M1.A33);
	}
	Matrix3 Matrix3::operator +(Matrix3 M2) const
	{// An overloaded operator + to return the  sum of two matrix 
		return  Matrix3(A11 + M2.A11, A12 + M2.A12, A13 + M2.A13,
			A21 + M2.A21, A22 + M2.A22, A23 + M2.A23,
			A31 + M2.A31, A32 + M2.A32, A33 + M2.A33);
	}
	Matrix3 Matrix3::operator -(Matrix3 M2) const
	{// An overloaded operator * to return the  difference of two matrix
		return  Matrix3(A11 - M2.A11, A12 - M2.A12, A13 - M2.A13,
			A21 - M2.A21, A22 - M2.A22, A23 - M2.A23,
			A31 - M2.A31, A32 - M2.A32, A33 - M2.A33);
	}

	Matrix3 Matrix3::operator*(double x) const
	{// An overloaded operator * to return the  product of the matrix by a scalar
		Matrix3 answer = Matrix3();
		answer.A11 = A11 * x;
		answer.A12 = A12 * x;
		answer.A13 = A13 * x;

		answer.A21 = A21 * x;
		answer.A22 = A22 * x;
		answer.A23 = A23 * x;

		answer.A31 = A31 * x;
		answer.A32 = A32 * x;
		answer.A33 = A33 * x;

		return answer;
	}

	Matrix3 Matrix3::operator *(Matrix3 M2) const
	{// An overloaded operator * to return the  product of two matrix
		Matrix3 answer;

		answer.A11 = Row(0) * M2.Column(0);
		answer.A12 = Row(0) * M2.Column(1);
		answer.A13 = Row(0) * M2.Column(2);

		answer.A21 = Row(1) * M2.Column(0);
		answer.A22 = Row(1) * M2.Column(1);
		answer.A23 = Row(1) * M2.Column(2);
		

		answer.A31 = Row(2) * M2.Column(0);
		answer.A32 = Row(2) * M2.Column(1);
		answer.A33 = Row(2) * M2.Column(2);


		return answer;
	}


	double Matrix3::Determinant(Matrix3 M1) const
	{// method to return the determinant of a 3x3 matrix
		//                     aei      -     ahf                  + dhc                     - gec                      +    gbh                    -     dbi   
		return M1.A11 * M1.A22 * M1.A33 - M1.A11 * M1.A32 * M1.A23 + M1.A21 * M1.A32 * M1.A13 - M1.A31 * M1.A22 * M1.A13 + M1.A31 * M1.A12 * M1.A23 - M1.A21 * M1.A12 * M1.A33;
	}

	Vector3 Matrix3::Row(int i) const
	{
		// a method to return as Row as vector3 0 == first row, default == last row
		switch (i)
		{
		case 0:
			return  { A11, A12, A13 };
		case 1:
			return  { A21, A22, A23 };
		case 2:
		default:
			return  { A31, A32, A33 };
		}
	}
	
	Vector3 Matrix3::Column(int i) const
	{// a method to return as column as vector3 0 == first column, default == last column
		switch (i)
		{
		case 0:
			return { A11, A21, A31 };
		case 1:
			return { A12, A22, A32 };
		case 2:
		default:
			return { A13, A23, A33 };
		}
	}


	Matrix3 Matrix3::Inverse(Matrix3 M1) const
	{
		// method to return the inverse of a matrix if exists else zero vector
		double det = Determinant(M1);
		if (det == 0)
			return  Matrix3();
		else
		{
			double scale = 1 / det;
			Matrix3 answer = Matrix3();
			answer.A11 = scale * (M1.A22 * M1.A33 - M1.A23 * M1.A32); // ei-fh
			answer.A12 = scale * (M1.A13 * M1.A32 - M1.A12 * M1.A33); // ch-bi
			answer.A13 = scale * (M1.A12 * M1.A23 - M1.A13 * M1.A22); // ch-bi

			answer.A21 = scale * (M1.A23 * M1.A31 - M1.A21 * M1.A33); // fg-di
			answer.A22 = scale * (M1.A11 * M1.A33 - M1.A13 * M1.A31); // ai-cg
			answer.A23 = scale * (M1.A13 * M1.A21 - M1.A11 * M1.A23); // cd-af


			answer.A31 = scale * (M1.A21 * M1.A32 - M1.A22 * M1.A31); // dh-eg
			answer.A32 = scale * (M1.A12 * M1.A31 - M1.A11 * M1.A32); // bg-ah
			answer.A33 = scale * (M1.A11 * M1.A22 - M1.A12 * M1.A21); // ae-bd

			return answer;
		}

	}

	Matrix3 Matrix3::Rotation(int _angle) const
	{
		double radians = PI / 180 * _angle;
		Matrix3 answer;
		answer.A11 = cos(radians);
		answer.A12 = sin(radians);
		answer.A13 = 0;
		answer.A21 = -sin(radians);
		answer.A22 = cos(radians);
		answer.A23 = 0;
		answer.A31 = 0;
		answer.A32 = 0;
		answer.A33 = 1;

		return answer;
	}


	Matrix3 Matrix3::Translate(float dx, float dy)
	{
		Matrix3 answer;
		answer.A11 = 1;
		answer.A12 = 0;
		answer.A13 = dx;
		answer.A21 = 0;
		answer.A22 = 1;
		answer.A23 = dy;
		answer.A31 = 0;
		answer.A32 = 0;
		answer.A33 = 1;

		return answer;
	}

	Matrix3 Matrix3::Scale(int dx, int dy)
	{
		Matrix3 answer;
		answer.A11 = (double)dx / 100;
		answer.A12 = 0;
		answer.A13 = 0;
		answer.A21 = 0;
		answer.A22 = (double)dy / 100;
		answer.A23 = 0;
		answer.A31 = 0;
		answer.A32 = 0;
		answer.A33 = 1;

		return answer;
	}

	Matrix3 Matrix3::operator -() const
	{
		Matrix3 answer(A11, A21, A31,
			A12, A22, A32,
			A13, A23, A33);

		return answer * (-1.0);
	}

	Matrix3 Matrix3::RotationX(float _angle)
	{
		double radians = PI / 180 * _angle;
		Matrix3 answer;
		answer.A11 = 1;
		answer.A12 = 0;
		answer.A13 = 0;
		answer.A21 = 0;
		answer.A22 = cos(radians);
		answer.A23 = -sin(radians);
		answer.A31 = 0;
		answer.A32 = sin(radians);
		answer.A33 = cos(radians);

		return answer;
	}
	Matrix3 Matrix3::RotationY(float _angle) 
	{
		double radians = PI / 180 * _angle;
		Matrix3 answer;
		answer.A11 = cos(radians);
		answer.A12 = 0;
		answer.A13 = sin(radians);
		answer.A21 = 0;
		answer.A22 = 1;
		answer.A23 = 0;
		answer.A31 = -sin(radians);
		answer.A32 = 0;
		answer.A33 = cos(radians);

		return answer;
	}
	 Matrix3 Matrix3::RotationZ(float _angle)
	{
		double radians = PI / 180 * _angle;
		Matrix3 answer;
		answer.A11 = cos(radians);
		answer.A12 = -sin(radians);
		answer.A13 = 0;
		answer.A21 = sin(radians);
		answer.A22 = cos(radians);
		answer.A23 = 0;
		answer.A31 = 0;
		answer.A32 = 0;
		answer.A33 = 1;

		return answer;
	}

	Matrix3 Matrix3::Scale3D(int dx)
	{
		Matrix3 answer;
		answer.A11 = (double)dx / 100;
		answer.A12 = 0;
		answer.A13 = 0;
		answer.A21 = 0;
		answer.A22 = (double)dx / 100;
		answer.A23 = 0;
		answer.A31 = 0;
		answer.A32 = 0;
		answer.A33 = (double)dx / 100;

		return answer;
	}

	//return the given matrix as a string
	std::string Matrix3::toString() const
	{
		std::string matrix = "( " + std::to_string(A11) + ", " + std::to_string(A12) + ", " + std::to_string(A13) + " ) \n"
			"( " + std::to_string(A21) + ", " + std::to_string(A22) + ", " + std::to_string(A23) + " ) \n"
			"( " + std::to_string(A31) + ", " + std::to_string(A32) + ", " + std::to_string(A33) + " ]";
		return matrix;
	}
