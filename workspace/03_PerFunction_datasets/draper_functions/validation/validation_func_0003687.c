Run() {
  TickSample sample;
  bool overflow = Remove(&sample);
  while (running_) {
    LOG(isolate_, TickEvent(&sample, overflow));
    overflow = Remove(&sample);
  }
}
