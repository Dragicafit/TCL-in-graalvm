import java.io.File;
import java.io.IOException;
import java.math.BigInteger;

import org.graalvm.polyglot.Context;
import org.graalvm.polyglot.Source;
import org.graalvm.polyglot.Value;

public class PolyglotEvalPutMemberBigInteger {

  public BigInteger passBigInteger(BigInteger bi) {
    System.out.println("BigInteger: " + bi);
    return bi;
  }

  public static void main(String[] args) throws IOException {
    try (Context polyglot = Context.newBuilder().allowAllAccess(true).build()) {
      PolyglotEvalPutMemberBigInteger polyglotEvalPutMemberBigInteger = new PolyglotEvalPutMemberBigInteger();
      polyglot.getPolyglotBindings().putMember("polyglotEvalPutMemberBigInteger", polyglotEvalPutMemberBigInteger);

      File file = new File(args[0]);
      Source source = Source.newBuilder("llvm", file).build();
      Value cpart = polyglot.eval(source);
      cpart.execute();
    }
  }
}
