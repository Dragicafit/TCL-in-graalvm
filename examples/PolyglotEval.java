import java.io.File;
import java.io.IOException;

import org.graalvm.polyglot.Context;
import org.graalvm.polyglot.Source;
import org.graalvm.polyglot.Value;

public class PolyglotEval {

  public static void main(String[] args) throws IOException {
    try (Context polyglot = Context.newBuilder().allowAllAccess(true).build()) {
      File file = new File(args[0]);
      Source source = Source.newBuilder("llvm", file).build();
      Value cpart = polyglot.eval(source);
      cpart.execute();
    }
  }
}
