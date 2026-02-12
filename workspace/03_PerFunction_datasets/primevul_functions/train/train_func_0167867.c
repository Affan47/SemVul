defaults (void)
{
  char *tmp;


  xzero (opt);

  opt.cookies = true;
  opt.verbose = -1;
  opt.ntry = 20;
  opt.reclevel = 5;
  opt.add_hostdir = true;
  opt.netrc = true;
  opt.ftp_glob = true;
  opt.htmlify = true;
  opt.http_keep_alive = true;
  opt.use_proxy = true;
  tmp = getenv ("no_proxy");
  if (tmp)
    opt.no_proxy = sepstring (tmp);
  opt.prefer_family = prefer_none;
  opt.allow_cache = true;

  opt.read_timeout = 900;
  opt.use_robots = true;

  opt.remove_listing = true;

  opt.dot_bytes = 1024;
  opt.dot_spacing = 10;
  opt.dots_in_line = 50;

  opt.dns_cache = true;
  opt.ftp_pasv = true;


  opt.retr_symlinks = true;

#ifdef HAVE_SSL
  opt.check_cert = true;
#endif


#if defined(WINDOWS) || defined(MSDOS) || defined(__CYGWIN__)
  opt.restrict_files_os = restrict_windows;
#else
  opt.restrict_files_os = restrict_unix;
#endif
  opt.restrict_files_ctrl = true;
  opt.restrict_files_nonascii = false;
  opt.restrict_files_case = restrict_no_case_restriction;

  opt.regex_type = regex_type_posix;

  opt.max_redirect = 20;

  opt.waitretry = 10;

#ifdef ENABLE_IRI
  opt.enable_iri = true;
#else
  opt.enable_iri = false;
#endif
  opt.locale = NULL;
  opt.encoding_remote = NULL;

  opt.useservertimestamps = true;
  opt.show_all_dns_entries = false;

  opt.warc_maxsize = 0;
#ifdef HAVE_LIBZ
  opt.warc_compression_enabled = true;
#else
  opt.warc_compression_enabled = false;
#endif
  opt.warc_digests_enabled = true;
  opt.warc_cdx_enabled = false;
  opt.warc_cdx_dedup_filename = NULL;
  opt.warc_tempdir = NULL;
  opt.warc_keep_log = true;


  opt.start_pos = -1;
  opt.show_progress = false;
  opt.noscroll = false;
}
