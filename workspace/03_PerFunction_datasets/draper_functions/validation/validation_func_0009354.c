DownSample(LargeRAWFile& SourceRAWFile, unsigned char* pDenseData, const UINT64VECTOR3& vVolumeSize, const UINT64VECTOR3& vDSFactor) {
  UINT64VECTOR3 vSmallSize = vVolumeSize/vDSFactor;

  uint64_t iNumDownsampledValues = vDSFactor.volume();
  size_t iTargetIndex = 0;
  size_t iSourceIndex = 0;
  for (size_t z = 0;z<size_t(vSmallSize[2]);z++) {
    MESSAGE("Downsampling data in slice %u of %llu\n(%g%% completed)",
            static_cast<unsigned>(z+1), vSmallSize[2],
            100.0f*float(z+1)/float(vSmallSize[2]));
    for (size_t y = 0;y<size_t(vSmallSize[1]);y++) {
      for (size_t x = 0;x<size_t(vSmallSize[0]);x++) {

        double fAccValue = 0;
        unsigned char cValue = 0;

        for (size_t w = 0;w<size_t(vDSFactor[2]);w++) {
          for (size_t v = 0;v<size_t(vDSFactor[1]);v++) {
            for (size_t u = 0;u<size_t(vDSFactor[0]);u++) {
                iSourceIndex = size_t((x*vDSFactor[0]+u) + (y*vDSFactor[1]+v) * vVolumeSize[0] + (z*vDSFactor[2]+w) * vVolumeSize[0] * vVolumeSize[1]);
                SourceRAWFile.Read<unsigned char>(&cValue, 1, iSourceIndex, 0);
                fAccValue += cValue;
            }
          }
        }

        fAccValue /= iNumDownsampledValues;

        pDenseData[iTargetIndex++] = (unsigned char)(fAccValue);
      }
    }
  }
}
