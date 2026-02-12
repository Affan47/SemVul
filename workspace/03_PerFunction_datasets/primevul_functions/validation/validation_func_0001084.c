void onStrobelightSignal(int signo) {
  if (!RuntimeOption::StrobelightEnabled) {

    return;
  }

  if (signo == strobelight::kSignumCurrent) {

    if (rds::isFullyInitialized()) {

      if (!Strobelight::isXenonActive()) {

        setSurpriseFlag(XenonSignalFlag);
      }
    }
  }


}
