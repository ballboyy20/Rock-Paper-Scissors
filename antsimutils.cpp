#include "antsimutils.h"
#include <cmath>

double convert_to_radians(double angleInDegrees)
{
    double PI{3.14159};
    return (angleInDegrees*(PI/180.0));
}

double calculate_clockwise_alignment_angle_degrees(const Eigen::Vector2d from, Eigen::Vector2d to)
{
    double PI{3.14159};
    double det = from[0]*to[1] - from[1]*to[0];
    double d = from.dot(to);
    double clockwiseAngle = std::atan2(-det,-d)+PI;
    return clockwiseAngle * (180.0/PI);
}

void rotate_vector(Eigen::Vector2d &vector_to_be_rotated, double angleInDegrees)
{
    int x{0};
    int y{1};

    double angleInRadians{convert_to_radians(angleInDegrees)};

    double newX{vector_to_be_rotated[x] * cos(angleInRadians) - vector_to_be_rotated[y] * sin(angleInRadians)};
    double newY{vector_to_be_rotated[x] * sin(angleInRadians) + vector_to_be_rotated[y] * cos(angleInRadians)};

    vector_to_be_rotated[x] = newX;
    vector_to_be_rotated[y] = newY;
}

Eigen::Vector2d create_orientaion(double angleInDegrees)
{
    Eigen::Vector2d newOrientation{{0.0,0.0}};
    double angleInRadians{convert_to_radians(angleInDegrees)};
    newOrientation[0] = cos(angleInRadians);
    newOrientation[1] = sin(angleInRadians);
    return newOrientation;
}


bool check_two_points(double firstX, double firstY, double secondX, double secondY, int tolerance)
{
    if ( (abs(firstX - secondX) <= tolerance) && (abs(firstY-secondY) <= tolerance))
        return true;
    else
        return false;
}

bool are_these_points_near_eachother(Eigen::Vector2d firstCor, Eigen::Vector2d secondCor, int tolerance)
{
    if ( (abs(firstCor[0] - secondCor[0]) <= tolerance) && (abs(firstCor[1]-secondCor[1]) <= tolerance))
        return true;
    else
        return false;
}

bool are_these_points_near_eachother(Eigen::Vector2d firstCor, double secondCor, int tolerance)
{
    if ( (abs(firstCor[0] - secondCor) <= tolerance) && (abs(firstCor[1]-secondCor) <= tolerance))
        return true;
    else
        return false;
}

bool is_ant_near_edge(Eigen::Vector2d &antLocation, int limit)
{
    int bounceFactor{2};
    int xCor{0};
    int yCor{1};

    if (antLocation[xCor] >= limit)
    {
        antLocation[xCor] = limit - bounceFactor;
        return true;
    }

    if (antLocation[yCor] >= limit)
    {
        antLocation[yCor] = limit - bounceFactor;
        return true;
    }

    if (antLocation[xCor] <= 0.0)
    {
        antLocation[xCor] = bounceFactor;
        return true;
    }

    if (antLocation[yCor] <= 0.0)
    {
        antLocation[yCor] = bounceFactor;
        return true;
    }

    else
    {
        return false;
    }
}
