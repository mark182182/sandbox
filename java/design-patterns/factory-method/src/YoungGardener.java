public class YoungGardener implements PlantMaker {
  @Override
  public Plant makePlant(PlantType plantType) {
    return new YoungGardenerPlant(plantType);
  }
}
