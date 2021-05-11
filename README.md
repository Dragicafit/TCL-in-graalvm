# TCL-in-graalvm

|                              |                                                        | 10⁶   | 10⁷   | 10⁸   |
| :--------------------------- | ------------------------------------------------------ | ----- | ----- | ----- |
| c-for                        | ./for                                                  | 0.003 | 0.020 | 0.170 |
| c-for                        | lli for                                                | 0.065 | 0.102 | 0.472 |
| c-for                        | java PolyglotEval for                                  | 1.486 | 1.480 | 1.900 |
| c-for-shortCompil            | lli for.so                                             | 0.068 | 0.101 | 0.480 |
| c-for-shortCompil            | java PolyglotEval for.so                               | 1.691 | 1.500 | 1.800 |
| c-for-interpreter-for        | ./polyglot-eval-for                                    | 0.117 | 1.164 | 11.58 |
| c-for-interpreter-for        | lli polyglot-eval-for                                  | 0.630 | 5.020 | 47.21 |
| c-for-interpreter-for        | java PolyglotEval polyglot-eval-for                    | 3.694 | 23.00 | 226.4 |
| c-tcl-native-for             | tclsh require-for.tcl                                  | 0.145 | 1.200 | 11.47 |
| c-tcl-native-interpreter-for | tclsh require.tcl                                      | 0.144 | 1.200 | 11.40 |
| java-c-for                   | java PolyglotEvalPutMemberFor polyglot-import-for      | 2.022 | 2.128 | 2.216 |
| java-c-tcl-interpreter-for   | java PolyglotEvalPutMemberFor polyglot-import-eval-for | 4.456 | 23.00 | 206.4 |
| java-for                     | java PolyglotFor                                       | 0.406 | 0.412 | 0.412 |
| tcl-for                      | tclsh for.tcl                                          | 0.446 | 4.355 | 43.65 |
| tcl-for                      | ./polyglot-eval                                        | 0.434 | 4.502 | 43.16 |
| tcl-for                      | lli polyglot-eval                                      | 0.465 | 4.411 | 43.00 |
| tcl-for                      | java PolyglotEval polyglot-eval                        | 1.666 | 5.811 | 44.24 |
