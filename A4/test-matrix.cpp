#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix-shape.hpp"

using namespace smorodnikov;

const double epsilon = 0.0001;

BOOST_AUTO_TEST_SUITE(testRectangle)

BOOST_AUTO_TEST_CASE(testRotate)
{
  Rectangle rectangle({{10, 6.5}, 4, 4});
  const rectangle_t framePrev = rectangle.getFrameRect();
  const double areaPrev = rectangle.getArea();

  rectangle.rotate(90);

  BOOST_CHECK_CLOSE(framePrev.width, rectangle.getFrameRect().height, epsilon);
  BOOST_CHECK_CLOSE(framePrev.height, rectangle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(areaPrev, rectangle.getArea(), epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testCircle)

BOOST_AUTO_TEST_CASE(testRotate)
{
  Circle circle({10, 5.5}, 4.7);
  const rectangle_t framePrev = circle.getFrameRect();
  const double areaPrev = circle.getArea();

  circle.rotate(-65);

  BOOST_CHECK_CLOSE(framePrev.width, circle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(framePrev.pos.x, circle.getFrameRect().pos.x, epsilon);
  BOOST_CHECK_CLOSE(framePrev.pos.y, circle.getFrameRect().pos.y, epsilon);
  BOOST_CHECK_CLOSE(areaPrev, circle.getArea(), epsilon);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testCompositeShape)

BOOST_AUTO_TEST_CASE(compositeshape)
{
  CompositeShape shapes;
  std::shared_ptr<Shape> rectangle(new Rectangle({{ 4, 4 }, 4, 4}));
  std::shared_ptr<Shape> circle(new Circle({10, 4}, 2));
  shapes.addShape(rectangle);
  shapes.addShape(circle);
  
  shapes.rotate(90);

  point_t newPos_ = circle->getFrameRect().pos;

  BOOST_CHECK_EQUAL(newPos_.x, 7);
  BOOST_CHECK_EQUAL(newPos_.y, 1);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(testMatrix)

BOOST_AUTO_TEST_CASE(testLayering)
{
  Matrix matrix;

  matrix.addShape(std::make_shared<Rectangle>(Rectangle({{-23.2, 12.2}, 2.8, 3.4})));
  BOOST_CHECK_EQUAL(matrix.getRowSize(), 1);

  matrix.addShape(std::make_shared<Circle>(Circle({24.2, 13.1}, 3.7)));
  BOOST_CHECK_EQUAL(matrix.getRowSize(), 1);

  matrix.addShape(std::make_shared<Rectangle>(Rectangle({{18.9, 15}, 4.2, 8.8})));
  BOOST_CHECK_EQUAL(matrix.getRowSize(), 2);

  CompositeShape shapes;
  shapes.addShape(std::make_shared<Rectangle>(Rectangle({{11.1, 3.5}, 6.8, 7.2})));
  shapes.addShape(std::make_shared<Circle>(Circle({-128.1, 17.3}, 5)));

  matrix.addShape(std::make_shared<CompositeShape>(shapes));
  BOOST_CHECK_EQUAL(matrix.getRowSize(), 2);
}

BOOST_AUTO_TEST_CASE(testOutOfRange)
{
  Matrix matrix;

  BOOST_CHECK_THROW(matrix.getElement(1, 2), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(testInvalidArgument)
{
  Matrix matrix;

  BOOST_CHECK_THROW(matrix.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_SUITE_END()

