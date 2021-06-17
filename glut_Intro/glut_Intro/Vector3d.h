#pragma once

#include<vector>
#include<stdexcept>

class Vector3d
{
	public:
		static Vector3d zero() { return Vector3d(0.0f, 0.0f, 0.0f); };
		static Vector3d up() { return Vector3d(0.0f, 1.0f, 0.0f); };
		static Vector3d down() { return Vector3d(0.0f, -1.0f, 0.0f); };
		static Vector3d right() { return Vector3d(1.0f, 0.0f, 0.0f); };
		static Vector3d left() { return Vector3d(-1.0f, 0.0f, 0.0f); };
		static Vector3d back() { return Vector3d(0.0f, 0.0f, 1.0f); };
		static Vector3d forward() { return Vector3d(0.0f, 0.0f, -1.0f); };

		Vector3d(float x, float y, float z);

		float X() const { return x; };
		float Y() const { return y; };
		float Z() const { return z; };

		friend Vector3d operator*(const float& value, const Vector3d& target)
		{
			return Vector3d(target.x * value, target.y * value, target.z * value);
		}

		Vector3d operator+(const Vector3d& other) const;
		Vector3d operator-(const Vector3d& other) const;

		bool Equals(const std::vector<float>& other) const {
			if (other.size() != 3)
				throw std::invalid_argument("other must have size 3.");

			return x == other[0] && y == other[1] && z == other[2];
		}

	private:
		float x;
		float y;
		float z;
};

