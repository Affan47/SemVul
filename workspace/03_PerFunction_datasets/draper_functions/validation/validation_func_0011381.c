io_thread(void)
{
  fd_set fds;
  unsigned char buf[16];
  struct timeval tv;

  ECA_LOG_MSG(ECA_LOGGER::user_objects, "Hey, in the I/O loop!");
  while(true) {
    if (running_rep.get() == 0 ||
	clients_rep[0]->is_open() != true) {
      usleep(50000);
      if (exit_request_rep.get() == 1) break;
      continue;
    }

    DBC_CHECK(clients_rep.size() > 0);
    DBC_CHECK(clients_rep[0]->supports_nonblocking_mode() == true);


    int fd = clients_rep[0]->poll_descriptor();

    FD_ZERO(&fds);
    FD_SET(fd, &fds);

    tv.tv_sec = 1;
    tv.tv_usec = 0;
    int retval = select(fd + 1 , &fds, NULL, NULL, &tv);


    int read_bytes = 0;
    if (retval) {
      if (FD_ISSET(fd, &fds) == true) {
	read_bytes = clients_rep[0]->read_bytes(buf, 16);

      }
    }

    if (read_bytes < 0) {
      std::cerr << "ERROR: Can't read from MIDI-device: "
		<< clients_rep[0]->label() << "." << std::endl;
      break;
    }
    else {

      for(int n = 0; n < read_bytes; n++) {
	buffer_rep.push_back(buf[n]);
	while(buffer_rep.size() > max_queue_size_rep) {
	  std::cerr << "(eca-midi) dropping midi bytes" << std::endl;
	  buffer_rep.pop_front();
	}
	for(unsigned int m = 0; m < handlers_rep.size(); m++) {
	  MIDI_HANDLER* p = handlers_rep[m];
	  if (p != 0) p->insert(buf[n]);
	}
      }
      parse_receive_queue();
    }

    if (stop_request_rep.get() == 1) {
      stop_request_rep.set(0);
      running_rep.set(0);
    }
  }
  ECA_LOG_MSG(ECA_LOGGER::system_objects, "exiting MIDI-server thread");
}
