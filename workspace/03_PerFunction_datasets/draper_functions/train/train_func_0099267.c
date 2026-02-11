init() {
  low=1;
  high=0xFFFFFFFF;
  pr.init();
  if (!pr.isModeled()) low=0, buf.resize(1<<16);
}
