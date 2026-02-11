GenerateMyCleartextMessage()
  {

    if(_looking_for_evidence == NotLookingForEvidence) {
      QPair<QByteArray, bool> pair = GetData(4096);

      const QByteArray cur_msg = _next_msg;
      _next_msg = pair.first;
      qDebug() << "GetData(4096) =" << _next_msg;

      QByteArray cleartext(8, 0);
      Serialization::WriteInt(_phase, cleartext, 0);
      Serialization::WriteInt(_next_msg.size(), cleartext, 4);
      cleartext.append(cur_msg);

      QByteArray sig = SignMessage(cleartext);

      cleartext.append(sig);


      cleartext.append('\0');

      _last_msg_cleartext = cleartext;

      QByteArray randomized = _message_randomizer.Randomize(cleartext);
      _last_msg = randomized;

      qDebug() << "RANDOMIZED:" << randomized.count();
      return randomized;

    } else if(_looking_for_evidence == LookingForEvidence) {


      QByteArray randomized = _message_randomizer.Randomize(_last_msg_cleartext);
      _last_msg = randomized;

      qDebug() << "RANDOMIZED:" << randomized.count();
      return randomized;

    } else if(_looking_for_evidence == FoundEvidence) {

      QSharedPointer<Dissent::Utils::Random> rand(_crypto_lib->GetRandomNumberGenerator());

      QByteArray msg(_last_msg_cleartext.count(), 0);
      rand->GenerateBlock(msg);

      return _message_randomizer.Randomize(msg);

    } else {
      qFatal("Should never reach here!");
      return QByteArray();
    }
  }
