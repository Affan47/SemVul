CreateEdgeListener(const Address &addr)
  {
    Callback cb = _type_to_callback[addr.GetType()];
    if(cb == 0) {
      qCritical() << "No such type registered:" << addr.GetType();
      return 0;
    }
    return cb(addr);
  }
