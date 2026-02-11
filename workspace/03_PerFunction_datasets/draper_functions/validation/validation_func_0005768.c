Start()
  {
    qDebug() << "Blame: Parsing logs";
    ParseLogs();
    qDebug() << "Blame: Checking public keys";
    CheckPublicKeys();
    if(!_set) {
      qDebug() << "Blame: Checking shuffle / data";
      CheckShuffle();
    }

    if(!_set) {
      qDebug() << "Blame: Checking go / no go";
      CheckVerification();
    }
    qDebug() << "Blame: Done";
  }
