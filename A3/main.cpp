#include <iostream>
#include <memory>
#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"

using namespace smorodnikov;

void printGetFrameResult(const rectangle_t &rectangle)
{
  std::cout << "\nFrame rect figure data:" << '\n' << "Central Point: "
      << "(" << rectangle.pos.x << ", " << rectangle.pos.y << ")"
      << '\n' << "Width: " << rectangle.width
      << '\n' << "Height: " << rectangle.height;
}
void printShape(const Shape &shape, const char* name)
{
  std::cout << "Figure name: " << name << "\n";
  std::cout << "============================\n";
  shape.show();
  std::cout << "\n\n";
  std::cout << name << " area: " << shape.getArea();
  std::cout << "\n\n";
  printGetFrameResult(shape.getFrameRect());
  std::cout << "\n\n";
}

int main()
{
  try
  {
    int index = 0;
    double moveOx = 2.0;
    double moveOy = 4.0;
    point_t movePoint{4, 6};
    std::shared_ptr<Shape> test_rectangle = std::make_shared<Rectangle>(Rectangle({{1.8, 2}, 3, 5}));
    std::shared_ptr<Shape> test_rectangle_second
        = std::make_shared<Rectangle>(Rectangle({{-3, 5}, 2, 6}));

    std::shared_ptr<Shape> test_circle = std::make_shared<Circle>(Circle({-1.5, 1.5}, 2));

    std::cout << "Composite shapes:\n" << "===================\n";

    CompositeShape shapes;
    shapes.addShape(test_rectangle);
    shapes.addShape(test_circle);
    shapes.show();
    std::cout << "\n\nArea:\n" << "===================\n";
    std::cout << '\n' << shapes.getArea() << '\n';
    std::cout << "-------------------------";
    printGetFrameResult(shapes.getFrameRect());
    std::cout << '\n';
    std::cout << "\n\nAfter move in point (4, 6):\n" << "===========================\n";
    shapes.move(movePoint);
    shapes.show();
    std::cout << "\n\nAfter move Ox = 2 and Oy = 4:\n" << "===========================\n";
    shapes.move(moveOx, moveOy);
    shapes.show();
    std::cout << "\n\nAfter scaling (х2):\n" << "===================\n";
    shapes.scale(2);
    shapes.show();
    std::cout << "\n\nComposite shapes after deleting first shape (rectangle): \n";
    shapes.removeShape(index);
    shapes.show();
    std::cout << '\n';
  }
  catch (const std::invalid_argument& error)
  {
    std::cerr << error.what() << "\n";
    return -1;
  }
  return 0;
}

