public class Person {
  private int age;

  public Person(int age) {
    this.age = age;
  }

  public void readBook(Book book) {
    if (age >= 10 && book.getPages() < 240 && book.getClass() != Lexicon.class) {
      System.out.println("The person reads a book with " + book.getPages() + " pages.");
    } else {
      System.out.println("The person can't read this book.");
    }
  }
}
