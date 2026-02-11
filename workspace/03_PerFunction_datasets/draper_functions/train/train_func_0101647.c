ProcessMessages()
  {
    uint size = GetGroup().Count();

    QByteArray cleartext(_expected_bulk_size, 0);


    QVector<int> bad_users;
    CheckCommits(_user_commits, _user_message_digests, bad_users);
    if(bad_users.count()) {
      AddBadMembers(bad_users);
      FoundBadMembers();
      return;
    }


    QVector<int> bad_servers;
    CheckCommits(_server_commits, _server_message_digests, bad_servers);
    if(bad_servers.count()) {
      AddBadMembers(bad_servers);
      FoundBadMembers();
      return;
    }

    for(int idx=0; idx<_user_messages.count(); idx++) {
      Xor(cleartext, cleartext, _user_messages[idx]);
    }

    for(int idx=0; idx<_server_messages.count(); idx++) {
      Xor(cleartext, cleartext, _server_messages[idx]);
    }

    SaveMessagesToHistory();

    uint msg_idx = 0;
    for(uint slot_idx = 0; slot_idx < size; slot_idx++) {
      int length = _message_lengths[slot_idx] + _header_lengths[slot_idx];
      QByteArray tcleartext = cleartext.mid(msg_idx, length);
      if(_bad_slots.contains(slot_idx)) {
        qDebug() << "Skipping bad slot" << slot_idx;
      } else {
        QByteArray msg = ProcessMessage(tcleartext, slot_idx);
        if(!msg.isEmpty()) {
          PushData(GetSharedPointer(), msg);
        }
      }
      msg_idx += length;
    }
  }
