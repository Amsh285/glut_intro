#include "pch.h"
#include "CppUnitTest.h"

#include "../glut_Intro/Vector3d.h"
#include "../glut_Intro/Vector3dMatrix.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace glutIntroTests
{
	TEST_CLASS(Vector3dMatrixTests)
	{
	public:

		TEST_METHOD(MatrixVectorMultiplicationIdentity)
		{
			Vector3d v1(1.0f, 1.0f, 0.0f);
			Vector3dMatrix m1 = Vector3dMatrix::identity();

			Vector3d v2 = m1 * v1;

			Assert::AreEqual(v2.X(), 1.0f);
			Assert::AreEqual(v2.Y(), 1.0f);
			Assert::AreEqual(v2.Z(), 0.0f);
		}

		TEST_METHOD(MatrixVectorMultiplication)
		{
			Vector3d col(1.0f, 1.0f, 1.0f);
			Vector3dMatrix m1(col, col, col);

			Vector3d v1 = m1 * Vector3d(1.0f, 0.0f, 0.0f);
			Vector3d v2 = m1 * Vector3d(1.0f, 1.0f, 0.0f);
			Vector3d v3 = m1 * Vector3d(1.0f, 1.0f, 1.0f);

			Assert::AreEqual(v1.X(), 1.0f);
			Assert::AreEqual(v1.Y(), 1.0f);
			Assert::AreEqual(v1.Z(), 1.0f);

			Assert::AreEqual(v2.X(), 2.0f);
			Assert::AreEqual(v2.Y(), 2.0f);
			Assert::AreEqual(v2.Z(), 2.0f);

			Assert::AreEqual(v3.X(), 3.0f);
			Assert::AreEqual(v3.Y(), 3.0f);
			Assert::AreEqual(v3.Z(), 3.0f);
		}

		TEST_METHOD(MatrixScalarMultiplication)
		{
			Vector3d col(1.0f, 1.0f, 1.0f);
			Vector3dMatrix m1(col, col, col);

			Vector3dMatrix m2 = 2.0f * m1;
			Vector3d col1 = m2.Col1();
			Vector3d col2 = m2.Col2();
			Vector3d col3 = m2.Col3();
			
			Assert::AreEqual(col1.X(), 2.0f);
			Assert::AreEqual(col1.Y(), 2.0f);
			Assert::AreEqual(col1.Z(), 2.0f);

			Assert::AreEqual(col2.X(), 2.0f);
			Assert::AreEqual(col2.Y(), 2.0f);
			Assert::AreEqual(col2.Z(), 2.0f);

			Assert::AreEqual(col3.X(), 2.0f);
			Assert::AreEqual(col3.Y(), 2.0f);
			Assert::AreEqual(col3.Z(), 2.0f);
		}
	};
}
