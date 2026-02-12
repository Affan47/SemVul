term_do_write(const char *buf, uint len)
{


  term.cblinker = 1;
  term_schedule_cblink();

  short oldy = term.curs.y;

  uint pos = 0;
  while (pos < len) {
    uchar c = buf[pos++];


    if (term.printing) {
      if (term.printbuf_pos >= term.printbuf_size) {
        term.printbuf_size = term.printbuf_size * 4 + 4096;
        term.printbuf = renewn(term.printbuf, term.printbuf_size);
      }
      term.printbuf[term.printbuf_pos++] = c;


      if (term.only_printing) {
        if (c == '\e')
          term.print_state = 1;
        else if (c == '[' && term.print_state == 1)
          term.print_state = 2;
        else if (c == '4' && term.print_state == 2)
          term.print_state = 3;
        else if (c == 'i' && term.print_state == 3) {
          term.printbuf_pos -= 4;
          term_print_finish();
        }
        else
          term.print_state = 0;
        continue;
      }
    }

    switch (term.state) {
      when NORMAL: {
        wchar wc;

        if (term.curs.oem_acs && !memchr("\e\n\r\b", c, 4)) {
          if (term.curs.oem_acs == 2)
            c |= 0x80;
          write_ucschar(0, cs_btowc_glyph(c), 1);
          continue;
        }


        short cset = term.curs.csets[term.curs.gl];
        if (term.curs.cset_single != CSET_ASCII && c > 0x20 && c < 0xFF) {
          cset = term.curs.cset_single;
          term.curs.cset_single = CSET_ASCII;
        }
        else if (term.decnrc_enabled
         && term.curs.gr && term.curs.csets[term.curs.gr] != CSET_ASCII
         && !term.curs.oem_acs && !term.curs.utf
         && c >= 0x80 && c < 0xFF) {

          if (c < 0xA0)
            continue;

          c &= 0x7F;
          cset = term.curs.csets[term.curs.gr];
        }

        if (term.vt52_mode) {
          if (term.vt52_mode > 1)
            cset = CSET_VT52DRW;
          else
            cset = CSET_ASCII;
        }
        else if (cset == CSET_DECSUPP)
          cset = term.curs.decsupp;

        switch (cs_mb1towc(&wc, c)) {
          when 0:
            if (wc)
              pos--;
          when -1:
            if (!tek_mode)
              write_error();
            if (term.in_mb_char || term.high_surrogate)
              pos--;
            term.high_surrogate = 0;
            term.in_mb_char = false;
            cs_mb1towc(0, 0);
            continue;
          when -2:
            term.in_mb_char = true;
            continue;
        }

        term.in_mb_char = false;


        wchar hwc = term.high_surrogate;
        term.high_surrogate = 0;

        if (is_low_surrogate(wc)) {
          if (hwc) {
#if HAS_LOCALES
            int width = (cfg.charwidth % 10)
                        ? xcwidth(combine_surrogates(hwc, wc)) :
# ifdef __midipix__
                        wcwidth(combine_surrogates(hwc, wc));
# else
                        wcswidth((wchar[]){hwc, wc}, 2);
# endif
#else
            int width = xcwidth(combine_surrogates(hwc, wc));
#endif
#ifdef support_triple_width


#endif
            write_ucschar(hwc, wc, width);
          }
          else
            write_error();
          continue;
        }

        if (hwc)
          write_error();


        if (wc >= ' ' && wc <= 0x7E && cset == CSET_ASCII) {
          write_ucschar(0, wc, 1);
          continue;
        }

        if (is_high_surrogate(wc)) {
          term.high_surrogate = wc;
          continue;
        }


        if (wc == 0xFFFE || wc == 0xFFFF) {
          write_error();
          continue;
        }


        wchar NRC(wchar * map)
        {
          static char * rpl = "#@[\\]^_`{|}~";
          char * match = strchr(rpl, c);
          if (match)
            return map[match - rpl];
          else
            return wc;
        }

        cattrflags asav = term.curs.attr.attr;

        switch (cset) {
          when CSET_VT52DRW:
            if (0x5E <= wc && wc <= 0x7E) {
              uchar dispcode = 0;
              uchar gcode = 0;
              if ('l' <= wc && wc <= 's') {
                dispcode = wc - 'l' + 1;
                gcode = 13;
              }
              else if ('c' <= wc && wc <= 'e') {
                dispcode = 0xF;
              }
              wc = W("^ ￿▮⅟³⁵⁷°±→…÷↓⎺⎺⎻⎻⎼⎼⎽⎽₀₁₂₃₄₅₆₇₈₉¶") [c - 0x5E];
              term.curs.attr.attr |= ((cattrflags)dispcode) << ATTR_GRAPH_SHIFT;
              if (gcode) {

                term.curs.attr.attr &= ~FONTFAM_MASK;
                term.curs.attr.attr |= (cattrflags)gcode << ATTR_FONTFAM_SHIFT;
              }
            }
          when CSET_LINEDRW:
            if (0x60 <= wc && wc <= 0x7E) {
              wchar dispwc = win_linedraw_char(wc - 0x60);
#define draw_vt100_line_drawing_chars
#ifdef draw_vt100_line_drawing_chars
              if ('j' <= wc && wc <= 'x') {
                static uchar linedraw_code[31] = {
                  0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
#if __GNUC__ >= 5
                  0b1001, 0b1100, 0b0110, 0b0011, 0b1111,
                  0x10, 0x20, 0b1010, 0x40, 0x50,
                  0b0111, 0b1101, 0b1011, 0b1110, 0b0101,
#else
                  0x09, 0x0C, 0x06, 0x03, 0x0F,
                  0x10, 0x20, 0x0A, 0x40, 0x50,
                  0x07, 0x0D, 0x0B, 0x0E, 0x05,
#endif
                  0, 0, 0, 0, 0, 0
                };
                uchar dispcode = linedraw_code[wc - 0x60];
                if (dispcode) {
                  uchar gcode = 11;
                  if (dispcode >> 4) {
                    dispcode >>= 4;
                    gcode++;
                  }
                  term.curs.attr.attr |= ((cattrflags)dispcode) << ATTR_GRAPH_SHIFT;

                  term.curs.attr.attr &= ~FONTFAM_MASK;
                  term.curs.attr.attr |= (cattrflags)gcode << ATTR_FONTFAM_SHIFT;
                }
              }
#endif
              wc = dispwc;
            }
          when CSET_TECH:
            if (c > ' ' && c < 0x7F) {


              wc = W("⎷┌─⌠⌡│⎡⎣⎤⎦⎧⎩⎫⎭⎨⎬╶╶╲╱╴╴╳￿￿￿￿≤≠≥∫∴∝∞÷  ΦΓ∼≃Θ×Λ⇔⇒≡ΠΨ￿Σ￿￿√ΩΞΥ⊂⊃∩∪∧∨¬αβχδεφγηιθκλ￿ν∂πψρστ￿ƒωξυζ←↑→↓")
                   [c - ' ' - 1];
              uchar dispcode = 0;
              if (c <= 0x37) {
                static uchar techdraw_code[23] = {
                  0xE,
                  0, 0, 0, 0, 0,
                  0x8, 0x9, 0xA, 0xB,
                  0, 0, 0, 0,
                  0, 0,
                  0x1, 0x2, 0, 0, 0x5, 0x6, 0x7
                };
                dispcode = techdraw_code[c - 0x21];
              }
              else if (c == 0x44)
                dispcode = 0xC;
              else if (c == 0x45)
                dispcode = 0xD;
              term.curs.attr.attr |= ((cattrflags)dispcode) << ATTR_GRAPH_SHIFT;
            }
          when CSET_NL:
            wc = NRC(W("£¾ĳ½|^_`¨ƒ¼´"));
          when CSET_FI:
            wc = NRC(W("#@ÄÖÅÜ_éäöåü"));
          when CSET_FR:
            wc = NRC(W("£à°ç§^_`éùè¨"));
          when CSET_CA:
            wc = NRC(W("#àâçêî_ôéùèû"));
          when CSET_DE:
            wc = NRC(W("#§ÄÖÜ^_`äöüß"));
          when CSET_IT:
            wc = NRC(W("£§°çé^_ùàòèì"));
          when CSET_NO:
            wc = NRC(W("#ÄÆØÅÜ_äæøåü"));
          when CSET_PT:
            wc = NRC(W("#@ÃÇÕ^_`ãçõ~"));
          when CSET_ES:
            wc = NRC(W("£§¡Ñ¿^_`°ñç~"));
          when CSET_SE:
            wc = NRC(W("#ÉÄÖÅÜ_éäöåü"));
          when CSET_CH:
            wc = NRC(W("ùàéçêîèôäöüû"));
          when CSET_DECSPGR
            or CSET_DECSUPP:
            if (c > ' ' && c < 0x7F) {
              wc = W("¡¢£￿¥￿§¤©ª«￿￿￿￿°±²³￿µ¶·￿¹º»¼½￿¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏ￿ÑÒÓÔÕÖŒØÙÚÛÜŸ￿ßàáâãäåæçèéêëìíîï￿ñòóôõöœøùúûüÿ￿")
                   [c - ' ' - 1];
            }

          when CSET_GBCHR:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ")
                   [c - ' '];
            }
          when CSET_ISO_Latin_Cyrillic:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" ЁЂЃЄЅІЇЈЉЊЋЌ­ЎЏАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюя№ёђѓєѕіїјљњћќ§ўџ")
                   [c - ' '];
            }
          when CSET_ISO_Greek_Supp:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" ‘’£€₯¦§¨©ͺ«¬­￿―°±²³΄΅Ά·ΈΉΊ»Ό½ΎΏΐΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟΠΡ￿ΣΤΥΦΧΨΩΪΫάέήίΰαβγδεζηθικλμνξοπρςστυφχψωϊϋόύώ")
                   [c - ' '];
            }
          when CSET_ISO_Hebrew:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" ￿¢£¤¥¦§¨©×«¬­®¯°±²³´µ¶·¸¹÷»¼½¾￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿‗אבגדהוזחטיךכלםמןנסעףפץצקרשת￿￿‎‏")
                   [c - ' '];
            }
          when CSET_ISO_Latin_5:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ")
                   [c - ' '];
            }
          when CSET_DEC_Greek_Supp:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" ¡¢£￿¥￿§¤©ª«￿￿￿￿°±²³￿µ¶·￿¹º»¼½￿¿ϊΑΒΓΔΕΖΗΘΙΚΛΜΝΞΟ￿ΠΡΣΤΥΦΧΨΩάέήί￿όϋαβγδεζηθικλμνξο￿πρστυφχψωςύώ΄￿")
                   [c - ' '];
            }
          when CSET_DEC_Hebrew_Supp:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" ¡¢£￿¥￿§¨©×«￿￿￿￿°±²³￿µ¶·￿¹÷»¼½￿¿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿אבגדהוזחטיךכלםמןנסעףפץצקרשת￿￿￿￿")
                   [c - ' '];
            }
          when CSET_DEC_Turkish_Supp:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" ¡¢£￿¥￿§¨©ª«￿￿İ￿°±²³￿µ¶·￿¹º»¼½ı¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖŒØÙÚÛÜŸŞßàáâãäåæçèéêëìíîïğñòóôõöœøùúûüÿş")
                   [c - ' '];
            }
          when CSET_DEC_Cyrillic:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" ￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿￿юабцдефгхийклмнопярстужвьызшэщчъЮАБЦДЕФГХИЙКЛМНОПЯРСТУЖВЬЫЗШЭЩЧЪ")
                   [c - ' '];
            }
          when CSET_NRCS_Greek:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`ΑΒΓΔΕΖΗΘΙΚΛΜΝΧΟΠΡΣΤΥΦΞΨΩ￿￿{|}~")
                   [c - ' '];
            }
          when CSET_NRCS_Hebrew:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_אבגדהוזחטיךכלםמןנסעףפץצקרשת{|}~")
                   [c - ' '];
            }
          when CSET_NRCS_Turkish:
            if (c >= ' ' && c <= 0x7F) {
              wc = W(" !\"#$%ğ'()*+,-./0123456789:;<=>?İABCDEFGHIJKLMNOPQRSTUVWXYZŞÖÇÜ_Ğabcdefghijklmnopqrstuvwxyzşöçü")
                   [c - ' '];
            }
          otherwise: ;
        }


        if (wc >= 0x2580 && wc <= 0x259F) {


          term.curs.attr.attr |= ((cattrflags)(wc & 0xF)) << ATTR_GRAPH_SHIFT;
          uchar gcode = 14 + ((wc >> 4) & 1);

          term.curs.attr.attr &= ~FONTFAM_MASK;
          term.curs.attr.attr |= (cattrflags)gcode << ATTR_FONTFAM_SHIFT;
        }
#ifdef draw_powerline_geometric_symbols
#warning graphical results of this approach are unpleasant; not enabled
        else if (wc >= 0xE0B0 && wc <= 0xE0BF && wc != 0xE0B5 && wc != 0xE0B7) {


          term.curs.attr.attr &= ~FONTFAM_MASK;
          term.curs.attr.attr |= (cattrflags)13 << ATTR_FONTFAM_SHIFT;
          term.curs.attr.attr |= (cattrflags)15 << ATTR_GRAPH_SHIFT;
        }
#endif


        int width;
        if (term.wide_indic && wc >= 0x0900 && indicwide(wc))
          width = 2;
        else if (term.wide_extra && wc >= 0x2000 && extrawide(wc)) {
          width = 2;


          if (win_char_width(wc, term.curs.attr.attr) < 2)
            term.curs.attr.attr |= TATTR_EXPAND;
        }
        else {
#if HAS_LOCALES
          if (cfg.charwidth % 10)
            width = xcwidth(wc);
          else
            width = wcwidth(wc);
#ifdef support_triple_width


#endif
# ifdef hide_isolate_marks


          if (wc >= 0x2066 && wc <= 0x2069)
            width = 0;
# endif
#else
          width = xcwidth(wc);
#endif
        }
        if (width < 0 && cfg.printable_controls) {
          if (wc >= 0x80 && wc < 0xA0)
            width = 1;
          else if (wc < ' ' && cfg.printable_controls > 1)
            width = 1;
        }


        if (width == 2

            && wc >= 0x3008 && wc <= 0x301B && (wc | 1) != 0x3013
            && win_char_width(wc, term.curs.attr.attr) < 2

            && win_char_width(wc ^ 1, term.curs.attr.attr) < 2)
        {
          term.curs.attr.attr |= TATTR_EXPAND;
        }


        if (wc < 0x20 || wc == 0x7F) {
          if (!do_ctrl(wc) && c == wc) {
            wc = cs_btowc_glyph(c);
            if (wc != c)
              write_ucschar(0, wc, 1);
            else if (cfg.printable_controls > 1)
              goto goon;
          }
          term.curs.attr.attr = asav;
          continue;

          goon:;
        }


        write_ucschar(0, wc, width);
        term.curs.attr.attr = asav;
      }

      when VT52_Y:
        term.cmd_len = 0;
        term_push_cmd(c);
        term.state = VT52_X;

      when VT52_X:
        term_push_cmd(c);
        do_vt52_move();

      when VT52_FG:
        do_vt52_colour(true, c);

      when VT52_BG:
        do_vt52_colour(false, c);

      when TEK_ESCAPE:
        tek_esc(c);

      when TEK_ADDRESS0 or TEK_ADDRESS:
        if (c < ' ')
          tek_ctrl(c);
        else if (tek_mode == TEKMODE_SPECIAL_PLOT && term.state == TEK_ADDRESS0) {
          term.state = TEK_ADDRESS;
          term.cmd_len = 0;
          tek_intensity(c & 0x40, c & 0x37);
        }


        else {
          if (term.state == TEK_ADDRESS0) {
            term.state = TEK_ADDRESS;
            term.cmd_len = 0;
          }

          term_push_cmd(c);
          if ((c & 0x60) == 0x40) {
            tek_address(term.cmd_buf);
            term.state = TEK_ADDRESS0;
            if (tek_mode == TEKMODE_GRAPH0)
              tek_mode = TEKMODE_GRAPH;
          }
        }

      when TEK_INCREMENTAL:
        if (c < ' ')
          tek_ctrl(c);
        else if (c == ' ' || c == 'P')
          tek_pen(c == 'P');
        else if (strchr("DEAIHJBF", c))
          tek_step(c);

      when ESCAPE or CMD_ESCAPE:
        if (term.vt52_mode)
          do_vt52(c);
        else if (c < 0x20)
          do_ctrl(c);
        else if (c < 0x30) {

          if (term.esc_mod) {
            esc_mod0 = term.esc_mod;
            esc_mod1 = c;
            term.esc_mod = 0xFF;
          }
          else {
            esc_mod0 = 0;
            esc_mod1 = 0;
            term.esc_mod = c;
          }
        }
        else if (c == '\\' && term.state == CMD_ESCAPE) {

          do_cmd();
          term.state = NORMAL;
        }
        else {
          do_esc(c);

        }

      when CSI_ARGS:
        if (c < 0x20)
          do_ctrl(c);
        else if (c == ';') {
          if (term.csi_argc < lengthof(term.csi_argv))
            term.csi_argc++;
        }
        else if (c == ':') {


          uint i = term.csi_argc - 1;
          term.csi_argv[i] |= SUB_PARS;
          if (term.csi_argc < lengthof(term.csi_argv))
            term.csi_argc++;
        }
        else if (c >= '0' && c <= '9') {
          uint i = term.csi_argc - 1;
          if (i < lengthof(term.csi_argv)) {
            term.csi_argv[i] = 10 * term.csi_argv[i] + c - '0';
            if ((int)term.csi_argv[i] < 0)
              term.csi_argv[i] = INT_MAX;
            term.csi_argv_defined[i] = 1;
          }
        }
        else if (c < 0x40) {

          if (term.esc_mod) {
            esc_mod0 = term.esc_mod;
            esc_mod1 = c;
            term.esc_mod = 0xFF;
          }
          else {
            esc_mod0 = 0;
            esc_mod1 = 0;
            term.esc_mod = c;
          }
        }
        else {
          do_csi(c);
          term.state = NORMAL;
        }

      when OSC_START:
        term.cmd_len = 0;
        switch (c) {
          when 'P':
            term.state = OSC_PALETTE;
          when 'R':
            win_reset_colours();
            term.state = NORMAL;
          when 'I':
            term.cmd_num = 7773;
            term.state = OSC_NUM;
          when 'L':
            term.cmd_num = 1;
            term.state = OSC_NUM;
          when 'l':
            term.cmd_num = 2;
            term.state = OSC_NUM;
          when '0' ... '9':
            term.cmd_num = c - '0';
            term.state = OSC_NUM;
          when ';':
            term.cmd_num = 0;
            term.state = CMD_STRING;
          when '\a':
            term.state = NORMAL;
          when '\e':
            term.state = ESCAPE;
          when '\n' or '\r':
            term.state = IGNORE_STRING;
          otherwise:
            term.state = IGNORE_STRING;
        }

      when OSC_NUM:
        switch (c) {
          when '0' ... '9':
            term.cmd_num = term.cmd_num * 10 + c - '0';
            if (term.cmd_num < 0)
              term.cmd_num = -99;
          when ';':
            term.state = CMD_STRING;
          when '\a':
            do_cmd();
            term.state = NORMAL;
          when '\e':
            term.state = CMD_ESCAPE;
          when '\n' or '\r':
            term.state = IGNORE_STRING;
          otherwise:
            term.state = IGNORE_STRING;
        }

      when OSC_PALETTE:
        if (isxdigit(c)) {


          term_push_cmd(c);
          if (term.cmd_len == 7) {
            uint n, r, g, b;
            sscanf(term.cmd_buf, "%1x%2x%2x%2x", &n, &r, &g, &b);
            win_set_colour(n, make_colour(r, g, b));
            term.state = NORMAL;
          }
        }
        else {


          term.state = NORMAL;
          if (c != '\a') {
            pos--;
            continue;
          }
        }

      when CMD_STRING:
        switch (c) {
          when '\a':
            do_cmd();
            term.state = NORMAL;
          when '\e':
            term.state = CMD_ESCAPE;
          when '\n' or '\r':

            if (term.cmd_num != 1337)
              term_push_cmd(c);

          otherwise:
            term_push_cmd(c);
        }

      when IGNORE_STRING:
        switch (c) {
          when '\a':
            term.state = NORMAL;
          when '\e':
            term.state = ESCAPE;
          when '\n' or '\r':

            ;
        }

      when DCS_START:
        term.cmd_num = -1;
        term.cmd_len = 0;
        term.dcs_cmd = 0;
        switch (c) {
          when '@' ... '~':
            term.dcs_cmd = c;
            do_dcs();
            term.state = DCS_PASSTHROUGH;
          when '\e':
            term.state = DCS_ESCAPE;
          when '0' ... '9':
            term.state = DCS_PARAM;
          when ';':
            term.state = DCS_PARAM;
          when ':':
            term.state = DCS_IGNORE;
          when '<' ... '?':
            term.dcs_cmd = c;
            term.state = DCS_PARAM;
          when ' ' ... '/':
            term.dcs_cmd = c;
            term.state = DCS_INTERMEDIATE;
          otherwise:
            term.state = DCS_IGNORE;
        }

      when DCS_PARAM:
        switch (c) {
          when '@' ... '~':
            term.dcs_cmd = term.dcs_cmd << 8 | c;
            do_dcs();
            term.state = DCS_PASSTHROUGH;
          when '\e':
            term.state = DCS_ESCAPE;
            term.esc_mod = 0;
          when '0' ... '9' or ';' or ':':
            term.state = DCS_PARAM;
          when '<' ... '?':
            term.dcs_cmd = term.dcs_cmd << 8 | c;
            term.state = DCS_PARAM;
          when ' ' ... '/':
            term.dcs_cmd = term.dcs_cmd << 8 | c;
            term.state = DCS_INTERMEDIATE;
          otherwise:
            term.state = DCS_IGNORE;
        }

      when DCS_INTERMEDIATE:
        switch (c) {
          when '@' ... '~':
            term.dcs_cmd = term.dcs_cmd << 8 | c;
            do_dcs();
            term.state = DCS_PASSTHROUGH;
          when '\e':
            term.state = DCS_ESCAPE;
            term.esc_mod = 0;
          when '0' ... '?':
            term.state = DCS_IGNORE;
          when ' ' ... '/':
            term.dcs_cmd = term.dcs_cmd << 8 | c;
          otherwise:
            term.state = DCS_IGNORE;
        }

      when DCS_PASSTHROUGH:
        switch (c) {
          when '\e':
            term.state = DCS_ESCAPE;
            term.esc_mod = 0;
          otherwise:
            if (!term_push_cmd(c)) {
              do_dcs();
              term.cmd_buf[0] = c;
              term.cmd_len = 1;
            }
        }

      when DCS_IGNORE:
        switch (c) {
          when '\e':
            term.state = ESCAPE;
            term.esc_mod = 0;
        }

      when DCS_ESCAPE:
        if (c < 0x20) {
          do_ctrl(c);
          term.state = NORMAL;
        } else if (c < 0x30) {
          term.esc_mod = term.esc_mod ? 0xFF : c;
          term.state = ESCAPE;
        } else if (c == '\\') {

          do_dcs();
          term.state = NORMAL;
        } else {
          term.state = ESCAPE;
          term.imgs.parser_state = NULL;
          do_esc(c);
        }
    }
  }

  if (term.ring_enabled && term.curs.y != oldy)
    term.ring_enabled = false;

  if (cfg.ligatures_support > 1) {

    term_invalidate(0, oldy, term.cols - 1, oldy);
  }


  term_schedule_search_update();


  win_schedule_update();


  if (term.printing) {
    printer_write(term.printbuf, term.printbuf_pos);
    term.printbuf_pos = 0;
  }
}
