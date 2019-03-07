public class Main {

  public static void main(String[] args) {
    Builder blacksmithBuilder = new Builder("blacksmith", "green").withIncome(100.0F).withMarried(true).withMoney(200F).withNumberOfHouses(2);
    Person blacksmith = blacksmithBuilder.build();
    System.out.println(blacksmith.toString());

    Builder engineerBuilder = new Builder("engineer", "red").withIncome(100.0F).withMarried(false).withMoney(120F).withNumberOfHouses(1);
    Person engineer = engineerBuilder.build();
    StringBuilder engineerDescription = new StringBuilder();
    engineerDescription.append(engineer.toString());
    engineerDescription.append(" Income: ").append((int) engineer.getIncome());
    engineerDescription.append(" Married: ").append(engineer.getMarried());
    engineerDescription.append(" Money: ").append(engineer.getMoney());
    engineerDescription.append(" Houses: ").append(engineer.getNumberOfHouses());
    System.out.println(engineerDescription.toString());
  }
}
