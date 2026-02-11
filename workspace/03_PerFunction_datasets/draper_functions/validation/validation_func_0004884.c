setDepthToAtLeast(unsigned NewDepth) {
  if (NewDepth <= getDepth())
    return;
  setDepthDirty();
  Depth = NewDepth;
  isDepthCurrent = true;
}
