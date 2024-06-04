public class LumberjackController implements Lumberjack {

  private final Lumberjack lumberjack;

  LumberjackController(Lumberjack lumberjack) {
    this.lumberjack = lumberjack;
  }

  @Override
  public String cutTree(String tree) {
    return lumberjack.cutTree(tree);
  }
}
