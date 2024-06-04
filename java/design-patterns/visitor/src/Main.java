public class Main {

  public static void main(String[] args) {
    Commander commander = new Commander(new Sergant(new Sergant(new Soldier()), new Soldier(), new Soldier(), new Soldier()));
    commander.accept(new SoldierVisitor());
    commander.accept(new SergantVisitor());
    commander.accept(new CommanderVisitor());

    System.out.println("----");
    Sergant sergant = new Sergant(new Commander(), new Sergant(new Soldier(), new Soldier()), new Sergant());
    sergant.accept(new SoldierVisitor());
    sergant.accept(new SergantVisitor());
    sergant.accept(new CommanderVisitor());

    System.out.println("----");
    Soldier soldier = new Soldier(new Commander(), new Sergant(), new Soldier());
    soldier.accept(new SoldierVisitor());
    soldier.accept(new SergantVisitor());
    soldier.accept(new CommanderVisitor());
  }
}
