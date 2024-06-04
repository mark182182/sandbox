public class Main {

  public static void main(String[] args) {
    TextBook textBook = new TextBook(120);
    Person person = new Person(10);
    person.readBook(textBook);

    System.out.println("----");

    Lexicon sacredLexicon = new Lexicon(300, true);
    person.readBook(sacredLexicon);

    System.out.println("----");

    LexiconAdapter sacredLexiconAdapter = new LexiconAdapter(sacredLexicon.getPages(), sacredLexicon);
    person.readBook(sacredLexiconAdapter);

    System.out.println("----");

    Lexicon lexicon = new Lexicon(220, false);
    person.readBook(lexicon);

    System.out.println("----");

    LexiconAdapter lexiconAdapter = new LexiconAdapter(lexicon.getPages(), lexicon);
    person.readBook(lexiconAdapter);
  }
}