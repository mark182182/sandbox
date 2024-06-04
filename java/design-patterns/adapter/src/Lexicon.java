public class Lexicon implements Book {
  private int pages;
  private boolean sacred;

  public Lexicon(int pages, boolean sacred) {
    this.pages = pages;
    this.sacred = sacred;
  }


  @Override
  public int getPages() {
    return pages;
  }

  public boolean isSacred() {
    return sacred;
  }
}
