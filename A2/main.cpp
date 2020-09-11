#include <iostream>
#include "rectangle.hpp"
#include "circle.hpp"

using namespace smorodnikov;

void printGetFrameResult(const rectangle_t &rectangle)
{
  std::cout << "Frame rect figure data:\n" << "Central Point: "
      << "(" << rectangle.pos.x << ", " << rectangle.pos.y << ")"
      << "\nWedth: " << rectangle.width
      << "\nHeight: " << rectangle.height;
}
void printShape(const Shape &shape, const char* name)
{
  std::cout << "Figure name: " << name << "\n";
  std::cout << "============================\n";
  shape.show();
  std::cout << "\n\n";
  std::cout << name << " area: " << shape.getArea();
  std::cout << "\n\n";
  std::cout << "Frame rect figure data:\n";
  printGetFrameResult(shape.getFrameRect());
  std::cout << "\n\n";
}

int main()
{
  try
  {
    double scaleValue = 4.0;
    double moveOx = 2.0;
    double moveOy = 4.0;
    point_t movePoint{4, 6};
    smorodnikov::Circle test_circle({3, 3}, 1);
    smorodnikov::Rectangle test_rectangle({{5, 5}, 10, 5});
    
    printShape(test_circle, "Circle");

    std::cout << "Move in point " << "(" << movePoint.x << ", " << movePoint.y << "):\n";
    test_circle.move(movePoint);
    test_circle.show();
    std::cout << "\n\n";
    
    std::cout << "Move Ox = " << moveOx << " and Oy = " << moveOy << ":\n";
    test_circle.move(moveOx, moveOy);
    test_circle.show();
    std::cout << "\n\n";
    
    std::cout << "'" << scaleValue << "' scaling result:\n";
    test_circle.scale(scaleValue);
    test_circle.show();
    std::cout << "\n\n";

    printShape(test_rectangle, "Rectangle");
    
    std::cout << "Move in point " << "(" << movePoint.x << ", " << movePoint.y << "):\n";
    test_rectangle.move(movePoint);
    test_rectangle.show();
    std::cout << "\n\n";

    std::cout << "Move Ox = " << moveOx << " and Oy = " << moveOy << ":\n";
    test_rectangle.move(moveOx, moveOy);
    test_rectangle.show();
    std::cout << "\n\n";
    
    std::cout << "'" << scaleValue << "' scaling result:\n";
    test_rectangle.scale(scaleValue);
    test_rectangle.show();
    std::cout << "\n\n";
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what() << "\n";
    return -1;
  }
  
  return 0;
}
