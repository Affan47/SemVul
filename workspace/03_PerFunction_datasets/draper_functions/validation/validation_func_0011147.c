bgav_init_video_decoders_real(bgav_options_t * opt)
  {
  int ret = 1;
  struct stat stat_buf;
  char test_filename[PATH_MAX];
  int i;


  for(i = 0; i < sizeof(real_codecs) / sizeof(real_codecs[0]); i++)
    {
    sprintf(test_filename, "%s/%s", bgav_dll_path_real, real_codecs[i].dll_name);
    if(!stat(test_filename, &stat_buf))
      bgav_video_decoder_register(&real_codecs[i].decoder);
    else
      {
      bgav_log(opt, BGAV_LOG_WARNING, LOG_DOMAIN,
               "Cannot find file %s, disabling %s",
               test_filename, real_codecs[i].decoder.name);
      ret = 0;
      }
    }
  return ret;
  }
