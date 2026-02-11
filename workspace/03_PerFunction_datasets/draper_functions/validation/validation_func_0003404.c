ServerStateResponse(const Response &response)
  {
    QSharedPointer<Connection> con =  response.GetFrom().dynamicCast<Connection>();
    if(!con) {
      qCritical() << "Received an rpc request from a non-connection.";
      return;
    }
    Id remote = con->GetRemoteId();

    QVariantHash msg = response.GetData().toHash();

    QHash<QByteArray, QUrl> id_to_addr;
    QDataStream stream(msg.value("list").toByteArray());
    stream >> id_to_addr;
    int cons = msg.value("connections").toInt();

    if(IsServer()) {
      ServerHandleServerStateResponse(remote, id_to_addr, cons);
    } else {
      ClientHandleServerStateResponse(remote, id_to_addr, cons);
    }
  }
