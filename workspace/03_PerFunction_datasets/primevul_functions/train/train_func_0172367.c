void set_init_1(void)
{
  int opt_idx;

  langmap_init();


  p_cp = FALSE;


  {
    const char *shell = os_getenv("SHELL");
    if (shell != NULL) {
      set_string_default("sh", (char *) shell, false);
    }
  }


  {
# ifdef UNIX
    static char     *(names[4]) = {"", "TMPDIR", "TEMP", "TMP"};
# else
    static char     *(names[3]) = {"TMPDIR", "TEMP", "TMP"};
# endif
    int len;
    garray_T ga;

    ga_init(&ga, 1, 100);
    for (size_t n = 0; n < ARRAY_SIZE(names); ++n) {
      bool mustfree = true;
      char *p;
# ifdef UNIX
      if (*names[n] == NUL) {
        p = "/tmp";
        mustfree = false;
      }
      else
# endif
      p = vim_getenv(names[n]);
      if (p != NULL && *p != NUL) {

        len = (int)strlen(p) + 3;
        ga_grow(&ga, len);
        if (!GA_EMPTY(&ga))
          STRCAT(ga.ga_data, ",");
        STRCAT(ga.ga_data, p);
        add_pathsep(ga.ga_data);
        STRCAT(ga.ga_data, "*");
        ga.ga_len += len;
      }
      if(mustfree) {
        xfree(p);
      }
    }
    if (ga.ga_data != NULL) {
      set_string_default("bsk", ga.ga_data, true);
    }
  }


  opt_idx = findoption((char_u *)"maxmemtot");
  if (opt_idx >= 0) {
    {


      uint64_t available_kib = os_get_total_mem_kib();
      uintptr_t n = available_kib / 2 > UINTPTR_MAX
                    ? UINTPTR_MAX
                    : (uintptr_t)(available_kib /2);
      options[opt_idx].def_val[VI_DEFAULT] = (char_u *)n;
      opt_idx = findoption((char_u *)"maxmem");
      if (opt_idx >= 0) {
        options[opt_idx].def_val[VI_DEFAULT] = (char_u *)n;
      }
    }
  }


  {
    char_u  *cdpath;
    char_u  *buf;
    int i;
    int j;


    cdpath = (char_u *)vim_getenv("CDPATH");
    if (cdpath != NULL) {
      buf = xmalloc(2 * STRLEN(cdpath) + 2);
      {
        buf[0] = ',';
        j = 1;
        for (i = 0; cdpath[i] != NUL; ++i) {
          if (vim_ispathlistsep(cdpath[i]))
            buf[j++] = ',';
          else {
            if (cdpath[i] == ' ' || cdpath[i] == ',')
              buf[j++] = '\\';
            buf[j++] = cdpath[i];
          }
        }
        buf[j] = NUL;
        opt_idx = findoption((char_u *)"cdpath");
        if (opt_idx >= 0) {
          options[opt_idx].def_val[VI_DEFAULT] = buf;
          options[opt_idx].flags |= P_DEF_ALLOCED;
        } else
          xfree(buf);
      }
      xfree(cdpath);
    }
  }

#if defined(MSWIN) || defined(MAC)

  set_string_default("printencoding", "hp-roman8", false);
#endif


  set_string_default("printexpr",
#ifdef UNIX
                     "system(['lpr'] "
                            "+ (empty(&printdevice)?[]:['-P', &printdevice]) "
                            "+ [v:fname_in])"
                     ". delete(v:fname_in)"
                     "+ v:shell_error",
#elif defined(MSWIN)
                     "system(['copy', v:fname_in, "
                             "empty(&printdevice)?'LPT1':&printdevice])"
                     ". delete(v:fname_in)",
#else
                     "",
#endif
                     false);

  char *backupdir = stdpaths_user_data_subpath("backup", 0, true);
  const size_t backupdir_len = strlen(backupdir);
  backupdir = xrealloc(backupdir, backupdir_len + 3);
  memmove(backupdir + 2, backupdir, backupdir_len + 1);
  memmove(backupdir, ".,", 2);
  set_string_default("viewdir", stdpaths_user_data_subpath("view", 0, true),
                     true);
  set_string_default("backupdir", backupdir, true);
  set_string_default("directory", stdpaths_user_data_subpath("swap", 2, true),
                     true);
  set_string_default("undodir", stdpaths_user_data_subpath("undo", 0, true),
                     true);


  set_runtimepath_default();


  set_options_default(0);


  curbuf->b_p_initialized = true;
  curbuf->b_p_ar = -1;
  curbuf->b_p_ul = NO_LOCAL_UNDOLEVEL;
  check_buf_options(curbuf);
  check_win_options(curwin);
  check_options();


  set_options_default(OPT_FREE);


  last_status(false);


  didset_options();


  init_spell_chartab();


  for (opt_idx = 0; options[opt_idx].fullname; opt_idx++) {
    if (options[opt_idx].flags & P_NO_DEF_EXP) {
      continue;
    }
    char *p;
    if ((options[opt_idx].flags & P_GETTEXT)
        && options[opt_idx].var != NULL) {
      p = _(*(char **)options[opt_idx].var);
    } else {
      p = (char *) option_expand(opt_idx, NULL);
    }
    if (p != NULL) {
      p = xstrdup(p);
      *(char **)options[opt_idx].var = p;


      if (options[opt_idx].flags & P_DEF_ALLOCED)
        xfree(options[opt_idx].def_val[VI_DEFAULT]);
      options[opt_idx].def_val[VI_DEFAULT] = (char_u *) p;
      options[opt_idx].flags |= P_DEF_ALLOCED;
    }
  }

  save_file_ff(curbuf);


  if (os_env_exists("MLTERM"))
    set_option_value((char_u *)"tbidi", 1L, NULL, 0);

  didset_options2();


  char_u *p = enc_locale();
  if (p == NULL) {

      p = vim_strsave((char_u *)"utf-8");
  }
  fenc_default = p;

#ifdef HAVE_WORKING_LIBINTL


  (void)bind_textdomain_codeset(PROJECT_NAME, (char *)p_enc);
#endif


  set_helplang_default(get_mess_lang());
}
