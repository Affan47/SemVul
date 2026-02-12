TEST_P(JSITest, JSErrorTest) {


  EXPECT_THROW(
      eval("var GetMessageThrows = {get message() { throw Error('ex'); }};"
           "throw GetMessageThrows;"),
      JSIException);

  EXPECT_THROW(
      eval("var GetMessageThrows = {get message() { throw GetMessageThrows; }};"
           "throw GetMessageThrows;"),
      JSIException);


  EXPECT_THROW(
      eval(
          "Object.defineProperty("
          "  globalThis, 'String', {configurable:true, get() { var e = Error(); e.message = 23; throw e; }});"
          "var e = Error();"
          "e.message = 17;"
          "throw e;"),
      JSIException);

  EXPECT_THROW(
      eval(
          "var e = Error();"
          "Object.defineProperty("
          "  e, 'message', {configurable:true, get() { throw Error('getter'); }});"
          "throw e;"),
      JSIException);

  EXPECT_THROW(
      eval("var e = Error();"
           "String = function() { throw Error('ctor'); };"
           "throw e;"),
      JSIException);


  EXPECT_THROW(
      eval("String = function() { return 42; };"
           "var e = Error();"
           "e.message = 17;"
           "throw e;"),
      JSIException);


  EXPECT_THROW(eval("throw 17;"), JSIException);

  EXPECT_THROW(eval("throw undefined;"), JSIException);


  EXPECT_THROW(
      eval("var e = {toString() { throw new Error('errstr'); }};"
           "throw e;"),
      JSIException);
}
