public class LexiconAdapter extends TextBook {
  private Lexicon lexicon;

  public LexiconAdapter(int pages, Lexicon lexicon) {
    super(pages);
    if (!lexicon.isSacred()) {
      this.lexicon = lexicon;
    }
  }
}
