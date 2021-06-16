#include "pch.h"
#include "CppUnitTest.h"

#include "../glut_Intro/Vector3d.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace glutIntroTests
{
	TEST_CLASS(VectorTests)
	{
	public:
		
		TEST_METHOD(VectorAddition)
		{
			Vector3d v1(1.0f, 1.0f, 0.0f);
			Vector3d v2(1.0f, 0.0f, 0.0f);

			Vector3d v3 = v1 + v2;
			Vector3d v4 = v1 - v2;

			Assert::AreEqual(v3.X(), 2.0f);
			Assert::AreEqual(v3.Y(), 1.0f);
			Assert::AreEqual(v3.Z(), 0.0f);

			Assert::AreEqual(v4.X(), 0.0f);
			Assert::AreEqual(v4.Y(), 1.0f);
			Assert::AreEqual(v4.Z(), 0.0f);
		}

		TEST_METHOD(ScalarMultiplication)
		{
			Vector3d v1(1.0f, 2.0f, 3.0f);
			Vector3d v2 = 2.0f * v1;

			Assert::AreEqual(v2.X(), 2.0f);
			Assert::AreEqual(v2.Y(), 4.0f);
			Assert::AreEqual(v2.Z(), 6.0f);
		}
	};
}
