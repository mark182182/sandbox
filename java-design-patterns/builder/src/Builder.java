public class Builder {
  private final String profession;
  private final String hairColor;
  private float money;
  private float income;

  public Boolean isMarried;
  public Integer numberOfHouses;

  public Builder(String profession, String hairColor) {
    if (profession == null || hairColor == null) {
      throw new IllegalArgumentException("Must have profession and hair color");
    } else {
      this.profession = profession;
      this.hairColor = hairColor;
    }
  }

  public Builder withMoney(Float money) {
    this.money = money;
    return this;
  }

  public Builder withIncome(Float income) {
    this.income = income;
    return this;
  }

  public Builder withMarried(Boolean isMarried) {
    this.isMarried = isMarried;
    return this;
  }

  public Builder withNumberOfHouses(Integer numberOfHouses) {
    this.numberOfHouses = numberOfHouses;
    return this;
  }

  public Person build() {
    return new Person(this);
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

  public Float getIncome() {
    return income;
  }

  public Boolean getMarried() {
    return isMarried;
  }

  public Integer getNumberOfHouses() {
    return numberOfHouses;
  }

}
