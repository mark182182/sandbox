public class Main {

    public static void main(String[] args) {
        Election election = Election.INSTANCE;
        Election election2 = Election.INSTANCE;
        System.out.println(election.getClass().equals(election2.getClass()));
    }
}
