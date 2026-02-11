getFeldKoord(int x, int y, int & xx, int & yy) const {
  xx = x * gric;
  yy = y * gric - mHochVerschiebung - (ld->mSechseck && (x & 1)) * gric / 2;
}
