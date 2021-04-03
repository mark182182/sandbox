public class PoisonousHedgehog implements Hedgehog {

  private Hedgehog poisonousHedgehog;

  public PoisonousHedgehog(Hedgehog poisonousHedgehog) {
    this.poisonousHedgehog = poisonousHedgehog;
  }

  @Override
  public void scratchEnemy() {
    poisonousHedgehog.scratchEnemy();
    System.out.println("The hedgehog uses poison!");
  }

  @Override
  public void shootSpikes(int spikes) {
    poisonousHedgehog.shootSpikes(spikes * 2);
    System.out.println("The enemy is now poisoned.");
  }

  @Override
  public int restoreSpikes() {
    return 2 + poisonousHedgehog.restoreSpikes();
  }
}
