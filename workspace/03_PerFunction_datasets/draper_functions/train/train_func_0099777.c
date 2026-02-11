VerifyAll(const QVector<QSharedPointer<AsymmetricKey> > &keys,
      const QVector<QVector<QByteArray> > &onion, QBitArray &bad) const
  {
    if(keys.count() != onion.count() - 1) {
      qWarning() << "Incorrect key to onion layers ratio: " << keys.count() <<
        ":" << onion.count();
      return false;
    }

    if(keys.count() != bad.count()) {
      bad = QBitArray(keys.count(), false);
    }

    bool res = true;
    for(int idx = 0; idx < keys.count(); idx++) {
      if(!VerifyOne(keys[idx], onion[idx], onion[idx + 1])) {
        bad[idx] = true;
        res = false;
      }
    }

    return res;
  }
