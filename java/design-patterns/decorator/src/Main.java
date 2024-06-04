public class Main {

    public static void main(String[] args) {
        System.out.println("With default hedgehog:");
        DefaultHedgehog defaultHedgehog = new DefaultHedgehog();
        defaultHedgehog.scratchEnemy();
        defaultHedgehog.shootSpikes(2);
        defaultHedgehog.restoreSpikes();
        System.out.println("With poisonous hedgehog:");
        PoisonousHedgehog poisonousHedgehog = new PoisonousHedgehog(defaultHedgehog);
        poisonousHedgehog.scratchEnemy();
        poisonousHedgehog.shootSpikes(2);
        poisonousHedgehog.restoreSpikes();
    }
}
