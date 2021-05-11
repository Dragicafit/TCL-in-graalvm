import java.io.File;
import java.io.IOException;

import org.graalvm.polyglot.Context;
import org.graalvm.polyglot.Source;
import org.graalvm.polyglot.Value;

public class PolyglotEvalPutMemberPuts {

  public String printFromJAVA() {
    System.out.println("Hello from JAVA");
    return "Hello from JAVA called by C";
  }

  public static void main(String[] args) throws IOException {
    try (Context polyglot = Context.newBuilder().allowAllAccess(true).build()) {
      PolyglotEvalPutMemberPuts polyglotEvalPutMemberPuts = new PolyglotEvalPutMemberPuts();
      polyglot.getPolyglotBindings().putMember("polyglotEvalPutMemberPuts", polyglotEvalPutMemberPuts);

      File file = new File(args[0]);
      Source source = Source.newBuilder("llvm", file).build();
      Value cpart = polyglot.eval(source);
      cpart.execute();
    }
  }
}
