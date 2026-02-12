void MonClient::_resend_mon_commands()
{

  map<uint64_t,MonCommand*>::iterator p = mon_commands.begin();
  while (p != mon_commands.end()) {
    auto cmd = p->second;
    ++p;
    _send_command(cmd);
  }
}
