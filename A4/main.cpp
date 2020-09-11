#include "rectangle.hpp"
#include "circle.hpp"
#include "composite-shape.hpp"
#include "matrix-shape.hpp"

using namespace smorodnikov;

int main()
{
  try
  {
    std::shared_ptr<Shape> rectangle(new Rectangle({{ 5, 6 }, 6, 4}));
    std::shared_ptr<Shape> circle(new Circle({ 6, 9 }, 3));
    std::shared_ptr<Shape> circle2(new Circle({ 12, 7 }, 3));

    CompositeShape shapes;
    shapes.addShape(rectangle);
    shapes.addShape(circle);
    shapes.addShape(circle2);

    Matrix test_matrix(shapes);
    
    test_matrix.show();
    return 0;
  }
  catch (const std::invalid_argument &error)
  {
    std::cerr << error.what() << "\n";
    return -1;
  }
}

