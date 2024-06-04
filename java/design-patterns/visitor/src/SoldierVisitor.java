public class SoldierVisitor implements UnitVisitor {
  @Override
  public void visitSoldier(Soldier soldier) {
    System.out.println("Hello, " + soldier);
  }

  @Override
  public void visitSergant(Sergant sergant) {

  }

  @Override
  public void visitCommander(Commander commander) {

  }
}
