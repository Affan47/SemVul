void check_config_file(BOOL force) {
   struct stat cfg_stat;

   if (force) {
      parse_config_file(config_file);
      return;
   }


   if (stat(config_file, &cfg_stat) == 0) {
      if (cfgfile_mtime < cfg_stat.st_mtime) {
         cfgfile_mtime = cfg_stat.st_mtime;
         parse_config_file(config_file);
      }
   } else
      eprintf("Cannot stat() config file \"%s\": %s\n", config_file, strerror(errno));
}
