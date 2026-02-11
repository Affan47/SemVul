config_vo(std::list<AuthVO>& vos,const std::string& cmd,std::string& rest) {
    if(cmd != "vo") return 1;
    std::string voname = config_next_arg(rest);
    std::string vofile = config_next_arg(rest);
    if((voname.length() == 0) || (vofile.length() == 0)) {
      return -1;
    };
    vos.push_back(AuthVO(voname,vofile));
    return 0;
  }
