import java.io.File;
import java.io.IOException;

import org.graalvm.polyglot.Context;
import org.graalvm.polyglot.Source;
import org.graalvm.polyglot.Value;

public class PolyglotEvalPutMemberFor {

  static int val = 0;

  public void increment() {
    val++;
  }

  public int getVal() {
    return val;
  }

  public static void main(String[] args) throws IOException {
    try (Context polyglot = Context.newBuilder().allowAllAccess(true).build()) {
      PolyglotEvalPutMemberFor polyglotEvalPutMemberFor = new PolyglotEvalPutMemberFor();
      polyglot.getPolyglotBindings().putMember("polyglotEvalPutMemberFor", polyglotEvalPutMemberFor);

      File file = new File(args[0]);
      Source source = Source.newBuilder("llvm", file).build();
      Value cpart = polyglot.eval(source);
      cpart.execute();
    }
  }
}
