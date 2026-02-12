write_char(wchar c, int width)
{


  if (tek_mode) {
    tek_write(c, width);
    return;
  }

  if (!c)
    return;

  term_cursor * curs = &term.curs;
  termline * line = term.lines[curs->y];


  if (width == -1) {
    last_high = last_char;
  }
  else {
    last_high = 0;
    last_width = width;
  }
  last_char = c;
  last_attr = curs->attr;

  void wrapparabidi(ushort parabidi, termline * line, int y)
  {
    line->lattr = (line->lattr & ~LATTR_BIDIMASK) | parabidi | LATTR_WRAPCONTD;

#ifdef determine_parabidi_during_output
    if (parabidi & (LATTR_BIDISEL | LATTR_AUTOSEL))
      return;


    termline * paraline = line;
    int paray = y;
    while ((paraline->lattr & LATTR_WRAPCONTD) && paray > -sblines()) {
      paraline = fetch_line(--paray);
      paraline->lattr = (paraline->lattr & ~LATTR_BIDIMASK) | parabidi;
      release_line(paraline);
    }
    paraline = line;
    paray = y;
    while ((paraline->lattr & LATTR_WRAPPED) && paray < term.rows) {
      paraline = fetch_line(++paray);
      paraline->lattr = (paraline->lattr & ~LATTR_BIDIMASK) | parabidi;
      release_line(paraline);
    }
#else
    (void)y;
#endif
  }

  void put_char(wchar c)
  {
    if (term.ring_enabled && curs->x == term.marg_right + 1 - 8) {
      win_margin_bell(&cfg);
      term.ring_enabled = false;
    }

    clear_cc(line, curs->x);
    line->chars[curs->x].chr = c;
    line->chars[curs->x].attr = curs->attr;
#ifdef insufficient_approach
#warning this does not help when scrolling via rectangular copy
    if (term.lrmargmode)
      line->lattr &= ~LATTR_MODE;
#endif
    if (!(line->lattr & LATTR_WRAPCONTD))
      line->lattr = (line->lattr & ~LATTR_BIDIMASK) | curs->bidimode;

    if (cfg.ligatures_support)
      term_invalidate(0, curs->y, curs->x, curs->y);
  }

  if (curs->wrapnext && term.autowrap && width > 0) {
    line->lattr |= LATTR_WRAPPED;
    line->wrappos = curs->x;
    ushort parabidi = getparabidi(line);
    if (curs->y == term.marg_bot)
      term_do_scroll(term.marg_top, term.marg_bot, 1, true);
    else if (curs->y < term.rows - 1)
      curs->y++;
    curs->x = term.marg_left;
    curs->wrapnext = false;
    line = term.lines[curs->y];
    wrapparabidi(parabidi, line, curs->y);
  }

  bool overstrike = false;
  if (curs->attr.attr & ATTR_OVERSTRIKE) {
    width = 0;
    overstrike = true;
    curs->wrapnext = false;
  }

  bool single_width = false;


  if (curs->width && width > 0) {

    if (curs->width == 1) {
      if (!(width < 2 || (cs_ambig_wide && is_ambig(c))))
        curs->attr.attr |= TATTR_CLEAR | TATTR_NARROW;
      width = 1;
    }
    else if (curs->width == 11) {
      if (width > 1) {
        if (!(cs_ambig_wide && is_ambig(c))) {
          single_width = true;
          curs->attr.attr |= TATTR_SINGLE;
        }
        width = 1;
      }
    }
    else if (curs->width == 2) {
      if (width < 2) {
        curs->attr.attr |= TATTR_EXPAND;
        width = 2;
      }
    }
#ifdef support_triple_width
    else if (curs->width == 3) {
      if (width < 2 || (cs_ambig_wide && is_ambig(c)))
        curs->attr.attr |= TATTR_EXPAND;
#define TATTR_TRIPLE 0x0080000000000000u
      curs->attr.attr |= TATTR_TRIPLE;
      width = 3;
    }
#endif
  }

#ifdef enforce_ambiguous_narrow_here


  if (cs_ambig_narrow && width > 1 && is_ambig(c))
    width = 1;
#endif

  if (cfg.charwidth >= 10 || cs_single_forced) {
    if (width > 1) {
      single_width = true;
      width = 1;
    }
    else if (is_wide(c) || (cs_ambig_wide && is_ambig(c))) {
      single_width = true;
    }
  }

  if (term.insert && width > 0)
    insert_char(width);

  switch (width) {
    when 1:
      term_check_boundary(curs->x, curs->y);
      term_check_boundary(curs->x + 1, curs->y);
      put_char(c);
      if (single_width)
        line->chars[curs->x].attr.attr |= TATTR_SINGLE;
    when 2 or 3:


      term_check_boundary(curs->x, curs->y);
      term_check_boundary(curs->x + width, curs->y);
      if (curs->x == term.marg_right || curs->x == term.cols - 1) {
        line->chars[curs->x] = term.erase_char;
        line->lattr |= LATTR_WRAPPED | LATTR_WRAPPED2;
        line->wrappos = curs->x;
        ushort parabidi = getparabidi(line);
        if (curs->y == term.marg_bot)
          term_do_scroll(term.marg_top, term.marg_bot, 1, true);
        else if (curs->y < term.rows - 1)
          curs->y++;
        curs->x = term.marg_left;
        line = term.lines[curs->y];
        wrapparabidi(parabidi, line, curs->y);

        term_check_boundary(curs->x, curs->y);
        term_check_boundary(curs->x + width, curs->y);
      }
      put_char(c);
      curs->x++;
      put_char(UCSWIDE);
#ifdef support_triple_width
      if (width > 2) {
        for (int i = 2; i < width; i++) {
          curs->x++;
          put_char(UCSWIDE);
        }
      }
#endif
    when 0 or -1:
#ifdef debug_surrogates
      printf("write_char %04X %2d %08llX\n", c, width, curs->attr.attr);
#endif
      if (curs->x > 0 || overstrike) {


        int x = curs->x - !curs->wrapnext;

        if (overstrike)
          x = curs->x;


        if (line->chars[x].chr == UCSWIDE) {
          assert(x > 0);
          x--;
        }

        wchar pc;
        if (termattrs_equal_fg(&line->chars[x].attr, &curs->attr))
          pc = win_combine_chars(line->chars[x].chr, c, curs->attr.attr);
        else
          pc = 0;
        if (pc)
          line->chars[x].chr = pc;
        else
          add_cc(line, x, c, curs->attr);
      }
      else {


        add_cc(line, -1, c, curs->attr);
      }
      if (!overstrike)
        return;


    otherwise:
      return;
  }

  curs->x++;
  if (curs->x == term.marg_right + 1 || curs->x == term.cols) {
    curs->x--;
    if (term.autowrap || cfg.old_wrapmodes)
      curs->wrapnext = true;
  }
}
