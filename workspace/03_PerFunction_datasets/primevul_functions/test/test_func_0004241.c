void doHandshake(std::unique_ptr<IOBuf> data, EncryptionLevel) override {
    IOBufEqualTo eq;
    auto chlo = folly::IOBuf::copyBuffer("CHLO");
    auto clientFinished = IOBuf::copyBuffer("FINISHED");
    if (eq(data, chlo)) {
      if (chloSync_) {


        writeDataToQuicStream(
            *getCryptoStream(*conn_.cryptoState, EncryptionLevel::Initial),
            IOBuf::copyBuffer("SHLO"));
        if (allowZeroRttKeys_) {
          validateAndUpdateSourceToken(conn_, sourceAddrs_);
          phase_ = Phase::KeysDerived;
          setEarlyKeys();
        }
        setHandshakeKeys();
      } else {

        executor_->add([&] {
          writeDataToQuicStream(
              *getCryptoStream(*conn_.cryptoState, EncryptionLevel::Initial),
              IOBuf::copyBuffer("SHLO"));
          if (allowZeroRttKeys_) {
            validateAndUpdateSourceToken(conn_, sourceAddrs_);
            phase_ = Phase::KeysDerived;
            setEarlyKeys();
          }
          setHandshakeKeys();
          if (callback_) {
            callback_->onCryptoEventAvailable();
          }
        });
      }
    } else if (eq(data, clientFinished)) {
      if (cfinSync_) {


        setOneRttKeys();
        phase_ = Phase::Established;
        handshakeDone_ = true;
      } else {

        executor_->add([&] {
          setOneRttKeys();
          phase_ = Phase::Established;
          handshakeDone_ = true;
          if (callback_) {
            callback_->onCryptoEventAvailable();
          }
        });
      }
    }
  }
