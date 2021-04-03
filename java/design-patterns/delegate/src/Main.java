public class Main {

  public static void main(String[] args) {
    CanadianLumberjack canadianLumberjack = new CanadianLumberjack();
    ItalianLumberjack italianLumberjack= new ItalianLumberjack();

    LumberjackController canadianLumberjackController = new LumberjackController(canadianLumberjack);
    LumberjackController italianLumberjackController = new LumberjackController(italianLumberjack);

    System.out.println(canadianLumberjackController.cutTree("tree"));
    System.out.println(italianLumberjackController.cutTree("tree"));
  }
}
