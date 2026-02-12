do_csi(uchar c)
{
  term_cursor *curs = &term.curs;
  int arg0 = term.csi_argv[0], arg1 = term.csi_argv[1];
  if (arg0 < 0)
    arg0 = 0;
  if (arg1 < 0)
    arg1 = 0;
  int arg0_def1 = arg0 ?: 1;

  if (term.esc_mod == 0xFF && esc_mod0 == '?' && esc_mod1 == '$' && c == 'p')
    term.esc_mod = '$';

  switch (CPAIR(term.esc_mod, c)) {
    when CPAIR('!', 'p'):
      term_reset(false);
    when 'b': {
      cattr cur_attr = term.curs.attr;
      term.curs.attr = last_attr;
      wchar h = last_high, c = last_char;
      for (int i = 0; i < arg0_def1; i++)
        write_ucschar(h, c, last_width);
      term.curs.attr = cur_attr;
    }
    when 'A':
      move(curs->x, curs->y - arg0_def1, 1);
    when 'e':
      move(curs->x, curs->y + arg0_def1, 1);
    when 'B':
      move(curs->x, curs->y + arg0_def1, 1);
    when 'c':
      if (!arg0)
        write_primary_da();
    when CPAIR('>', 'c'):
      if (!arg0) {
        if (cfg.charwidth % 10)
          child_printf("\e[>77;%u;%uc", DECIMAL_VERSION, UNICODE_VERSION);
        else
          child_printf("\e[>77;%u;0c", DECIMAL_VERSION);
      }
    when CPAIR('>', 'q'):
      if (!arg0)
        child_printf("\eP>|%s %s\e\\", APPNAME, VERSION);
    when 'a':
      move(curs->x + arg0_def1, curs->y, 1);
    when 'C':
      move(curs->x + arg0_def1, curs->y, 1);
    when 'D':
      if (arg0_def1 > curs->x) {
        arg0_def1 -= curs->x + 1;
        move(0, curs->y, 1);
        write_backspace();
        move(curs->x - arg0_def1, curs->y, 1);
      }
      else
        move(curs->x - arg0_def1, curs->y, 1);
      enable_progress();
    when 'E':
      move(0, curs->y + arg0_def1, 1);
    when 'F':
      move(0, curs->y - arg0_def1, 1);
    when 'G' or '`': {
      short x = (curs->origin ? term.marg_left : 0) + arg0_def1 - 1;
      if (x < curs->x)
        enable_progress();
      move(x, curs->y, curs->origin ? 2 : 0);
    }
    when 'd':
      move(curs->x,
           (curs->origin ? term.marg_top : 0) + arg0_def1 - 1,
           curs->origin ? 2 : 0);
    when 'H' or 'f':
      move((curs->origin ? term.marg_left : 0) + (arg1 ?: 1) - 1,
           (curs->origin ? term.marg_top : 0) + arg0_def1 - 1,
           curs->origin ? 2 : 0);
    when 'I':
      for (int i = 0; i < arg0_def1; i++)
        write_tab();
    when 'J' or CPAIR('?', 'J'):
      if (arg0 == 3) {

        term_clear_scrollback();
        term.disptop = 0;
      }
      else if (arg0 <= 2) {
        bool above = arg0 == 1 || arg0 == 2;
        bool below = arg0 == 0 || arg0 == 2;
        term_erase(term.esc_mod, false, above, below);
      }
    when 'K' or CPAIR('?', 'K'):
      if (arg0 <= 2) {
        bool right = arg0 == 0 || arg0 == 2;
        bool left  = arg0 == 1 || arg0 == 2;
        term_erase(term.esc_mod, true, left, right);
      }
    when 'L':
      if (curs->y >= term.marg_top && curs->y <= term.marg_bot
       && curs->x >= term.marg_left && curs->x <= term.marg_right
         )
      {
        term_do_scroll(curs->y, term.marg_bot, -arg0_def1, false);
        curs->x = term.marg_left;
      }
    when 'M':
      if (curs->y >= term.marg_top && curs->y <= term.marg_bot
       && curs->x >= term.marg_left && curs->x <= term.marg_right
         )
      {
        term_do_scroll(curs->y, term.marg_bot, arg0_def1, true);
        curs->x = term.marg_left;
      }
    when '@':
      insert_char(arg0_def1);
    when 'P':
      insert_char(-arg0_def1);
    when 'h' or CPAIR('?', 'h'):
      set_modes(true);
    when 'l' or CPAIR('?', 'l'):
      set_modes(false);
    when CPAIR('?', 's'): {
      int arg = term.csi_argv[0];
      int val = get_mode(true, arg);
      if (val)
        push_mode(arg, val);
    }
    when CPAIR('?', 'r'): {
      int arg = term.csi_argv[0];
      int val = pop_mode(arg);
      if (val >= 0) {
        term.csi_argc = 1;
        set_modes(val & 1);
      }
    }
    when CPAIR('#', '{') or CPAIR('#', 'p'): {
      cattr ca = term.curs.attr;
      cattrflags caflagsmask = 0;

      void set_push(int attr) {
        switch (attr) {
          when 1: caflagsmask |= ATTR_BOLD | ATTR_SHADOW;
          when 2: caflagsmask |= ATTR_DIM;
          when 3: caflagsmask |= ATTR_ITALIC;
          when 4 or 21: caflagsmask |= UNDER_MASK;
          when 5 or 6: caflagsmask |= ATTR_BLINK | ATTR_BLINK2;
          when 7: caflagsmask |= ATTR_REVERSE;
          when 8: caflagsmask |= ATTR_INVISIBLE | ATTR_OVERSTRIKE;
          when 9: caflagsmask |= ATTR_STRIKEOUT;
          when 20: caflagsmask |= FONTFAM_MASK;
          when 53: caflagsmask |= ATTR_OVERL;
          when 58: caflagsmask |= ATTR_ULCOLOUR;
          when 30 or 10: caflagsmask |= ATTR_FGMASK;
          when 31 or 11: caflagsmask |= ATTR_BGMASK;
          when 73: caflagsmask |= ATTR_SUPERSCR;
          when 74: caflagsmask |= ATTR_SUBSCR;
        }
      }

      if (!term.csi_argv_defined[0])
        for (int a = 1; a < 90; a++)
          set_push(a);
      else
        for (uint i = 0; i < term.csi_argc; i++) {

          set_push(term.csi_argv[i]);
        }
      if ((ca.attr & caflagsmask & ATTR_FGMASK) != TRUE_COLOUR)
        ca.truefg = 0;
      if ((ca.attr & caflagsmask & ATTR_BGMASK) != TRUE_COLOUR << ATTR_BGSHIFT)
        ca.truebg = 0;
      if (!(caflagsmask & ATTR_ULCOLOUR))
        ca.ulcolr = (colour)-1;

      push_attrs(ca, caflagsmask);
    }
    when CPAIR('#', '}') or CPAIR('#', 'q'): {

      cattr ca;
      cattrflags caflagsmask;
      if (pop_attrs(&ca, &caflagsmask)) {

        term.curs.attr.attr = (term.curs.attr.attr & ~caflagsmask)
                              | (ca.attr & caflagsmask);
        if ((ca.attr & caflagsmask & ATTR_FGMASK) == TRUE_COLOUR)
          term.curs.attr.truefg = ca.truefg;
        if ((ca.attr & caflagsmask & ATTR_BGMASK) == TRUE_COLOUR << ATTR_BGSHIFT)
          term.curs.attr.truebg = ca.truebg;
        if (caflagsmask & ATTR_ULCOLOUR)
          term.curs.attr.ulcolr = ca.ulcolr;
      }
    }
    when CPAIR('#', 'P'):
      push_colours(arg0);
    when CPAIR('#', 'Q'):
      pop_colours(arg0);
      win_invalidate_all(false);
    when CPAIR('#', 'R'):
      child_printf("\e[?%d;%d#Q", colours_cur, colours_num);
    when CPAIR('$', 'p'): {
      int arg = term.csi_argv[0];
      child_printf("\e[%s%u;%u$y",
                   esc_mod0 ? "?" : "",
                   arg,
                   get_mode(esc_mod0, arg));
    }
    when 'i' or CPAIR('?', 'i'):
      if (arg0 == 5 && *cfg.printer) {
        term.printing = true;
        term.only_printing = !term.esc_mod;
        term.print_state = 0;
        if (*cfg.printer == '*')
          printer_start_job(printer_get_default());
        else
          printer_start_job(cfg.printer);
      }
      else if (arg0 == 4 && term.printing) {

        while (term.printbuf[--term.printbuf_pos] != '\e');
        term_print_finish();
      }
      else if (arg0 == 10 && !term.esc_mod) {
        term_export_html(false);
      }
#ifdef support_SVG
      else if (arg0 == 11 && !term.esc_mod) {
        term_export_svg();
      }
#endif
      else if (arg0 == 12 && !term.esc_mod) {
        term_save_image();
      }
      else if (arg0 == 0 && !term.esc_mod) {
        print_screen();
      }
    when 'g':
      if (!arg0)
        term.tabs[curs->x] = false;
      else if (arg0 == 3) {
        for (int i = 0; i < term.cols; i++)
          term.tabs[i] = false;
        term.newtab = 0;
      }
    when 'r': {
      int top = arg0_def1 - 1;
      int bot = (arg1 ? min(arg1, term.rows) : term.rows) - 1;
      if (bot > top) {
        term.marg_top = top;
        term.marg_bot = bot;
        curs->x = curs->origin ? term.marg_left : 0;
        curs->y = curs->origin ? term.marg_top : 0;
      }
    }
    when 's':
      if (term.lrmargmode) {
        int left = arg0_def1 - 1;
        int right = (arg1 ? min(arg1, term.cols) : term.cols) - 1;
        if (right > left) {
          term.marg_left = left;
          term.marg_right = right;
          curs->x = curs->origin ? term.marg_left : 0;
          curs->y = curs->origin ? term.marg_top : 0;
        }
      }
      else
        save_cursor();
    when 'u':
      restore_cursor();
    when 'm':
      do_sgr();
    when 't':

      if (arg0 >= 24) {
        if (*cfg.suppress_win && contains(cfg.suppress_win, 24))
          ;
        else {
          win_set_chars(arg0, term.cols);
          term.selected = false;
        }
      }
      else
        do_winop();
    when 'S':
      term_do_scroll(term.marg_top, term.marg_bot, arg0_def1, true);
      curs->wrapnext = false;
    when 'T':

      if (term.csi_argc <= 1) {
        term_do_scroll(term.marg_top, term.marg_bot, -arg0_def1, true);
        curs->wrapnext = false;
      }
    when CPAIR('*', '|'):

      win_set_chars(arg0 ?: cfg.rows, term.cols);
      term.selected = false;
    when CPAIR('$', '|'):

      win_set_chars(term.rows, arg0 ?: cfg.cols);
      term.selected = false;
    when 'X': {
      termline *line = term.lines[curs->y];
      int cols = min(line->cols, line->size);
      int n = min(arg0_def1, cols - curs->x);
      if (n > 0) {
        int p = curs->x;
        term_check_boundary(curs->x, curs->y);
        term_check_boundary(curs->x + n, curs->y);
        while (n--)
          line->chars[p++] = term.erase_char;
      }
    }
    when 'x':
      if (arg0 <= 1)
        child_printf("\e[%u;1;1;120;120;1;0x", arg0 + 2);
    when 'Z': {
      int n = arg0_def1;
      while (--n >= 0 && curs->x > 0) {
        do
          curs->x--;
        while (curs->x > 0 && !term.tabs[curs->x]);
      }
      enable_progress();
    }
    when CPAIR('$', 'w'):
      if (arg0 == 2) {
        child_printf("\eP2$");
        char sep = 'u';
        for (int i = 0; i < term.cols; i++)
          if (term.tabs[i]) {
            child_printf("%c%d", sep, i + 1);
            sep = '/';
          }
        child_printf("\e\\");
      }
    when CPAIR('>', 'm'):

      if (!arg0)
        term.modify_other_keys = 0;
      else if (arg0 == 4)
        term.modify_other_keys = arg1;
    when CPAIR('>', 'p'):
      if (arg0 == 0)
        term.hide_mouse = false;
      else if (arg0 == 2)
        term.hide_mouse = true;
    when CPAIR('>', 'n'):

      if (arg0 == 4)
        term.modify_other_keys = 0;
    when CPAIR(' ', 'q'):
      term.cursor_type = arg0 ? (arg0 - 1) / 2 : -1;
      term.cursor_blinks = arg0 ? arg0 % 2 : -1;
      if (term.cursor_blinks)
        term.cursor_blink_interval = arg1;
      term.cursor_invalid = true;
      term_schedule_cblink();
    when CPAIR('?', 'c'):
      term.cursor_size = arg0;
    when CPAIR('"', 'q'):
      switch (arg0) {
        when 0 or 2: term.curs.attr.attr &= ~ATTR_PROTECTED;
        when 1: term.curs.attr.attr |= ATTR_PROTECTED;
      }
    when 'n':
      if (arg0 == 6)
        child_printf("\e[%d;%dR",
                     curs->y + 1 - (curs->origin ? term.marg_top : 0),
                     curs->x + 1 - (curs->origin ? term.marg_left : 0));
      else if (arg0 == 5)
        child_write("\e[0n", 4);
    when CPAIR('?', 'n'):
      switch (arg0) {
        when 6:
          child_printf("\e[?%d;%dR",
                       curs->y + 1 - (curs->origin ? term.marg_top : 0),
                       curs->x + 1 - (curs->origin ? term.marg_left : 0));
        when 15:
          child_printf("\e[?%un", 11 - !!*cfg.printer);

        when 53 or 55:
          child_printf("\e[?53n");
        when 56:
          child_printf("\e[?57;1n");
      }

    when CPAIR('\'', 'z'): {
      switch (arg0) {
        when 0:
          if (term.mouse_mode == MM_LOCATOR) {
            term.mouse_mode = 0;
            win_update_mouse();
          }
          term.locator_1_enabled = false;
        when 1:
          term.mouse_mode = MM_LOCATOR;
          win_update_mouse();
        when 2:
          term.locator_1_enabled = true;
          win_update_mouse();
      }
      switch (arg1) {
        when 0 or 2:
          term.locator_by_pixels = false;
        when 1:
          term.locator_by_pixels = true;
      }
      term.locator_rectangle = false;
    }
    when CPAIR('\'', '{'): {
      for (uint i = 0; i < term.csi_argc; i++)
        switch (term.csi_argv[i]) {
          when 0: term.locator_report_up = term.locator_report_dn = false;
          when 1: term.locator_report_dn = true;
          when 2: term.locator_report_dn = false;
          when 3: term.locator_report_up = true;
          when 4: term.locator_report_up = false;
        }
    }
    when CPAIR('\'', '|'): {
      if (term.mouse_mode == MM_LOCATOR || term.locator_1_enabled) {
        int x, y, buttons;
        win_get_locator_info(&x, &y, &buttons, term.locator_by_pixels);
        child_printf("\e[1;%d;%d;%d;0&w", buttons, y, x);
        term.locator_1_enabled = false;
      }
      else {

      }
    }
    when CPAIR('\'', 'w'): {
      int arg2 = term.csi_argv[2], arg3 = term.csi_argv[3];
      int x, y, buttons;
      win_get_locator_info(&x, &y, &buttons, term.locator_by_pixels);
      term.locator_top = arg0 ?: y;
      term.locator_left = arg1 ?: x;
      term.locator_bottom = arg2 ?: y;
      term.locator_right = arg3 ?: x;
      term.locator_rectangle = true;
    }
    when 'q': {
      if (arg0 > 20)
        win_led(arg0 - 20, false);
      else if (arg0)
        win_led(arg0, true);
      else {
        win_led(0, false);
      }
    }
    when CPAIR(' ', 'k'):
      if (arg0 <= 2) {
        if (arg0 == 2)
          curs->bidimode |= LATTR_BIDIRTL;
        else if (arg0 == 1)
          curs->bidimode &= ~LATTR_BIDIRTL;
        else {
          curs->bidimode &= ~(LATTR_BIDISEL | LATTR_BIDIRTL);
        }

      }
    when CPAIR(' ', 'S'):
      if (arg0 == 0)
          curs->bidimode &= ~LATTR_PRESRTL;
      else if (arg0 == 3)
          curs->bidimode |= LATTR_PRESRTL;
#define urows (uint) term.rows
#define ucols (uint) term.cols
    when CPAIR('$', 'v'):
      copy_rect(arg0_def1, arg1 ?: 1,
                term.csi_argv[2] ?: urows, term.csi_argv[3] ?: ucols,

                term.csi_argv[5] ?: urows, term.csi_argv[6] ?: ucols

                );
    when CPAIR('$', 'x'):
      fill_rect(arg0 ?: ' ', curs->attr, false,
                arg1 ?: 1, term.csi_argv[2] ?: 1,
                term.csi_argv[3] ?: urows, term.csi_argv[4] ?: ucols);
    when CPAIR('$', 'z'):
      fill_rect(' ', term.erase_char.attr, false,
                arg0_def1, arg1 ?: 1,
                term.csi_argv[2] ?: urows, term.csi_argv[3] ?: ucols);
    when CPAIR('$', '{'):
      fill_rect(' ', term.erase_char.attr, true,
                arg0_def1, arg1 ?: 1,
                term.csi_argv[2] ?: urows, term.csi_argv[3] ?: ucols);
    when CPAIR('*', 'x'):
      switch (arg0) {
        when 2: term.attr_rect = true;
        when 0 or 1: term.attr_rect = false;
      }
    when CPAIR('$', 'r')
      or CPAIR('$', 't'): {
      cattrflags a1 = 0, a2 = 0;
      for (uint i = 4; i < term.csi_argc; i++)
        switch (term.csi_argv[i]) {
          when 0: a2 = ATTR_BOLD | ATTR_UNDER | ATTR_BLINK | ATTR_REVERSE;
          when 1: a1 |= ATTR_BOLD;
          when 4: a1 |= ATTR_UNDER;
          when 5: a1 |= ATTR_BLINK;
          when 7: a1 |= ATTR_REVERSE;
          when 22: a2 |= ATTR_BOLD;
          when 24: a2 |= ATTR_UNDER;
          when 25: a2 |= ATTR_BLINK;
          when 27: a2 |= ATTR_REVERSE;

        }
      a1 &= ~a2;
      if (c == 'r')
        attr_rect(a1, a2, 0, arg0_def1, arg1 ?: 1,
                  term.csi_argv[2] ?: urows, term.csi_argv[3] ?: ucols);
      else
        attr_rect(0, 0, a1, arg0_def1, arg1 ?: 1,
                  term.csi_argv[2] ?: urows, term.csi_argv[3] ?: ucols);
    }
    when CPAIR('*', 'y'): {
      uint s = sum_rect(term.csi_argv[2] ?: 1, term.csi_argv[3] ?: 1,
                        term.csi_argv[4] ?: urows, term.csi_argv[5] ?: ucols);
      child_printf("\eP%u!~%04X\e\\", arg0, -s & 0xFFFF);
    }
    when CPAIR('\'', '}'):
      if (curs->x >= term.marg_left && curs->x <= term.marg_right
       && curs->y >= term.marg_top && curs->y <= term.marg_bot
         )
        insdel_column(curs->x, false, arg0_def1);
    when CPAIR('\'', '~'):
      if (curs->x >= term.marg_left && curs->x <= term.marg_right
       && curs->y >= term.marg_top && curs->y <= term.marg_bot
         )
        insdel_column(curs->x, true, arg0_def1);
    when CPAIR(' ', 'A'):
      if (curs->x >= term.marg_left && curs->x <= term.marg_right
       && curs->y >= term.marg_top && curs->y <= term.marg_bot
         )
        insdel_column(term.marg_left, false, arg0_def1);
    when CPAIR(' ', '@'):
      if (curs->x >= term.marg_left && curs->x <= term.marg_right
       && curs->y >= term.marg_top && curs->y <= term.marg_bot
         )
        insdel_column(term.marg_left, true, arg0_def1);
    when CPAIR('#', 't'):
      win_set_scrollview(arg0, arg1, term.csi_argc > 2 ? (int)term.csi_argv[2] : -1);
    when CPAIR('<', 't'):
      win_set_ime(arg0);
    when CPAIR('<', 's'):
      push_mode(-1, win_get_ime());
    when CPAIR('<', 'r'):
      win_set_ime(pop_mode(-1));
    when CPAIR(' ', 't'):
      if (arg0 <= 8)
        term.bell.vol = arg0;
    when CPAIR(' ', 'u'):
      if (!arg0)
        term.marginbell.vol = 8;
      else if (arg0 <= 8)
        term.marginbell.vol = arg0;
    when CPAIR(' ', 'Z'):
      if (!arg0)
        curs->width = 0;
      else if (arg0 == 1)
        curs->width = 2;
      else if (arg0 == 2) {
        if (arg1 == 2)
          curs->width = 11;
        else
          curs->width = 1;
      }
      else if (arg0 == 22)
        curs->width = 11;
#ifdef support_triple_width
      else if (arg0 == 3)
        curs->width = 3;
#endif
    when CPAIR('-', 'p'):
      if (arg0 <= 30)
        term.repeat_rate = arg0;
    when CPAIR('%', 'q'):
      set_taskbar_progress(arg0, term.csi_argc > 1 ? arg1 : -1);
    when 'y':
      if (arg0 == 4) {
        cattr attr = (cattr)
                     {.attr = ATTR_DEFFG | (TRUE_COLOUR << ATTR_BGSHIFT),
                      .truefg = 0, .truebg = 0, .ulcolr = (colour)-1,
                      .link = -1
                     };
        switch (arg1) {
          when 10: attr.truebg = RGB(0, 0, 255);
          when 11: attr.truebg = RGB(255, 0, 0);
          when 12: attr.truebg = RGB(0, 255, 0);
          when 13: attr.truebg = RGB(255, 255, 255);
          otherwise: return;
        }
        for (int i = 0; i < term.rows; i++) {
          termline *line = term.lines[i];
          for (int j = 0; j < term.cols; j++) {
            line->chars[j] =
              (termchar) {.cc_next = 0, .chr = ' ', attr};
          }
          line->lattr = LATTR_NORM;
        }
        term.disptop = 0;
      }
  }
}
}
