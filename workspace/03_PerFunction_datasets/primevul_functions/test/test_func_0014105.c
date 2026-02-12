void SplashOutputDev::unsetSoftMaskFromImageMask(GfxState *state, double *baseMatrix) {
  double bbox[4] = {0,0,1,1};


  if (transpGroupStack->softmask != nullptr) {
    unsigned char *dest = bitmap->getAlphaPtr();
    unsigned char *src = transpGroupStack->softmask->getDataPtr();
    for (int c= 0; c < transpGroupStack->softmask->getRowSize() * transpGroupStack->softmask->getHeight(); c++) {
      dest[c] = src[c];
    }
    delete transpGroupStack->softmask;
    transpGroupStack->softmask = nullptr;
  }
  endTransparencyGroup(state);
  baseMatrix[4] += transpGroupStack->tx;
  baseMatrix[5] += transpGroupStack->ty;
  paintTransparencyGroup(state, bbox);
}
