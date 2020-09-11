#define BOOST_TEST_MAIN

#include <boost/test/included/unit_test.hpp>
#include "circle.hpp"
#include "rectangle.hpp"
#include "composite-shape.hpp"

using namespace smorodnikov;

const double epsilon = 0.0001;

BOOST_AUTO_TEST_SUITE(testCompositeShape)

BOOST_AUTO_TEST_CASE(testMoveByOffset)
{
  CompositeShape shapes;
  shapes.addShape(std::make_shared<Rectangle>(Rectangle({{-1.5, 1.5}, 5, 6})));
  shapes.addShape(std::make_shared<Circle>(Circle({1.9, 2.5}, 4)));

  const rectangle_t framePrev = shapes.getFrameRect();
  const double areaPrev = shapes.getArea();
  const double dx = 5.1;
  const double dy = -11.4;

  shapes.move(dx, dy);
  BOOST_CHECK_EQUAL(framePrev.height, shapes.getFrameRect().height);
  BOOST_CHECK_EQUAL(framePrev.width, shapes.getFrameRect().width);
  BOOST_CHECK_EQUAL(areaPrev, shapes.getArea());
}

BOOST_AUTO_TEST_CASE(testMoveToPoint)
{
  CompositeShape shapes;
  shapes.addShape(std::make_shared<Rectangle>(Rectangle({{1.8, 2}, 7.1, 9.5})));
  shapes.addShape(std::make_shared<Circle>(Circle({5.3, 7.4}, 5)));

  const rectangle_t framePrev = shapes.getFrameRect();
  const double areaPrev = shapes.getArea();
  const point_t shiftPoint = {-19.7, 54.2};

  shapes.move(shiftPoint);
  BOOST_CHECK_CLOSE(framePrev.height, shapes.getFrameRect().height, epsilon);
  BOOST_CHECK_CLOSE(framePrev.width, shapes.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(areaPrev, shapes.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(testAreaAfterScailing)
{
  CompositeShape shapes;
  shapes.addShape(std::make_shared<Rectangle>(Rectangle({{14.3, 0.0}, 3.7, 9.9})));
  shapes.addShape(std::make_shared<Circle>(Circle({92.1, -55.1}, 3.3)));
  const double areaPrev = shapes.getArea();
  const double coef = 4.3;
  
  shapes.scale(coef);
  BOOST_CHECK_CLOSE(areaPrev * coef * coef, shapes.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(testInsertNullPtrParametr)
{
  CompositeShape shapes;
  BOOST_CHECK_THROW(shapes.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testScaleParametr)
{
  CompositeShape shapes;
  BOOST_CHECK_THROW(shapes.scale(-1.0), std::logic_error);

  shapes.addShape(std::make_shared<Rectangle>(Rectangle({{-99.9, 5.5}, 12.7, 5.9})));
  shapes.addShape(std::make_shared<Circle>(Circle({104.6, -9.3}, 5.4)));

  BOOST_CHECK_THROW(shapes.scale(-1.0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testInsertParametr)
{
  CompositeShape shapes;
  shapes.addShape(std::make_shared<Circle>(Circle({0.0, 0.0}, 2.4)));

  BOOST_CHECK_THROW(shapes.addShape(nullptr), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(testRemoveParametr)
{
  CompositeShape shapes;
  shapes.addShape(std::make_shared<Circle>(Circle({2.8, 1.3}, 1.4)));
  shapes.addShape(std::make_shared<Rectangle>(Rectangle({{21.0, 21.5}, 6.4, 9.2})));

  BOOST_CHECK_THROW(shapes.removeShape(14), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(testSquareBraketsParametr)
{
  CompositeShape shapes;
  shapes.addShape(std::make_shared<Circle>(Circle({6.3, 3.2}, 6.0)));
  shapes.addShape(std::make_shared<Rectangle>(Rectangle({{17.1, 4.5}, 3.2, 7.1})));

  BOOST_CHECK_THROW(shapes[11], std::out_of_range);
}

BOOST_AUTO_TEST_SUITE_END()

