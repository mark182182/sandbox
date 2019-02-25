public class OldGardener implements PlantMaker {
  @Override
  public Plant makePlant(PlantType plantType) {
    return new OldGardenerPlant(plantType);
  }
}
