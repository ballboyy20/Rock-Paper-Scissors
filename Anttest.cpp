#include "gtest/gtest.h"
#include "random.h"
#include "ant.h"
#include "antsimutils.h"
#include <Eigen/Dense>

double testingTolerance{1e-2};



class NonRandomGenerator: public Random
{

public:
    NonRandomGenerator(double numberToReturn);
    virtual double get_random_number(double minValue, double maxValue);

protected:
    double nonRandomNumber{0};
};

NonRandomGenerator::NonRandomGenerator(double numberToReturn):nonRandomNumber{numberToReturn}
{
}

double NonRandomGenerator::get_random_number(double minValue, double maxValue)
{
    return nonRandomNumber;
}

class AntSpy: public Ant
{

public:


    void move_ant_location_nonrandom()
    {
        this->rotate_orientation();

        antPosition = antPosition + antOrientation;
    }

    void set_random_angle(double nonRandomNumber)
    {
        nonRandomNumber = convert_to_radians(nonRandomNumber);
        this->randomAngle = nonRandomNumber;
    }

    double get_initial_position()
    {
        return initialPosition;
    }

protected:

};

//TEST(AntTest1, GivenAnAnt_WhenCheckingToSeeIfTheAntIsMoving_ExpectAntXLocationToHaveChanged)
//{
//    PheromoneMap testingPheromoneMap;
//    FoodMap testingFoodMap;
//    AntSpy testingAnt(testingPheromoneMap,testingFoodMap);



//    EXPECT_TRUE(testingAnt.get_ant_x_coordinate() == testingAnt.get_initial_position());

//    testingAnt.move_ant_location();

//    EXPECT_TRUE(testingAnt.get_ant_x_coordinate() != testingAnt.get_initial_position());
//}

//TEST(AntTest2, GivenAnAnt_WhenCheckingToSeeIfTheAntIsMoving_ExpectAntYLocationToHaveChanged)
//{
//    AntSpy testingAnt;

//    EXPECT_TRUE(testingAnt.get_ant_y_coordinate() ==  testingAnt.get_initial_position());

//    testingAnt.move_ant_location();

//    EXPECT_TRUE(testingAnt.get_ant_y_coordinate() != testingAnt.get_initial_position());
//}


TEST(UtilsTest, GivenAnAngleInDegrees_WhenCheckingToSeeIfTheFunctinoCreatesA2dVectorPointingAtGivenAngle_Expect2DVectorToPointAtGivenAngle)
{
    double angleInDegrees{90.0};
    Eigen::Vector2d testingVector{{0.0,0.0}};
    testingVector = create_orientaion(angleInDegrees);
    EXPECT_NEAR(testingVector[0], 0.0, testingTolerance);
    EXPECT_NEAR(testingVector[1], 1.0, testingTolerance);
}

TEST(UtilsTest2, GivenAnAngleInDegrees_WhenCheckingToSeeIfTheFunctinoCreatesA2dVectorPointingAtGivenAngle_Expect2DVectorToPointAtGivenAngle)
{
    double angleInDegrees{270.0};
    Eigen::Vector2d testingVector{{0.0,0.0}};
    testingVector = create_orientaion(angleInDegrees);
    EXPECT_NEAR(testingVector[0], 0.0, testingTolerance);
    EXPECT_NEAR(testingVector[1], -1.0, testingTolerance);
}

TEST(UtilsTest3, GivenAVectorLocationAndALimit_WhenCheckingToSeeIfTheVectorLocationIsOutSideTheLimit_ExpectFunctionToReturnTrueAndChangeCoordianteOfVector)
{
    Eigen::Vector2d testingVector{{-1.0,5.0}};
    int limit{10};
    EXPECT_TRUE(is_ant_near_edge(testingVector,limit));
    testingVector[1] = limit - 1;
    testingVector[0] = limit - 1;
    EXPECT_FALSE(is_ant_near_edge(testingVector,limit));
    testingVector[1] = limit + 1;
    testingVector[0] = limit + 1;
    EXPECT_TRUE(is_ant_near_edge(testingVector,limit));
}

TEST(VectorRotatingTest, GivenA2DVectorAt90DegreesOnTheUnitCircle_WhenCheckingToSeeIfItRotatesByPositive90Degrees_ExpectTheVectorToHaveBePointingLeftOnUnitCircle)
{

    Eigen::Vector2d testingOrientation{{0.0,0.0}};
    double angleRotation{90.0};
    testingOrientation = create_orientaion(angleRotation);

    rotate_vector(testingOrientation, angleRotation);

    EXPECT_NEAR(testingOrientation[0], -1.0, testingTolerance);
}

TEST(VectorRotatingTest2, GivenA2DVectorAt45DegreesOnTheUnitCircle_WhenCheckingToSeeIfItRotatesByPositive90Degrees_ExpectTheVectorToHaveBePointing45DegreesFromStraightUp)
{

    Eigen::Vector2d testingOrientation{{0.0,0.0}};
    double angleRotation{90.0};
    double initialAngle{45.0};
    testingOrientation = create_orientaion(initialAngle);

    rotate_vector(testingOrientation, angleRotation);

    EXPECT_NEAR(testingOrientation[0], -0.707106, testingTolerance);
    EXPECT_NEAR(testingOrientation[1], 0.707106, testingTolerance);
}

TEST(AntMotionTest1, GivenA2DVectorAtZeroDegreesOnTheUnitCircle_WhenCheckingToSeeIfItRotatesByPositive90Degrees_ExpectTheVectorToHaveBePointingStraightUpMeaningYOrientationIs1)
{

    Eigen::Vector2d testingOrientation{{0.0,0.0}};
    double angleRotation{90.0};
    testingOrientation = create_orientaion(angleRotation);

    rotate_vector(testingOrientation, angleRotation);

    EXPECT_NEAR(testingOrientation[0], -1.0, testingTolerance);
}


TEST(DegreeToRadianConverter, GivenAnAngleOf45Degrees_WhenCheckingToSeeIfRadianCovnerterWorks_ExpectValueToBeCorrectlyConverted)
{
    double valueToBeConverted{45};
    double valueInRadians{0.785};
    EXPECT_NEAR(convert_to_radians(valueToBeConverted), valueInRadians, testingTolerance);
}

TEST(DegreeToRadianConverter, GivenAnAngleOfNegative30Degrees_WhenCheckingToSeeIfRadianCovnerterWorks_ExpectValueToBeCorrectlyConverted)
{

    double valueToBeConverted{-30};
    double valueInRadians{-0.523599};
    EXPECT_NEAR(convert_to_radians(valueToBeConverted), valueInRadians, testingTolerance);
}

//TEST(AntMotionTest, WhenGivenAnAnt_WhenCheckingToSeeIfItIsMovingByOnlyTheRangeSet_ExpectItToMoveAngleByAmountSet)
//{
//    AntSpy testingAnt;
//    double initialOrientation{45.0};

//    double initialOrientationInRadians{0.785398};

//    testingAnt.set_orientation(initialOrientation);

//    EXPECT_NEAR(testingAnt.get_x_orientation(), cos(initialOrientationInRadians), testingTolerance);
//    EXPECT_NEAR(testingAnt.get_y_orientation(), sin(initialOrientationInRadians), testingTolerance);
//}






