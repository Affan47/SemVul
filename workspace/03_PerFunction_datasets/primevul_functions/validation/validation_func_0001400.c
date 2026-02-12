void Strobelight::log(c_WaitableWaitHandle* wh) const {
  if (RuntimeOption::XenonForceAlwaysOn) {


    return;
  }

  if (getSurpriseFlag(XenonSignalFlag)) {

    clearSurpriseFlag(XenonSignalFlag);
  }

  TRACE(1, "Strobelight::log\n");
  if (active()) {


    auto bt = createBacktrace(BacktraceArgs()
                              .fromWaitHandle(wh)


                              .ignoreArgs());
    logToUSDT(bt);
  }
}
