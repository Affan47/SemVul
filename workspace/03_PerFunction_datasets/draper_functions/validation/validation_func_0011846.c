procgetbulk(const char* path, int32_t oflags,
                           const std::vector<std::string>& keys, bool px) {
  kc::TreeDB db;
  db.tune_logger(stdlogger(g_progname, &std::cerr));
  if (!db.open(path, kc::TreeDB::OREADER | oflags)) {
    dberrprint(&db, "DB::open failed");
    return 1;
  }
  bool err = false;
  std::map<std::string, std::string> recs;
  if (db.get_bulk(keys, &recs) >= 0) {
    std::map<std::string, std::string>::iterator it = recs.begin();
    std::map<std::string, std::string>::iterator itend = recs.end();
    while (it != itend) {
      printdata(it->first.data(), it->first.size(), px);
      oprintf("\t");
      printdata(it->second.data(), it->second.size(), px);
      oprintf("\n");
      ++it;
    }
  } else {
    dberrprint(&db, "DB::get_bulk failed");
    err = true;
  }
  if (!db.close()) {
    dberrprint(&db, "DB::close failed");
    err = true;
  }
  return err ? 1 : 0;
}
