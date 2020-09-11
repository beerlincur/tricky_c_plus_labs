#include "rectangle.hpp"
#include "circle.hpp"

int main()
{
  point_t toP = {50, 40};
  double toX = 5;
  double toY = -5;
  
  Rectangle rectangle({2, 2}, 8, 9);
  
  Circle circle({2, 3}, 2);
  
  Shape *shapeRectangle = &rectangle;
  Shape *shapeCircle = &circle;
  
  std::cout << *shapeRectangle << " area: " << shapeRectangle->getArea() << "\n"
      << *shapeCircle << " area: " << shapeCircle->getArea() << "\n\n";
  
  shapeRectangle->move(toX, toY);
  shapeCircle->move(toX, toY);
  std::cout << "After moving to (double, double): to X = " << toX << ", to Y = " << toY << "\n"
      << *shapeRectangle << " area: " << shapeRectangle->getArea() << "\n"
      << *shapeCircle << " area: " << shapeCircle->getArea() << "\n\n";
  
  shapeRectangle->move(toP);
  shapeCircle->move(toP);
  std::cout << "After moving to point_t: (" << toP.x << ", " << toP.y << ")\n"
      << *shapeRectangle << " area: " << shapeRectangle->getArea() << "\n"
      << *shapeCircle << " area: " << shapeCircle->getArea() << "\n\n";
    
  rectangle_t borderRectangleForRectangle = shapeRectangle->getFrameRect();
  rectangle_t borderRectangleForCircle = shapeCircle->getFrameRect();
  std::cout << "Bounding rectangles:" << "\n"
      << "Rectangle's rectangle center = (" << borderRectangleForRectangle.pos.x << ", " << borderRectangleForRectangle.pos.y << ") heigt = "
      << borderRectangleForRectangle.height << " width = " << borderRectangleForRectangle.width << "\n"
      << "Circle's rectangle center = (" << borderRectangleForCircle.pos.x << ", " << borderRectangleForCircle.pos.y << ") heigt = "
      << borderRectangleForCircle.height << " width = " << borderRectangleForCircle.width << "\n\n";
  
  return 0;
}
