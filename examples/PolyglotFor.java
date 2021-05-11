public class PolyglotFor {

  static int val = 0;

  public void increment() {
    val++;
  }

  public void getVal() {
    System.out.println("val: " + val);
  }

  public static void main(String[] args) {
    PolyglotFor polyglotFor = new PolyglotFor();

    for (int i = 0; i < NB_ITERATIONS; i++) {
        polyglotFor.increment();
    }
    polyglotFor.getVal();
  }
}
