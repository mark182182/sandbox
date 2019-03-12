public class DefaultHedgehog implements Hedgehog {
  @Override
  public void scratchEnemy() {
    System.out.println("The hedgehog scratches its enemy.");
  }

  @Override
  public void shootSpikes(int spikes) {
    System.out.println("The hedgehog shoots " + spikes + " spikes!");
  }

  @Override
  public int restoreSpikes() {
    System.out.println("The hedgehog refills some spikes.");
    return 2;
  }
}
