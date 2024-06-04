public enum PlantType {
  ALOE_VERA("aloe vera"), CACTUS("cactus");

  private String plantName;

  PlantType(String plantName) {
    this.plantName = plantName;
  }

  @Override
  public String toString() {
    return plantName;
  }
}
