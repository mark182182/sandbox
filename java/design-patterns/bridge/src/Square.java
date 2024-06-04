public class Square implements Shape {
  Color color = Color.DEFAULT;
  private int sideLengthInCentimeters;

  public Square(int sideLengthInCentimeters) {
    this.sideLengthInCentimeters = sideLengthInCentimeters;
  }

  @Override
  public void getDimensions() {
    System.out.println("The side of the square is " + sideLengthInCentimeters + "cms.");
  }

  @Override
  public void getInformation() {
    System.out.println("This is a " + this.color + " square.");
  }

  @Override
  public void setColor(Color color) {
    this.color = color;
  }

  @Override
  public String toString() {
    return "square";
  }
}
