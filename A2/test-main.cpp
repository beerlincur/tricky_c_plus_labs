#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <cmath>
#include "circle.hpp"
#include "rectangle.hpp"

using namespace smorodnikov;

const double epsilon = 0.001;

BOOST_AUTO_TEST_CASE(const_rectangle_parameters_and_area_after_move_dx_dy)
{
  Rectangle test_rectangle({{5, 5}, 10, 5});
  const double rectangle_area = test_rectangle.getArea();
  const double rectangle_width = test_rectangle.getFrameRect().width;
  const double rectangle_height = test_rectangle.getFrameRect().height;
  test_rectangle.move(2, 4);
  BOOST_CHECK_CLOSE(rectangle_area, test_rectangle.getArea(), epsilon);
  BOOST_CHECK_CLOSE(rectangle_width, test_rectangle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(rectangle_height, test_rectangle.getFrameRect().height, epsilon);
}

BOOST_AUTO_TEST_CASE(const_rectangle_parameters_and_area_after_move_point)
{
  Rectangle test_rectangle({{5, 5}, 10, 5});
  const double rectangle_area = test_rectangle.getArea();
  const double rectangle_width = test_rectangle.getFrameRect().width;
  const double rectangle_height = test_rectangle.getFrameRect().height;
  test_rectangle.move({2, 4});
  BOOST_CHECK_CLOSE(rectangle_area, test_rectangle.getArea(), epsilon);
  BOOST_CHECK_CLOSE(rectangle_width, test_rectangle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(rectangle_height, test_rectangle.getFrameRect().height, epsilon);
}

BOOST_AUTO_TEST_CASE(rectangle_quadratic_area_change_after_scaling)
{
  Rectangle test_rectangle({{5, 5}, 10, 5});
  const double rectangle_area = test_rectangle.getArea();
  const double factor = 4;
  test_rectangle.scale(factor);
  BOOST_CHECK_CLOSE(rectangle_area * factor * factor, test_rectangle.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(invalid_scale_parameter_for_rectangle1)
{
  Rectangle test_rectangle({{5, 5}, 10, 5});
  const double factor = 0;
  BOOST_CHECK_THROW (test_rectangle.scale(factor), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_scale_parameter_for_rectangle2)
{
  Rectangle test_rectangle({{5, 5}, 10, 5});
  const double factor = -1;
  BOOST_CHECK_THROW (test_rectangle.scale(factor), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_rectangle_constructor_parameters1)
{
  BOOST_CHECK_THROW (Rectangle({{5, 5}, -10, -5}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_rectangle_constructor_parameters2)
{
  BOOST_CHECK_THROW (Rectangle({{5, 5}, 0, 0}), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(const_circle_parameters_and_area_after_move_dx_dy)
{
  Circle test_circle({3, 3}, 1);
  const double circle_area = test_circle.getArea();
  const double frame_rectangle_width = test_circle.getFrameRect().width;
  const double frame_rectangle_height = test_circle.getFrameRect().height;
  test_circle.move(2, 4);
  BOOST_CHECK_CLOSE(circle_area, test_circle.getArea(), epsilon);
  BOOST_CHECK_CLOSE(frame_rectangle_width, test_circle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(frame_rectangle_height, test_circle.getFrameRect().height, epsilon);
}

BOOST_AUTO_TEST_CASE(const_circle_parameters_and_area_after_move_point)
{
  Circle test_circle({3, 3}, 1);
  const double circle_area = test_circle.getArea();
  const double frame_rectangle_width = test_circle.getFrameRect().width;
  const double frame_rectangle_height = test_circle.getFrameRect().height;
  test_circle.move({2, 4});
  BOOST_CHECK_CLOSE(circle_area, test_circle.getArea(), epsilon);
  BOOST_CHECK_CLOSE(frame_rectangle_width, test_circle.getFrameRect().width, epsilon);
  BOOST_CHECK_CLOSE(frame_rectangle_height, test_circle.getFrameRect().height, epsilon);
}

BOOST_AUTO_TEST_CASE(circle_quadratic_area_change_after_scaling)
{
  Circle test_circle({3, 3}, 1);
  const double circle_area = test_circle.getArea();
  const double factor = 4;
  test_circle.scale(factor);
  BOOST_CHECK_CLOSE(circle_area * factor * factor, test_circle.getArea(), epsilon);
}

BOOST_AUTO_TEST_CASE(invalid_scale_parameter_for_circle1)
{
  Circle test_circle({3, 3}, 1);
  const double factor = 0;
  BOOST_CHECK_THROW (test_circle.scale(factor);, std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_scale_parameter_for_circle2)
{
  Circle test_circle({3, 3}, 1);
  const double factor = -1;
  BOOST_CHECK_THROW (test_circle.scale(factor);, std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_circle_constructor_parameter1)
{
  BOOST_CHECK_THROW (Circle({3, 3}, -1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(invalid_circle_constructor_parameter2)
{
  BOOST_CHECK_THROW (Circle({3, 3}, 0);, std::invalid_argument);
}
