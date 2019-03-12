public class Painter implements Paint {

  @Override
  public void paintShape(Shape shape, Color color) {
    shape.setColor(color);
    System.out.println(color + " set for " + shape.toString() + ".");
  }
}
