#include "Geometry.h"

std::vector<Vector3d> Geometry::rotateX(const std::vector<Vector3d>& source, const float& angle)
{
    return rotate(source, Vector3dMatrix::rotationX(angle));
}

std::vector<Vector3d> Geometry::rotateY(const std::vector<Vector3d>& source, const float& angle)
{
    return rotate(source, Vector3dMatrix::rotationY(angle));
}

std::vector<Vector3d> Geometry::rotateZ(const std::vector<Vector3d>& source, const float& angle)
{
    return rotate(source, Vector3dMatrix::rotationZ(angle));
}

std::vector<Vector3d> Geometry::rotate(
    const std::vector<Vector3d>& source,
    const Vector3dMatrix& rotationMatrix)
{
    std::vector<Vector3d> result;

    for (size_t i = 0; i < source.size(); i++)
    {
        Vector3d rotatedVector = rotationMatrix * source[i];
        result.push_back(rotatedVector);
    }

    return result;
}
