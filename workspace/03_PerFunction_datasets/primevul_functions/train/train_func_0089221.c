do_sgr(void)
{

  uint argc = term.csi_argc;
  cattr attr = term.curs.attr;
  uint prot = attr.attr & ATTR_PROTECTED;
  for (uint i = 0; i < argc; i++) {


    int sub_pars = 0;


    if (term.csi_argv[i] & SUB_PARS)
      for (uint j = i + 1; j < argc; j++) {
        sub_pars++;
        if (term.csi_argv[j] & SUB_PARS)
          term.csi_argv[j] &= ~SUB_PARS;
        else
          break;
      }
    if (*cfg.suppress_sgr
        && contains(cfg.suppress_sgr, term.csi_argv[i] & ~SUB_PARS))
    {


      if (term.csi_argv[i] == 38 || term.csi_argv[i] == 48) {
        if (i + 2 < argc && term.csi_argv[i + 1] == 5)
          sub_pars = 2;
        else if (i + 4 < argc && term.csi_argv[i + 1] == 2)
          sub_pars = 4;
      }
    }
    else
    switch (term.csi_argv[i]) {
      when 0:
        attr = CATTR_DEFAULT;
        attr.attr |= prot;
      when 1: attr.attr |= ATTR_BOLD;
      when 2: attr.attr |= ATTR_DIM;
      when 1 | SUB_PARS:
        if (i + 1 < argc)
          switch (term.csi_argv[i + 1]) {
            when 2:
              attr.attr |= ATTR_SHADOW;
          }
      when 3: attr.attr |= ATTR_ITALIC;
      when 4:
        attr.attr &= ~UNDER_MASK;
        attr.attr |= ATTR_UNDER;
      when 4 | SUB_PARS:
        if (i + 1 < argc)
          switch (term.csi_argv[i + 1]) {
            when 0:
              attr.attr &= ~UNDER_MASK;
            when 1:
              attr.attr &= ~UNDER_MASK;
              attr.attr |= ATTR_UNDER;
            when 2:
              attr.attr &= ~UNDER_MASK;
              attr.attr |= ATTR_DOUBLYUND;
            when 3:
              attr.attr &= ~UNDER_MASK;
              attr.attr |= ATTR_CURLYUND;
            when 4:
              attr.attr &= ~UNDER_MASK;
              attr.attr |= ATTR_BROKENUND;
            when 5:
              attr.attr &= ~UNDER_MASK;
              attr.attr |= ATTR_BROKENUND | ATTR_DOUBLYUND;
          }
      when 5: attr.attr |= ATTR_BLINK;
      when 6: attr.attr |= ATTR_BLINK2;
      when 7: attr.attr |= ATTR_REVERSE;
      when 8: attr.attr |= ATTR_INVISIBLE;
      when 8 | SUB_PARS:
        if (i + 1 < argc)
          switch (term.csi_argv[i + 1]) {
            when 7:
              attr.attr |= ATTR_OVERSTRIKE;
          }
      when 9: attr.attr |= ATTR_STRIKEOUT;
      when 73: attr.attr |= ATTR_SUPERSCR;
      when 74: attr.attr |= ATTR_SUBSCR;
      when 75: attr.attr &= ~(ATTR_SUPERSCR | ATTR_SUBSCR);
      when 10 ... 11: {


          uchar arg_10 = term.csi_argv[i] - 10;
          if (arg_10 && *cfg.fontfams[arg_10].name) {
            attr.attr &= ~FONTFAM_MASK;
            attr.attr |= (cattrflags)arg_10 << ATTR_FONTFAM_SHIFT;
          }
          else {
            if (!arg_10)
              attr.attr &= ~FONTFAM_MASK;
            term.curs.oem_acs = arg_10;
            term_update_cs();
          }
        }
      when 12 ... 20:
        attr.attr &= ~FONTFAM_MASK;
        attr.attr |= (cattrflags)(term.csi_argv[i] - 10) << ATTR_FONTFAM_SHIFT;

      when 21:
        attr.attr &= ~UNDER_MASK;
        attr.attr |= ATTR_DOUBLYUND;
      when 22: attr.attr &= ~(ATTR_BOLD | ATTR_DIM | ATTR_SHADOW);
      when 23:
        attr.attr &= ~ATTR_ITALIC;
        if (((attr.attr & FONTFAM_MASK) >> ATTR_FONTFAM_SHIFT) + 10 == 20)
          attr.attr &= ~FONTFAM_MASK;
      when 24: attr.attr &= ~UNDER_MASK;
      when 25: attr.attr &= ~(ATTR_BLINK | ATTR_BLINK2);
      when 27: attr.attr &= ~ATTR_REVERSE;
      when 28: attr.attr &= ~(ATTR_INVISIBLE | ATTR_OVERSTRIKE);
      when 29: attr.attr &= ~ATTR_STRIKEOUT;
      when 30 ... 37:
        attr.attr &= ~ATTR_FGMASK;
        attr.attr |= (term.csi_argv[i] - 30 + ANSI0) << ATTR_FGSHIFT;
      when 51 or 52:
        attr.attr |= ATTR_FRAMED;
      when 54:
        attr.attr &= ~ATTR_FRAMED;
      when 53: attr.attr |= ATTR_OVERL;
      when 55: attr.attr &= ~ATTR_OVERL;
      when 90 ... 97:
        attr.attr &= ~ATTR_FGMASK;
        attr.attr |= ((term.csi_argv[i] - 90 + 8 + ANSI0) << ATTR_FGSHIFT);
      when 38:
        if (i + 2 < argc && term.csi_argv[i + 1] == 5) {

          attr.attr &= ~ATTR_FGMASK;
          attr.attr |= ((term.csi_argv[i + 2] & 0xFF) << ATTR_FGSHIFT);
          i += 2;
        }
        else if (i + 4 < argc && term.csi_argv[i + 1] == 2) {

          attr.attr &= ~ATTR_FGMASK;
          attr.attr |= TRUE_COLOUR << ATTR_FGSHIFT;
          uint r = term.csi_argv[i + 2];
          uint g = term.csi_argv[i + 3];
          uint b = term.csi_argv[i + 4];
          attr.truefg = make_colour(r, g, b);
          i += 4;
        }
      when 38 | SUB_PARS:
        if (sub_pars >= 2 && term.csi_argv[i + 1] == 5) {

          attr.attr &= ~ATTR_FGMASK;
          attr.attr |= ((term.csi_argv[i + 2] & 0xFF) << ATTR_FGSHIFT);
        }
        else if (sub_pars >= 4 && term.csi_argv[i + 1] == 2) {

          uint pi = sub_pars >= 5;
          attr.attr &= ~ATTR_FGMASK;
          attr.attr |= TRUE_COLOUR << ATTR_FGSHIFT;
          uint r = term.csi_argv[i + pi + 2];
          uint g = term.csi_argv[i + pi + 3];
          uint b = term.csi_argv[i + pi + 4];
          attr.truefg = make_colour(r, g, b);
        }
        else if ((sub_pars >= 5 && term.csi_argv[i + 1] == 3) ||
                 (sub_pars >= 6 && term.csi_argv[i + 1] == 4)) {

          ulong f = term.csi_argv[i + 2];
          ulong c = term.csi_argv[i + 3];
          ulong m = term.csi_argv[i + 4];
          ulong y = term.csi_argv[i + 5];
          ulong k = term.csi_argv[i + 1] == 4 ? term.csi_argv[i + 6] : 0;
          if (c <= f && m <= f && y <= f && k <= f) {
            uint r = (f - c) * (f - k) / f * 255 / f;
            uint g = (f - m) * (f - k) / f * 255 / f;
            uint b = (f - y) * (f - k) / f * 255 / f;
            attr.attr &= ~ATTR_FGMASK;
            attr.attr |= TRUE_COLOUR << ATTR_FGSHIFT;
            attr.truefg = make_colour(r, g, b);
          }
        }
      when 39:
        attr.attr &= ~ATTR_FGMASK;
        attr.attr |= ATTR_DEFFG;
      when 40 ... 47:
        attr.attr &= ~ATTR_BGMASK;
        attr.attr |= (term.csi_argv[i] - 40 + ANSI0) << ATTR_BGSHIFT;
      when 100 ... 107:
        attr.attr &= ~ATTR_BGMASK;
        attr.attr |= ((term.csi_argv[i] - 100 + 8 + ANSI0) << ATTR_BGSHIFT);
      when 48:
        if (i + 2 < argc && term.csi_argv[i + 1] == 5) {

          attr.attr &= ~ATTR_BGMASK;
          attr.attr |= ((term.csi_argv[i + 2] & 0xFF) << ATTR_BGSHIFT);
          i += 2;
        }
        else if (i + 4 < argc && term.csi_argv[i + 1] == 2) {

          attr.attr &= ~ATTR_BGMASK;
          attr.attr |= TRUE_COLOUR << ATTR_BGSHIFT;
          uint r = term.csi_argv[i + 2];
          uint g = term.csi_argv[i + 3];
          uint b = term.csi_argv[i + 4];
          attr.truebg = make_colour(r, g, b);
          i += 4;
        }
      when 48 | SUB_PARS:
        if (sub_pars >= 2 && term.csi_argv[i + 1] == 5) {

          attr.attr &= ~ATTR_BGMASK;
          attr.attr |= ((term.csi_argv[i + 2] & 0xFF) << ATTR_BGSHIFT);
        }
        else if (sub_pars >= 4 && term.csi_argv[i + 1] == 2) {

          uint pi = sub_pars >= 5;
          attr.attr &= ~ATTR_BGMASK;
          attr.attr |= TRUE_COLOUR << ATTR_BGSHIFT;
          uint r = term.csi_argv[i + pi + 2];
          uint g = term.csi_argv[i + pi + 3];
          uint b = term.csi_argv[i + pi + 4];
          attr.truebg = make_colour(r, g, b);
        }
        else if ((sub_pars >= 5 && term.csi_argv[i + 1] == 3) ||
                 (sub_pars >= 6 && term.csi_argv[i + 1] == 4)) {

          ulong f = term.csi_argv[i + 2];
          ulong c = term.csi_argv[i + 3];
          ulong m = term.csi_argv[i + 4];
          ulong y = term.csi_argv[i + 5];
          ulong k = term.csi_argv[i + 1] == 4 ? term.csi_argv[i + 6] : 0;
          if (c <= f && m <= f && y <= f && k <= f) {
            uint r = (f - c) * (f - k) / f * 255 / f;
            uint g = (f - m) * (f - k) / f * 255 / f;
            uint b = (f - y) * (f - k) / f * 255 / f;
            attr.attr &= ~ATTR_BGMASK;
            attr.attr |= TRUE_COLOUR << ATTR_BGSHIFT;
            attr.truebg = make_colour(r, g, b);
          }
        }
      when 49:
        attr.attr &= ~ATTR_BGMASK;
        attr.attr |= ATTR_DEFBG;
      when 58 | SUB_PARS:
        if (sub_pars >= 2 && term.csi_argv[i + 1] == 5) {

          attr.attr |= ATTR_ULCOLOUR;
          attr.ulcolr = colours[term.csi_argv[i + 2] & 0xFF];
        }
        else if (sub_pars >= 4 && term.csi_argv[i + 1] == 2) {

          uint pi = sub_pars >= 5;
          uint r = term.csi_argv[i + pi + 2];
          uint g = term.csi_argv[i + pi + 3];
          uint b = term.csi_argv[i + pi + 4];
          attr.attr |= ATTR_ULCOLOUR;
          attr.ulcolr = make_colour(r, g, b);
        }
        else if ((sub_pars >= 5 && term.csi_argv[i + 1] == 3) ||
                 (sub_pars >= 6 && term.csi_argv[i + 1] == 4)) {

          ulong f = term.csi_argv[i + 2];
          ulong c = term.csi_argv[i + 3];
          ulong m = term.csi_argv[i + 4];
          ulong y = term.csi_argv[i + 5];
          ulong k = term.csi_argv[i + 1] == 4 ? term.csi_argv[i + 6] : 0;
          if (c <= f && m <= f && y <= f && k <= f) {
            uint r = (f - c) * (f - k) / f * 255 / f;
            uint g = (f - m) * (f - k) / f * 255 / f;
            uint b = (f - y) * (f - k) / f * 255 / f;
            attr.attr |= ATTR_ULCOLOUR;
            attr.ulcolr = make_colour(r, g, b);
          }
        }
      when 59:
        attr.attr &= ~ATTR_ULCOLOUR;
        attr.ulcolr = (colour)-1;
    }

    i += sub_pars;
  }
  term.curs.attr = attr;
  term.erase_char.attr = attr;
  term.erase_char.attr.attr &= (ATTR_FGMASK | ATTR_BGMASK);
  term.erase_char.attr.attr |= TATTR_CLEAR;
}
