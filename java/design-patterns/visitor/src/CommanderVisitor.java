public class CommanderVisitor implements UnitVisitor {
  @Override
  public void visitSoldier(Soldier soldier) {

  }

  @Override
  public void visitSergant(Sergant sergant) {

  }

  @Override
  public void visitCommander(Commander commander) {
    System.out.println("Good to see you, " + commander);
  }
}
