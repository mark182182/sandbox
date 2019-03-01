public class YoungGardenerPlant implements Plant {

  private PlantType plantType;

  public YoungGardenerPlant(PlantType plantType) {
    this.plantType = plantType;
  }

  @Override
  public String toString() {
    return "Young gardener: " + getPlantType();
  }

  @Override
  public PlantType getPlantType() {
    return plantType;
  }
}
