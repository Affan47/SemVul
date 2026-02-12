set_taskbar_progress(int state, int percent)
{
  if (state == 0) {
    taskbar_progress(-9);
    term.detect_progress = 0;
  }
  else if (state == 8) {
    taskbar_progress(-8);
    term.detect_progress = 0;
  }
  else if (state <= 3) {
    taskbar_progress(- state);
    if (percent >= 0) {
      taskbar_progress(percent);
      term.detect_progress = 0;
    }
    else
      term.detect_progress = state;
  }
}
