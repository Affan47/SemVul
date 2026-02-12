set_modes(bool state)
{
  for (uint i = 0; i < term.csi_argc; i++) {
    uint arg = term.csi_argv[i];
    if (term.esc_mod) {
      if (*cfg.suppress_dec && contains(cfg.suppress_dec, arg))
        ;
      else
      switch (arg) {
        when 1:
          term.app_cursor_keys = state;
        when 66:
          term.app_keypad = state;
        when 2:
          if (state) {

            for (uint i = 0; i < lengthof(term.curs.csets); i++)
              term.curs.csets[i] = CSET_ASCII;
            term.curs.cset_single = CSET_ASCII;
            term_update_cs();
          }
          else
            term.vt52_mode = 1;
        when 3:
          if (term.deccolm_allowed) {
            term.selected = false;
            win_set_chars(term.rows, state ? 132 : 80);
            term.reset_132 = state;
            term.marg_top = 0;
            term.marg_bot = term.rows - 1;
            term.marg_left = 0;
            term.marg_right = term.cols - 1;
            move(0, 0, 0);
            if (!term.deccolm_noclear)
              term_erase(false, false, true, true);
          }
        when 5:
          if (state != term.rvideo) {
            term.rvideo = state;
            win_invalidate_all(false);
          }
        when 6:
          term.curs.origin = state;
          if (state)
            move(term.marg_left, term.marg_top, 0);
          else
            move(0, 0, 0);
        when 7:
          term.autowrap = state;
          term.curs.wrapnext = false;
        when 45:
          term.rev_wrap = state;
          term.curs.wrapnext = false;
        when 8:
          term.auto_repeat = state;
        when 9:
          term.mouse_mode = state ? MM_X10 : 0;
          win_update_mouse();
        when 12:
          term.cursor_blinkmode = state;
          term.cursor_invalid = true;
          term_schedule_cblink();
        when 25:
          term.cursor_on = state;

        when 30:
          if (state != term.show_scrollbar) {
            term.show_scrollbar = state;
            win_update_scrollbar(false);
          }
        when 38:
          if (state) {
            tek_mode = TEKMODE_ALPHA;
            tek_init(true, cfg.tek_glow);
          }
        when 40:
          term.deccolm_allowed = state;
        when 95:
          term.deccolm_noclear = state;
        when 42:
          term.decnrc_enabled = state;
        when 44:
          term.margin_bell = state;
        when 67:
          term.backspace_sends_bs = state;
        when 69:
          term.lrmargmode = state;
          if (state) {
            for (int i = 0; i < term.rows; i++) {
              termline *line = term.lines[i];
              line->lattr = LATTR_NORM;
            }
          }
          else {
            term.marg_left = 0;
            term.marg_right = term.cols - 1;
          }
        when 80:
          term.sixel_display = !state;
        when 1000:
          term.mouse_mode = state ? MM_VT200 : 0;
          win_update_mouse();
        when 1002:
          term.mouse_mode = state ? MM_BTN_EVENT : 0;
          win_update_mouse();
        when 1003:
          term.mouse_mode = state ? MM_ANY_EVENT : 0;
          win_update_mouse();
        when 1004:
          term.report_focus = state;
        when 1005:
          term.mouse_enc = state ? ME_UTF8 : 0;
        when 1006:
          term.mouse_enc = state ? ME_XTERM_CSI : 0;
        when 1016:
          term.mouse_enc = state ? ME_PIXEL_CSI : 0;
        when 1015:
          term.mouse_enc = state ? ME_URXVT_CSI : 0;
        when 1037:
          term.delete_sends_del = state;
        when 1042:
          term.bell_taskbar = state;
        when 1043:
          term.bell_popup = state;
        when 47:
          if (!cfg.disable_alternate_screen) {
            term.selected = false;
            term_switch_screen(state, false);
            term.disptop = 0;
          }
        when 1047:
          if (!cfg.disable_alternate_screen) {
            term.selected = false;
            term_switch_screen(state, true);
            term.disptop = 0;
          }
        when 1046:
          if (term.on_alt_screen && !state)
            term_switch_screen(false, false);
          cfg.disable_alternate_screen = !state;
        when 1048:
          if (!cfg.disable_alternate_screen) {
            if (state)
              save_cursor();
            else
              restore_cursor();
          }
        when 1049:
          if (!cfg.disable_alternate_screen) {
            if (state)
              save_cursor();
            term.selected = false;
            term_switch_screen(state, true);
            if (!state)
              restore_cursor();
            term.disptop = 0;
          }
        when 1061:
          term.vt220_keys = state;
        when 2004:
          term.bracketed_paste = state;


        when 7700:
          term.report_ambig_width = state;
        when 7711:
          if (state)
            term.lines[term.curs.y]->lattr |= LATTR_MARKED;
          else
            term.lines[term.curs.y]->lattr |= LATTR_UNMARKED;
        when 7727:
          term.app_escape_key = state;
        when 7728:
          term.escape_sends_fs = state;
        when 7730:


          term.sixel_scrolls_left = state;
        when 7766:
          if (cfg.scrollbar && state != term.show_scrollbar) {
            term.show_scrollbar = state;
            win_update_scrollbar(true);
          }
        when 7767:
          term.report_font_changed = state;
        when 7783:
          term.shortcut_override = state;
        when 1007:
          term.wheel_reporting_xterm = state;
        when 7786:
          term.wheel_reporting = state;
        when 7787:
          term.app_wheel = state;
        when 7796:
          if (state)
            term.lines[term.curs.y]->lattr |= LATTR_NOBIDI;
          else
            term.lines[term.curs.y]->lattr &= ~LATTR_NOBIDI;
        when 77096:
          term.disable_bidi = state;
        when 8452:


          term.sixel_scrolls_right = state;
        when 77000 ... 77031: {
          int ctrl = arg - 77000;
          term.app_control = (term.app_control & ~(1 << ctrl)) | (state << ctrl);
        }
        when 2500:
          if (state)
            term.curs.bidimode |= LATTR_BOXMIRROR;
          else
            term.curs.bidimode &= ~LATTR_BOXMIRROR;
        when 2501:
          if (state)
            term.curs.bidimode &= ~LATTR_BIDISEL;
          else
            term.curs.bidimode |= LATTR_BIDISEL;
      }
    }
    else {
      switch (arg) {
        when 4:
          term.insert = state;
        when 8:
          if (state)
            term.curs.bidimode &= ~LATTR_NOBIDI;
          else
            term.curs.bidimode |= LATTR_NOBIDI;
        when 12:
          term.echoing = !state;
        when 20:
          term.newline_mode = state;
#ifdef support_Wyse_cursor_modes
        when 33:
          term.cursor_blinkmode = !state;
          term.cursor_invalid = true;
          term_schedule_cblink();
        when 34:
          term.cursor_type = state;
          term.cursor_blinkmode = false;
          term.cursor_invalid = true;
          term_schedule_cblink();
#endif
      }
    }
  }
}
