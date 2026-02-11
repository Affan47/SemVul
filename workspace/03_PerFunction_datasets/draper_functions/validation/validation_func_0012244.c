Preset(int size, int step,
      double (*NewWindow)(double phase), float Scale)
{ int err;
  err=Preset(size,step,(float *)NULL); if(err) return -1;
  err=SetWindow(NewWindow,Scale);
  if(err) { Free(); return -1; }
  return 0; }
