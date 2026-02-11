ProcessConflicts()
  {
    QByteArray proof_messages;
    for(int i=0; i<_conflicts.count(); i++) {
      uint user_idx = _conflicts[i].GetUserIndex();
      uint server_idx = _conflicts[i].GetServerIndex();
      qDebug() << "Conflict <" << user_idx << "," << server_idx << ">";

      if(user_idx == server_idx) {
        qDebug() << "Conflict between same user and server -- blaming" << user_idx;
        AddBadMember(user_idx);
        FoundBadMembers();
      }

      if(user_idx == _user_idx) {
        qDebug() << "User" << _user_idx << "needs to send proof";
        SendUserProof(i, server_idx);
      }

      if(_is_server && server_idx == _server_idx) {
        qDebug() << "Server" << _server_idx << "needs to send proof";
        SendServerProof(i, user_idx);
      }
    }
  }
