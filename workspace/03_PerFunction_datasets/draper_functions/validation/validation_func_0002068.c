OnPing() {


  UpdateConnectionStates();


  Connection* conn = FindNextPingableConnection();
  if (conn)
    conn->Ping(talk_base::Time());


  uint32 delay = writable() ? WRITABLE_DELAY : UNWRITABLE_DELAY;
  thread()->PostDelayed(delay, this, MSG_PING);
}
