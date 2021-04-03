public interface UnitVisitor {
  void visitSoldier(Soldier soldier);
  void visitSergant(Sergant sergant);
  void visitCommander(Commander commander);
}
