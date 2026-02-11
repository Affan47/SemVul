Start() {
  if (state_ != STATE_INIT)
    return;


  start_time_ = CurrentTime();
  GetRunner()->StartTask(this);
}
