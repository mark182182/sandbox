public class Main {

  public static void main(String[] args) {
    System.out.println("Before painting: ");

    Square square = new Square(10);
    square.getDimensions();
    square.getInformation();

    System.out.println("----");
    Triangle triangle = new Triangle(20);
    triangle.getDimensions();
    triangle.getInformation();

    System.out.println("----");
    System.out.println("After painting: ");
    Painter painter = new Painter();
    painter.paintShape(square, Color.BLUE);
    painter.paintShape(triangle, Color.RED);

    System.out.println("----");
    square.getInformation();
    triangle.getInformation();
  }
}
