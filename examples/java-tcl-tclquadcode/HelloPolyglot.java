import java.io.File;
import java.io.IOException;

import org.graalvm.polyglot.Context;
import org.graalvm.polyglot.Source;
import org.graalvm.polyglot.Value;

public class HelloPolyglot {

  public static class PrintFromJAVA {

    public void printFromJAVA() {
      System.out.println("Hello from JAVA");
    }
  }

  public static void main(String[] args) throws IOException {
    try (Context polyglot = Context.newBuilder().allowAllAccess(true).build()) {
      PrintFromJAVA printFromJAVA = new PrintFromJAVA();
      polyglot.getPolyglotBindings().putMember("printFromJAVA", printFromJAVA);

      File file = new File(args[0]);
      Source source = Source.newBuilder("llvm", file).build();
      Value cpart = polyglot.eval(source);
      Value res = cpart.execute();
      System.out.println(res.asString());
    }
  }
}