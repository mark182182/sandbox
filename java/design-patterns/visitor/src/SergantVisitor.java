public class SergantVisitor implements UnitVisitor {
  @Override
  public void visitSoldier(Soldier soldier) {

  }

  @Override
  public void visitSergant(Sergant sergant) {
    System.out.println("Good day to you, " + sergant);
  }

  @Override
  public void visitCommander(Commander commander) {

  }
}
