open_server_socket(void)
{
  DBC_REQUIRE(server_listening_rep != true);
  DBC_REQUIRE(srvfd_rep > 0);

  int val = 1;
  int ret = setsockopt(srvfd_rep, SOL_SOCKET, SO_REUSEADDR, (void *)&val, sizeof(val));
  if (ret < 0)
    std::cerr << "setsockopt() failed." << endl;


  int res = 0;
  if (unix_sockets_rep == true)
    res = bind(srvfd_rep, (struct sockaddr*)&addr_un_rep, sizeof(addr_un_rep));
  else
    res = bind(srvfd_rep, (struct sockaddr*)&addr_in_rep, sizeof(addr_in_rep));

  if (res == 0) {
    res = listen(srvfd_rep, 5);
    if (res == 0) {
      int res = fcntl(srvfd_rep, F_SETFL, O_NONBLOCK);
      if (res == -1)
	std::cerr << "fcntl() failed." << endl;

      NETECI_DEBUG(std::cout << "server socket created." << endl);
      server_listening_rep = true;
    }
    else
      std::cerr << "listen() failed." << endl;
  }
  else {
    if (unix_sockets_rep == true) {
      unlink(socketpath_rep.c_str());
    }
    socketpath_rep.resize(0);
    std::cerr << "bind() failed." << endl;
  }

  DBC_ENSURE((unix_sockets_rep == true &&
	     (((server_listening_rep == true && socketpath_rep.size() > 0) ||
	       (server_listening_rep != true && socketpath_rep.size() == 0)))) ||
	     (unix_sockets_rep != true));
}
