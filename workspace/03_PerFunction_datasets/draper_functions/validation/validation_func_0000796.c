jsiLoop() {

  jshIdle();

  jsiIdle();

  JsVar *exception = jspGetException();
  if (exception) {
    jsiConsolePrintf("Uncaught %v\n", exception);
    jsvUnLock(exception);
  }

  if (jspIsInterrupted()) {
    jsiConsoleRemoveInputLine();
    jsiConsolePrint("Execution Interrupted.\n");
    jspSetInterrupted(false);
  }
  JsVar *stackTrace = jspGetStackTrace();
  if (stackTrace) {
    jsiConsolePrintStringVar(stackTrace);
    jsvUnLock(stackTrace);
  }


  if (execInfo.execute & EXEC_CTRL_C_MASK) {
    execInfo.execute = execInfo.execute & (JsExecFlags)~EXEC_CTRL_C_MASK;
#ifndef EMBEDDED
    if (jsvIsEmptyString(inputLine)) exit(0);
#endif
    jsiClearInputLine();
  }


  jsiReturnInputLine();

  return loopsIdling==0;
}
