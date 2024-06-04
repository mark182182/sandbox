public class Triangle implements Shape {
  Color color = Color.DEFAULT;
  private int sideLengthInCentimeters;

  public Triangle(int sideLengthInCentimeters) {
    this.sideLengthInCentimeters = sideLengthInCentimeters;
  }

  @Override
  public void getDimensions() {
    System.out.println("The side of the triangle is " + sideLengthInCentimeters + "cms.");
  }

  @Override
  public void getInformation() {
    System.out.println("This is a " + this.color + " triangle.");
  }

  @Override
  public void setColor(Color color) {
    this.color = color;
  }

  @Override
  public String toString() {
    return "triangle";
  }
}