public class Main {

  public static void main(String[] args) {
    PlantMaker youngGardener = new YoungGardener();
    System.out.println(youngGardener.makePlant(PlantType.ALOE_VERA));
    System.out.println(youngGardener.makePlant(PlantType.CACTUS));
    PlantMaker oldGardener = new OldGardener();
    System.out.println(oldGardener.makePlant((PlantType.ALOE_VERA)));
    System.out.println(oldGardener.makePlant((PlantType.CACTUS)));
  }

}
