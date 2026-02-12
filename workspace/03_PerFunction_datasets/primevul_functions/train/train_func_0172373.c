set_bool_option (
    int opt_idx,
    char_u *varp,
    int value,
    int opt_flags
)
{
  int old_value = *(int *)varp;


  if ((secure || sandbox != 0)
      && (options[opt_idx].flags & P_SECURE)) {
    return e_secure;
  }

  *(int *)varp = value;

  set_option_scriptID_idx(opt_idx, opt_flags, current_SID);


  if ((opt_flags & (OPT_LOCAL | OPT_GLOBAL)) == 0)
    *(int *)get_varp_scope(&(options[opt_idx]), OPT_GLOBAL) = value;


  if ((int *)varp == &p_force_on && p_force_on == FALSE) {
    p_force_on = TRUE;
    return e_unsupportedoption;
  }

  else if ((int *)varp == &p_force_off && p_force_off == TRUE) {
    p_force_off = FALSE;
    return e_unsupportedoption;
  }

  else if ((int *)varp == &curbuf->b_p_udf || (int *)varp == &p_udf) {


    if (curbuf->b_p_udf || p_udf) {
      char_u hash[UNDO_HASH_SIZE];
      buf_T       *save_curbuf = curbuf;

      for (curbuf = firstbuf; curbuf != NULL; curbuf = curbuf->b_next) {


        if ((curbuf == save_curbuf
             || (opt_flags & OPT_GLOBAL) || opt_flags == 0)
            && !curbufIsChanged() && curbuf->b_ml.ml_mfp != NULL) {
          u_compute_hash(hash);
          u_read_undo(NULL, hash, curbuf->b_fname);
        }
      }
      curbuf = save_curbuf;
    }
  } else if ((int *)varp == &curbuf->b_p_ro) {

    if (!curbuf->b_p_ro && (opt_flags & OPT_LOCAL) == 0)
      readonlymode = FALSE;


    if (curbuf->b_p_ro)
      curbuf->b_did_warn = false;

    redraw_titles();
  }

  else if ((int *)varp == &curbuf->b_p_ma) {
    redraw_titles();
  }

  else if ((int *)varp == &curbuf->b_p_eol) {
    redraw_titles();
  } else if ((int *)varp == &curbuf->b_p_fixeol) {

    redraw_titles();
  }

  else if ((int *)varp == &curbuf->b_p_bomb) {
    redraw_titles();
  }

  else if ((int *)varp == &curbuf->b_p_bin) {
    set_options_bin(old_value, curbuf->b_p_bin, opt_flags);
    redraw_titles();
  }

  else if ((int *)varp == &curbuf->b_p_bl && old_value != curbuf->b_p_bl) {
    apply_autocmds(curbuf->b_p_bl ? EVENT_BUFADD : EVENT_BUFDELETE,
        NULL, NULL, TRUE, curbuf);
  }

  else if ((int *)varp == (int *)&curbuf->b_p_swf) {
    if (curbuf->b_p_swf && p_uc)
      ml_open_file(curbuf);
    else


      mf_close_file(curbuf, true);
  }

  else if ((int *)varp == &p_terse) {
    char_u  *p;

    p = vim_strchr(p_shm, SHM_SEARCH);


    if (p_terse && p == NULL) {
      STRCPY(IObuff, p_shm);
      STRCAT(IObuff, "s");
      set_string_option_direct((char_u *)"shm", -1, IObuff, OPT_FREE, 0);
    }

    else if (!p_terse && p != NULL)
      STRMOVE(p, p + 1);
  }

  else if ((int *)varp == &p_paste) {
    paste_option_changed();
  }

  else if ((int *)varp == &p_im) {
    if (p_im) {
      if ((State & INSERT) == 0) {
        need_start_insertmode = true;
      }
      stop_insert_mode = false;
    } else if (old_value) {
      need_start_insertmode = false;
      stop_insert_mode = true;
      if (restart_edit != 0 && mode_displayed) {
        clear_cmdline = true;
      }
      restart_edit = 0;
    }
  }

  else if ((int *)varp == &p_ic && p_hls) {
    redraw_all_later(SOME_VALID);
  }

  else if ((int *)varp == &p_hls) {
    SET_NO_HLSEARCH(FALSE);
  }


  else if ((int *)varp == &curwin->w_p_scb) {
    if (curwin->w_p_scb) {
      do_check_scrollbind(FALSE);
      curwin->w_scbind_pos = curwin->w_topline;
    }
  }

  else if ((int *)varp == &curwin->w_p_pvw) {
    if (curwin->w_p_pvw) {
      FOR_ALL_WINDOWS_IN_TAB(win, curtab) {
        if (win->w_p_pvw && win != curwin) {
          curwin->w_p_pvw = FALSE;
          return (char_u *)N_("E590: A preview window already exists");
        }
      }
    }
  } else if (varp == (char_u *)&(curbuf->b_p_lisp)) {


    (void)buf_init_chartab(curbuf, false);
  } else if ((int *)varp == &p_title) {

    did_set_title(false);
  } else if ((int *)varp == &p_icon) {
    did_set_title(true);
  } else if ((int *)varp == &curbuf->b_changed) {
    if (!value) {
      save_file_ff(curbuf);
    }
    redraw_titles();
    modified_was_set = value;
  }

#ifdef BACKSLASH_IN_FILENAME
  else if ((int *)varp == &p_ssl) {
    if (p_ssl) {
      psepc = '/';
      psepcN = '\\';
      pseps[0] = '/';
    } else {
      psepc = '\\';
      psepcN = '/';
      pseps[0] = '\\';
    }


    buflist_slash_adjust();
    alist_slash_adjust();
    scriptnames_slash_adjust();
  }
#endif


  else if ((int *)varp == &curwin->w_p_wrap) {
    if (curwin->w_p_wrap)
      curwin->w_leftcol = 0;
  } else if ((int *)varp == &p_ea) {
    if (p_ea && !old_value) {
      win_equal(curwin, false, 0);
    }
  } else if ((int *)varp == &p_acd) {

    do_autochdir();
  }

  else if ((int *)varp == &curwin->w_p_diff) {

    diff_buf_adjust(curwin);
    if (foldmethodIsDiff(curwin))
      foldUpdateAll(curwin);
  }


  else if ((int *)varp == &curwin->w_p_spell) {
    if (curwin->w_p_spell) {
      char_u      *errmsg = did_set_spelllang(curwin);
      if (errmsg != NULL)
        EMSG(_(errmsg));
    }
  } else if ((int *)varp == &p_altkeymap) {
    if (old_value != p_altkeymap) {
      if (!p_altkeymap) {
        p_hkmap = p_fkmap;
        p_fkmap = 0;
      } else {
        p_fkmap = p_hkmap;
        p_hkmap = 0;
      }
      (void)init_chartab();
    }
  }


  if ((p_hkmap || p_fkmap) && p_altkeymap) {
    p_altkeymap = p_fkmap;
    curwin->w_p_arab = FALSE;
    (void)init_chartab();
  }


  if (p_hkmap && p_altkeymap) {
    p_altkeymap = 0;
    p_fkmap = 0;
    curwin->w_p_arab = FALSE;
    (void)init_chartab();
  }


  if (p_fkmap && !p_altkeymap) {
    p_altkeymap = 1;
    p_hkmap = 0;
    curwin->w_p_arab = FALSE;
    (void)init_chartab();
  }

  if ((int *)varp == &curwin->w_p_arab) {
    if (curwin->w_p_arab) {


      if (!p_tbidi) {

        if (!curwin->w_p_rl) {
          curwin->w_p_rl = TRUE;
          changed_window_setting();
        }


        if (!p_arshape) {
          p_arshape = TRUE;
          redraw_later_clear();
        }
      }


      if (STRCMP(p_enc, "utf-8") != 0) {
        static char *w_arabic = N_(
            "W17: Arabic requires UTF-8, do ':set encoding=utf-8'");

        msg_source(hl_attr(HLF_W));
        MSG_ATTR(_(w_arabic), hl_attr(HLF_W));
        set_vim_var_string(VV_WARNINGMSG, _(w_arabic), -1);
      }


      p_deco = TRUE;


      set_option_value((char_u *)"keymap", 0L, (char_u *)"arabic",
          OPT_LOCAL);
      p_altkeymap = 0;
      p_hkmap = 0;
      p_fkmap = 0;
      (void)init_chartab();
    } else {


      if (!p_tbidi) {

        if (curwin->w_p_rl) {
          curwin->w_p_rl = FALSE;
          changed_window_setting();
        }


      }


      curbuf->b_p_iminsert = B_IMODE_NONE;
      curbuf->b_p_imsearch = B_IMODE_USE_INSERT;
    }
  }


  options[opt_idx].flags |= P_WAS_SET;

  if (!starting) {
    char buf_old[2];
    char buf_new[2];
    char buf_type[7];
    vim_snprintf(buf_old, ARRAY_SIZE(buf_old), "%d",
                 old_value ? true: false);
    vim_snprintf(buf_new, ARRAY_SIZE(buf_new), "%d",
                 value ? true: false);
    vim_snprintf(buf_type, ARRAY_SIZE(buf_type), "%s",
                 (opt_flags & OPT_LOCAL) ? "local" : "global");
    set_vim_var_string(VV_OPTION_NEW, buf_new, -1);
    set_vim_var_string(VV_OPTION_OLD, buf_old, -1);
    set_vim_var_string(VV_OPTION_TYPE, buf_type, -1);
    apply_autocmds(EVENT_OPTIONSET,
                   (char_u *) options[opt_idx].fullname,
                   NULL, false, NULL);
    reset_v_option_vars();
  }

  comp_col();
  if (curwin->w_curswant != MAXCOL
      && (options[opt_idx].flags & (P_CURSWANT | P_RALL)) != 0)
    curwin->w_set_curswant = TRUE;
  check_redraw(options[opt_idx].flags);

  return NULL;
}
