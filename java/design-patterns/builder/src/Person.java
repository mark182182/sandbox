public final class Person {

  private final String profession;
  private final String hairColor;
  private final float money;
  private final float income;
  private final Boolean isMarried;
  private final Integer numberOfHouses;

  Person(Builder builder) {
    this.profession = builder.getProfession();
    this.hairColor = builder.getHairColor();
    this.money = builder.getMoney();
    this.income = builder.getIncome();
    this.isMarried = builder.getMarried();
    this.numberOfHouses = builder.getNumberOfHouses();
  }

  public String getProfession() {
    return profession;
  }

  public String getHairColor() {
    return hairColor;
  }

  public Float getMoney() {
    return money;
  }

  public float getIncome() {
    return income;
  }

  public Boolean getMarried() {
    return isMarried;
  }

  public Integer getNumberOfHouses() {
    return numberOfHouses;
  }

  @Override
  public String toString() {
    return "A person, who is a " + getHairColor() + " haired " + getProfession() + ".";
  }
}
