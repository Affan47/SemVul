debuginfod_fetch_separate_debug_info (struct dwarf_section * section,
                                      char ** filename,
                                      void * file)
{
  size_t build_id_len;
  unsigned char * build_id;

  if (strcmp (section->uncompressed_name, ".gnu_debuglink") == 0)
    {

      build_id = get_build_id (file);
      build_id_len = 0;
    }
  else if (strcmp (section->uncompressed_name, ".gnu_debugaltlink") == 0)
    {

      unsigned int filelen;

      filelen = strnlen ((const char *)section->start, section->size);
      if (filelen == section->size)

        return false;

      build_id = section->start + filelen + 1;
      build_id_len = section->size - (filelen + 1);

      if (build_id_len == 0)
        return false;
    }
  else
    return false;

  if (build_id)
    {
      int fd;
      debuginfod_client * client;

      client = debuginfod_begin ();
      if (client == NULL)
        return false;


      fd = debuginfod_find_debuginfo (client, build_id, build_id_len, filename);
      debuginfod_end (client);


      if (build_id_len == 0)
        free (build_id);

      if (fd >= 0)
        {


          close (fd);
          return true;
        }
    }

  return false;
}
