ReceiveLine() {
  std::string ret;
  while (1) {
    char r;
    int result = recv(s_, &r, 1, MSG_WAITALL);
    switch(result) {
      case 0:


  		if (DEBUG) std::cerr << host << ":" << port << " -> " << ret << endl;
        return ret;
      case -1:
        return "";


    }

    ret += r;
    if (r == '\n') {
  		if (DEBUG) std::cerr << host << ":" << port << " -> " << ret;
        return ret;
    }
  }
}
