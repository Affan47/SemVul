get_mode(bool privatemode, int arg)
{
  if (privatemode) {
    switch (arg) {
      when 1:
        return 2 - term.app_cursor_keys;
      when 66:
        return 2 - term.app_keypad;
      when 2:

        for (uint i = 0; i < lengthof(term.curs.csets); i++)
          if (term.curs.csets[i] != CSET_ASCII)
            return 2;
        return 1;
      when 3:
        return 2 - term.reset_132;
      when 5:
        return 2 - term.rvideo;
      when 6:
        return 2 - term.curs.origin;
      when 7:
        return 2 - term.autowrap;
      when 45:
        return 2 - term.rev_wrap;
      when 8:
        return 2 - term.auto_repeat;

      when 9:
        return 2 - (term.mouse_mode == MM_X10);
      when 12:
        return 2 - term.cursor_blinkmode;
      when 25:
        return 2 - term.cursor_on;
      when 30:
        return 2 - term.show_scrollbar;
      when 40:
        return 2 - term.deccolm_allowed;
      when 42:
        return 2 - term.decnrc_enabled;
      when 44:
        return 2 - term.margin_bell;
      when 67:
        return 2 - term.backspace_sends_bs;
      when 69:
        return 2 - term.lrmargmode;
      when 80:
        return 2 - !term.sixel_display;
      when 1000:
        return 2 - (term.mouse_mode == MM_VT200);
      when 1002:
        return 2 - (term.mouse_mode == MM_BTN_EVENT);
      when 1003:
        return 2 - (term.mouse_mode == MM_ANY_EVENT);
      when 1004:
        return 2 - term.report_focus;
      when 1005:
        return 2 - (term.mouse_enc == ME_UTF8);
      when 1006:
        return 2 - (term.mouse_enc == ME_XTERM_CSI);
      when 1016:
        return 2 - (term.mouse_enc == ME_PIXEL_CSI);
      when 1015:
        return 2 - (term.mouse_enc == ME_URXVT_CSI);
      when 1037:
        return 2 - term.delete_sends_del;
      when 1042:
        return 2 - term.bell_taskbar;
      when 1043:
        return 2 - term.bell_popup;
      when 47:
        return 2 - term.on_alt_screen;
      when 1047:
        return 2 - term.on_alt_screen;
      when 1048:
        return 4;
      when 1049:
        return 2 - term.on_alt_screen;
      when 1061:
        return 2 - term.vt220_keys;
      when 2004:
        return 2 - term.bracketed_paste;


      when 7700:
        return 2 - term.report_ambig_width;
      when 7711:
        return 2 - !!(term.lines[term.curs.y]->lattr & LATTR_MARKED);
      when 7727:
        return 2 - term.app_escape_key;
      when 7728:
        return 2 - term.escape_sends_fs;
      when 7730:
        return 2 - term.sixel_scrolls_left;
      when 7766:
        return 2 - term.show_scrollbar;
      when 7767:
        return 2 - term.report_font_changed;
      when 7783:
        return 2 - term.shortcut_override;
      when 1007:
        return 2 - term.wheel_reporting_xterm;
      when 7786:
        return 2 - term.wheel_reporting;
      when 7787:
        return 2 - term.app_wheel;
      when 7796:
        return 2 - !!(term.lines[term.curs.y]->lattr & LATTR_NOBIDI);
      when 77096:
        return 2 - term.disable_bidi;
      when 8452:
        return 2 - term.sixel_scrolls_right;
      when 77000 ... 77031: {
        int ctrl = arg - 77000;
        return 2 - !!(term.app_control & (1 << ctrl));
      }
      when 2500:
        return 2 - !!(term.curs.bidimode & LATTR_BOXMIRROR);
      when 2501:
        return 2 - !(term.curs.bidimode & LATTR_BIDISEL);
      otherwise:
        return 0;
    }
  }
  else {
    switch (arg) {
      when 4:
        return 2 - term.insert;
      when 8:
        return 2 - !(term.curs.bidimode & LATTR_NOBIDI);
      when 12:
        return 2 - !term.echoing;
      when 20:
        return 2 - term.newline_mode;
#ifdef support_Wyse_cursor_modes
      when 33:
        return 2 - (!term.cursor_blinkmode);
      when 34:
        if (term.cursor_type <= 1)
          return 2 - (term.cursor_type == 1);
        else
          return 0;
#endif
      otherwise:
        return 0;
    }
  }
}
