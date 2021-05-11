# TCL-in-graalvm

| lanaguages added to eval | languages with polygot |                                                        | 10⁶   | 10⁷   | 10⁸   |
| -----------------------: | :--------------------- | ------------------------------------------------------ | ----- | ----- | ----- |
|                          | c                      | ./for                                                  | 0.003 | 0.020 | 0.170 |
|                          | c                      | lli for                                                | 0.065 | 0.102 | 0.472 |
|                     java | c                      | java PolyglotEval for                                  | 1.486 | 1.480 | 1.900 |
|                          | c                      | lli for.so                                             | 0.068 | 0.101 | 0.480 |
|                     java | c                      | java PolyglotEval for.so                               | 1.691 | 1.500 | 1.800 |
|                          | c-tcl                  | ./polyglot-eval-for                                    | 0.117 | 1.164 | 11.58 |
|                          | c-tcl                  | lli polyglot-eval-for                                  | 0.630 | 5.020 | 47.21 |
|                     java | c-tcl                  | java PolyglotEval polyglot-eval-for                    | 3.694 | 23.00 | 206.5 |
|                          | tcl-c                  | tclsh require-for.tcl                                  | 0.139 | 1.200 | 11.47 |
|                        c | tcl-c                  | ./polyglot-eval                                        | 0.140 | 1.420 | 11.69 |
|                        c | tcl-c                  | lli polyglot-eval                                      | 0.164 | 1.217 | 13.69 |
|                   java-c | tcl-c                  | java PolyglotEval polyglot-eval                        | 1.393 | 2.425 | 13.05 |
|                          | tcl-c-tcl              | tclsh require.tcl                                      | 0.144 | 1.200 | 11.82 |
|                        c | tcl-c-tcl              | ./polyglot-eval                                        | 0.140 | 1.174 | 11.62 |
|                        c | tcl-c-tcl              | lli polyglot-eval                                      | 0.161 | 1.198 | 13.78 |
|                   java-c | tcl-c-tcl              | java PolyglotEval polyglot-eval                        | 1.428 | 2.427 | 13.26 |
|                          | java-c                 | java PolyglotEvalPutMemberFor polyglot-import-for      | 2.022 | 2.128 | 2.216 |
|                          | java-c-tcl             | java PolyglotEvalPutMemberFor polyglot-import-eval-for | 4.456 | 23.00 | 206.4 |
|                          | java                   | java PolyglotFor                                       | 0.406 | 0.412 | 0.412 |
|                          | tcl                    | tclsh for.tcl                                          | 0.446 | 4.355 | 43.65 |
|                        c | tcl                    | ./polyglot-eval                                        | 0.434 | 4.502 | 43.16 |
|                        c | tcl                    | lli polyglot-eval                                      | 0.465 | 4.411 | 43.00 |
|                   java-c | tcl                    | java PolyglotEval polyglot-eval                        | 1.666 | 5.811 | 44.24 |
