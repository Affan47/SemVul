CheckDN(const std::string& url, const std::string& DN) {

    if (DN.empty())
      return false;

    std::string meta_file = _getMetaFileName(url);
    struct stat fileStat;
    if (!FileStat(meta_file, &fileStat, true)) {
      if (errno != ENOENT)
        logger.msg(ERROR, "Error reading meta file %s: %s", meta_file, StrError(errno));
      return false;
    }
    std::list<std::string> lines;
    if (!FileRead(meta_file, lines)) {
      logger.msg(ERROR, "Error opening meta file %s", meta_file);
      return false;
    }
    if (lines.empty()) {
      logger.msg(ERROR, "meta file %s is empty", meta_file);
      return false;
    }


    for (std::list<std::string>::iterator line = lines.begin(); line != lines.end(); ++line) {
      std::string::size_type space_pos = line->rfind(' ');
      if (line->substr(0, space_pos) == DN) {
        std::string exp_time = line->substr(space_pos + 1);
        if (Time(exp_time) > Time()) {
          logger.msg(VERBOSE, "DN %s is cached and is valid until %s for URL %s", DN, Time(exp_time).str(), url);
          return true;
        }
        else {
          logger.msg(VERBOSE, "DN %s is cached but has expired for URL %s", DN, url);
          return false;
        }
      }
    }
    return false;
  }
