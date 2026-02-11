CreateEdge(const Request &request)
  {
    QVariantHash msg = request.GetData().toHash();

    Id remote_peer = Id(msg.value("x_peer_id").toString());
    if(remote_peer == Id::Zero()) {
      request.Failed(Response::InvalidInput, "Unparseable peerid");
      return;
    }

    bool ok;
    int x_edge_id = msg.value("x_edge_id").toInt(&ok);
    if(!ok) {
      request.Failed(Response::InvalidInput, "Invalid out_edge_id");
      return;
    }

    int y_edge_id = GetEdgeId();
    QSharedPointer<RelayEdge> redge(new RelayEdge(GetAddress(),
          RelayAddress(remote_peer), false, _rpc,
          request.GetFrom(), y_edge_id, x_edge_id));
    redge->SetSharedPointer(redge);

    _edges[y_edge_id] = redge;
    QVariantHash response;
    response["x_edge_id"] = y_edge_id;
    response["y_edge_id"] = x_edge_id;
    request.Respond(response);

    ProcessNewEdge(redge);
  }
