public class Sergant extends Unit {
  public Sergant(Unit... children) {
    super(children);
  }

  @Override
  public void accept(UnitVisitor visitor) {
    visitor.visitSergant(this);
    super.accept(visitor);
  }

  @Override
  public String toString() {
    return "sergant";
  }
}
