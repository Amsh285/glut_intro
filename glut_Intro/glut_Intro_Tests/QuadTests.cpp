#include "pch.h"
#include "CppUnitTest.h"

#include "../glut_Intro/Vector3d.h"
#include "../glut_Intro/Vector3dMatrix.h"
#include "../glut_Intro/Quad.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace glutIntroTests
{
	TEST_CLASS(QuadTests)
	{
	public:

		TEST_METHOD(QuadFulcrum)
		{
			Quad q1(2.0f, 2.0f, 2.0f);
			Quad q2(50.0f, 1.0f, 50.0f);
			Vector3d fulcrum1 = q1.fulcrum();
			Vector3d fulcrum2 = q2.fulcrum();

			Assert::AreEqual(fulcrum1.X(), 1.0f);
			Assert::AreEqual(fulcrum1.Y(), 1.0f);
			Assert::AreEqual(fulcrum1.Z(), 1.0f);

			Assert::AreEqual(fulcrum2.X(), 25.0f);
			Assert::AreEqual(fulcrum2.Y(), 0.5f);
			Assert::AreEqual(fulcrum2.Z(), 25.0f);
		}

		TEST_METHOD(QuadVerticesFrontSide)
		{
			Quad q1(2.0f, 2.0f, 2.0f);
			std::vector<Vector3d> vertices = q1.getQuadVertices();
			Vector3d leftBottom = vertices[0];
			Vector3d rightBottom = vertices[1];
			Vector3d rightTop = vertices[2];
			Vector3d leftTop = vertices[3];

			Assert::IsTrue(leftBottom.Equals({-1.0f, -1.0f, 1.0f}));
			Assert::IsTrue(rightBottom.Equals({1.0f, -1.0f, 1.0f}));
			Assert::IsTrue(rightTop.Equals({1.0f, 1.0f, 1.0f}));
			Assert::IsTrue(leftTop.Equals({-1.0f, 1.0f, 1.0f}));
		}

		TEST_METHOD(QuadVerticesRightSide)
		{
			Quad q1(2.0f, 2.0f, 2.0f);
			std::vector<Vector3d> vertices = q1.getQuadVertices();

			Vector3d frontRightBottom = vertices[4];
			Vector3d backRightBottom = vertices[5];
			Vector3d backRightTop = vertices[6];
			Vector3d frontRightTop = vertices[7];

			Assert::IsTrue(frontRightBottom.Equals({1.0f, -1.0f, 1.0f}));
			Assert::IsTrue(backRightBottom.Equals({ 1.0f, -1.0f, -1.0f }));
			Assert::IsTrue(backRightTop.Equals({ 1.0f, 1.0f, -1.0f }));
			Assert::IsTrue(frontRightTop.Equals({ 1.0f, 1.0f, 1.0f }));
		}

		TEST_METHOD(QuadVertivesUpSide)
		{
			Quad q1(2.0f, 2.0f, 2.0f);
			std::vector<Vector3d> vertices = q1.getQuadVertices();

			Vector3d frontLeftTop = vertices[8];
			Vector3d frontRightTop = vertices[9];
			Vector3d backRightTop = vertices[10];
			Vector3d backLeftTop = vertices[11];

			Assert::IsTrue(frontLeftTop.Equals({-1.0f, 1.0f, 1.0f}));
			Assert::IsTrue(frontRightTop.Equals({ 1.0f, 1.0f, 1.0f }));
			Assert::IsTrue(backRightTop.Equals({ 1.0f, 1.0f, -1.0f }));
			Assert::IsTrue(backLeftTop.Equals({ -1.0f, 1.0f, -1.0f }));
		}

		TEST_METHOD(QuadVerticesBackSide)
		{
			Quad q1(2.0f, 2.0f, 2.0f);
			std::vector<Vector3d> vertices = q1.getQuadVertices();

			Vector3d backLeftBottom = vertices[12];
			Vector3d backRightBottom = vertices[13];
			Vector3d backRightTop = vertices[14];
			Vector3d backLeftTop = vertices[15];

			Assert::IsTrue(backLeftBottom.Equals({-1.0f, -1.0f, -1.0f}));
			Assert::IsTrue(backRightBottom.Equals({ 1.0f, -1.0f, -1.0f }));
			Assert::IsTrue(backRightTop.Equals({ 1.0f, 1.0f, -1.0f }));
			Assert::IsTrue(backLeftTop.Equals({ -1.0f, 1.0f, -1.0f }));
		}

		TEST_METHOD(QuadVerticesLeftSide)
		{
			Quad q1(2.0f, 2.0f, 2.0f);
			std::vector<Vector3d> vertices = q1.getQuadVertices();

			Vector3d frontleftBottom = vertices[16];
			Vector3d backLeftBottom = vertices[17];
			Vector3d backLeftTop = vertices[18];
			Vector3d frontLeftTop = vertices[19];

			Assert::IsTrue(frontleftBottom.Equals({-1.0f, -1.0f, 1.0f}));
			Assert::IsTrue(backLeftBottom.Equals({ -1.0f, -1.0f, -1.0f }));
			Assert::IsTrue(backLeftTop.Equals({ -1.0f, 1.0f, -1.0f }));
			Assert::IsTrue(frontLeftTop.Equals({ -1.0f, 1.0f, 1.0f }));
		}

		TEST_METHOD(QuadVerticesDownSide)
		{
			Quad q1(2.0f, 2.0f, 2.0f);
			std::vector<Vector3d> vertices = q1.getQuadVertices();

			Vector3d frontLeftBottom = vertices[20];
			Vector3d frontRightBottom = vertices[21];
			Vector3d backRightBottom = vertices[22];
			Vector3d backLeftBottom = vertices[23];

			Assert::IsTrue(frontLeftBottom.Equals({-1.0f, -1.0f, 1.0f}));
			Assert::IsTrue(frontRightBottom.Equals({ 1.0f, -1.0f, 1.0f }));
			Assert::IsTrue(backRightBottom.Equals({ 1.0f, -1.0f, -1.0f }));
			Assert::IsTrue(backLeftBottom.Equals({ -1.0f, -1.0f, -1.0f }));
		}
	};
}
