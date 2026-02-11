print_iso9660_recurse (CdIo_t *p_cdio, const char pathname[],
                       cdio_fs_anal_t fs)
{
  CdioList_t *p_entlist;
  CdioList_t *p_dirlist =  _cdio_list_new ();
  CdioListNode_t *entnode;
  uint8_t i_joliet_level;
  char *translated_name = (char *) malloc(4096);
  size_t translated_name_size = 4096;

  i_joliet_level = (opts.no_joliet)
    ? 0
    : cdio_get_joliet_level(p_cdio);

  p_entlist = iso9660_fs_readdir (p_cdio, pathname, false);

  printf ("%s:\n", pathname);

  if (NULL == p_entlist) {
    report( stderr, "Error getting above directory information\n" );
    free(translated_name);
    free(p_dirlist);
    return;
  }


  _CDIO_LIST_FOREACH (entnode, p_entlist)
    {
      iso9660_stat_t *p_statbuf = _cdio_list_node_data (entnode);
      char *psz_iso_name = p_statbuf->filename;
      char _fullname[4096] = { 0, };
       if (strlen(psz_iso_name) >= translated_name_size) {
         translated_name_size = strlen(psz_iso_name)+1;
         free(translated_name);
         translated_name = (char *) malloc(translated_name_size);
         if (!translated_name) {
           report( stderr, "Error allocating memory\n" );
           return;
         }
       }

      if (yep != p_statbuf->rr.b3_rock || 1 == opts.no_rock_ridge) {
        iso9660_name_translate_ext(psz_iso_name, translated_name,
                                   i_joliet_level);
      }


      snprintf (_fullname, sizeof (_fullname), "%s%s", pathname,
                psz_iso_name);

      strncat (_fullname, "/", sizeof (_fullname));

      if (p_statbuf->type == _STAT_DIR
          && strcmp (psz_iso_name, ".")
          && strcmp (psz_iso_name, ".."))
        _cdio_list_append (p_dirlist, strdup (_fullname));

      print_fs_attrs(p_statbuf, 0 == opts.no_rock_ridge, fs & CDIO_FS_ANAL_XA,
                     psz_iso_name, translated_name);
      if (p_statbuf->rr.i_symlink) {
        free(p_statbuf->rr.psz_symlink);
        p_statbuf->rr.i_symlink = 0;
      }
    }
    free (translated_name);

  _cdio_list_free (p_entlist, true);

  printf ("\n");


  _CDIO_LIST_FOREACH (entnode, p_dirlist)
    {
      char *_fullname = _cdio_list_node_data (entnode);

      print_iso9660_recurse (p_cdio, _fullname, fs);
    }

  _cdio_list_free (p_dirlist, true);
}
