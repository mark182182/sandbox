public class OldGardenerPlant implements Plant {

  private PlantType plantType;

  public OldGardenerPlant(PlantType plantType) {
    this.plantType = plantType;
  }

  @Override
  public String toString() {
    return "Old gardener: " + getPlantType();
  }

  @Override
  public PlantType getPlantType() {
    return plantType;
  }
}
