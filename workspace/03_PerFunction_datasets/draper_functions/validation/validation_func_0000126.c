HandleData(const QSharedPointer<ISender> &from,
      const QVariantList &container)
  {
    if(container.size() < 2) {
      return;
    }

    QString type = container.at(0).toString();
    if(type == Request::RequestType ||
        type == Request::NotificationType)
    {
      HandleRequest(Request(_responder, from, container));
    } else if(type == Response::ResponseType) {
      HandleResponse(Response(from, container));
    } else {
      qDebug() << "Received an unknown Rpc type:" << type;
    }
  }
