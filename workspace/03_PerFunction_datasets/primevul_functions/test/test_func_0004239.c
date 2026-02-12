void setOneRttKeys() {


    if (!allowZeroRttKeys_) {
      oneRttWriteCipher_ = createNoOpAead();
      oneRttWriteHeaderCipher_ = createNoOpHeaderCipher();
    }
    oneRttReadCipher_ = createNoOpAead();
    oneRttReadHeaderCipher_ = createNoOpHeaderCipher();
  }
