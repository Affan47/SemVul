
      unsigned int compile(char *ss, char *se, const unsigned int depth, unsigned int *const p_ref,
                           const bool is_single) {
        if (depth>256) {
          cimg::strellipsize(expr,64);
          throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                      "CImg<%s>::%s: Call stack overflow (infinite recursion?), "
                                      "in expression '%s%s%s'.",
                                      pixel_type(),_cimg_mp_calling_function,
                                      (ss - 4)>expr._data?"...":"",
                                      (ss - 4)>expr._data?ss - 4:expr._data,
                                      se<&expr.back()?"...":"");
        }
        char c1, c2, c3, c4;


        do {
          c2 = 0;
          if (ss<se) {
            while (*ss && (cimg::is_blank(*ss) || *ss==';')) ++ss;
            while (se>ss && (cimg::is_blank(c1 = *(se - 1)) || c1==';')) --se;
          }
          while (*ss=='(' && *(se - 1)==')' && std::strchr(ss,')')==se - 1) {
            ++ss; --se; c2 = 1;
          }
        } while (c2 && ss<se);

        if (se<=ss || !*ss) {
          cimg::strellipsize(expr,64);
          throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                      "CImg<%s>::%s: %s%s Missing %s, in expression '%s%s%s'.",
                                      pixel_type(),_cimg_mp_calling_function,s_op,*s_op?":":"",
                                      *s_op=='F'?"argument":"item",
                                      (ss_op - 4)>expr._data?"...":"",
                                      (ss_op - 4)>expr._data?ss_op - 4:expr._data,
                                      ss_op + std::strlen(ss_op)<&expr.back()?"...":"");
        }

        const char *const previous_s_op = s_op, *const previous_ss_op = ss_op;
        const unsigned int depth1 = depth + 1;
        unsigned int pos, p1, p2, p3, arg1, arg2, arg3, arg4, arg5, arg6;
        char
          *const se1 = se - 1, *const se2 = se - 2, *const se3 = se - 3,
          *const ss1 = ss + 1, *const ss2 = ss + 2, *const ss3 = ss + 3, *const ss4 = ss + 4,
          *const ss5 = ss + 5, *const ss6 = ss + 6, *const ss7 = ss + 7, *const ss8 = ss + 8,
          *s, *ps, *ns, *s0, *s1, *s2, *s3, sep = 0, end = 0;
        double val = 0, val1, val2;
        mp_func op;


        if (p_ref) { *p_ref = 0; p_ref[1] = p_ref[2] = p_ref[3] = p_ref[4] = p_ref[5] = p_ref[6] = ~0U; }

        const char saved_char = *se; *se = 0;
        const unsigned int clevel = level[ss - expr._data], clevel1 = clevel + 1;
        bool is_sth, is_relative;
        CImg<uintT> ref;
        CImg<charT> variable_name;
        CImgList<ulongT> l_opcode;


        int nb = 0;
        s = ss + (*ss=='+' || *ss=='-'?1:0);
        if (*s=='i' || *s=='I' || *s=='n' || *s=='N') {
          is_sth = *ss=='-';
          if (!cimg::strcasecmp(s,"inf")) { val = cimg::type<double>::inf(); nb = 1; }
          else if (!cimg::strcasecmp(s,"nan")) { val = cimg::type<double>::nan(); nb = 1; }
          if (nb==1 && is_sth) val = -val;
        } else if (*s=='0' && (s[1]=='x' || s[1]=='X')) {
          is_sth = *ss=='-';
          if (cimg_sscanf(s + 2,"%x%c",&arg1,&sep)==1) {
            nb = 1;
            val = (double)arg1;
            if (is_sth) val = -val;
          }
        }
        if (!nb) nb = cimg_sscanf(ss,"%lf%c%c",&val,&(sep=0),&(end=0));
        if (nb==1) _cimg_mp_constant(val);
        if (nb==2 && sep=='%') _cimg_mp_constant(val/100);

        if (ss1==se) switch (*ss) {
          case 'c' : _cimg_mp_return(reserved_label[(int)'c']!=~0U?reserved_label[(int)'c']:_cimg_mp_slot_c);
          case 'd' : _cimg_mp_return(reserved_label[(int)'d']!=~0U?reserved_label[(int)'d']:20);
          case 'e' : _cimg_mp_return(reserved_label[(int)'e']!=~0U?reserved_label[(int)'e']:27);
          case 'h' : _cimg_mp_return(reserved_label[(int)'h']!=~0U?reserved_label[(int)'h']:19);
          case 'l' : _cimg_mp_return(reserved_label[(int)'l']!=~0U?reserved_label[(int)'l']:26);
          case 'r' : _cimg_mp_return(reserved_label[(int)'r']!=~0U?reserved_label[(int)'r']:22);
          case 's' : _cimg_mp_return(reserved_label[(int)'s']!=~0U?reserved_label[(int)'s']:21);
          case 't' : _cimg_mp_return(reserved_label[(int)'t']!=~0U?reserved_label[(int)'t']:17);
          case 'w' : _cimg_mp_return(reserved_label[(int)'w']!=~0U?reserved_label[(int)'w']:18);
          case 'x' : _cimg_mp_return(reserved_label[(int)'x']!=~0U?reserved_label[(int)'x']:_cimg_mp_slot_x);
          case 'y' : _cimg_mp_return(reserved_label[(int)'y']!=~0U?reserved_label[(int)'y']:_cimg_mp_slot_y);
          case 'z' : _cimg_mp_return(reserved_label[(int)'z']!=~0U?reserved_label[(int)'z']:_cimg_mp_slot_z);
          case 'u' :
            if (reserved_label[(int)'u']!=~0U) _cimg_mp_return(reserved_label[(int)'u']);
            _cimg_mp_scalar2(mp_u,0,1);
          case 'g' :
            if (reserved_label[(int)'g']!=~0U) _cimg_mp_return(reserved_label[(int)'g']);
            _cimg_mp_scalar0(mp_g);
          case 'i' :
            if (reserved_label[(int)'i']!=~0U) _cimg_mp_return(reserved_label[(int)'i']);
            _cimg_mp_scalar0(mp_i);
          case 'I' :
            _cimg_mp_op("Variable 'I'");
            if (reserved_label[(int)'I']!=~0U) _cimg_mp_return(reserved_label[(int)'I']);
            if (!imgin._spectrum) _cimg_mp_return(0);
            need_input_copy = true;
            pos = vector(imgin._spectrum);
            CImg<ulongT>::vector((ulongT)mp_Joff,pos,0,0,imgin._spectrum).move_to(code);
            _cimg_mp_return(pos);
          case 'R' :
            if (reserved_label[(int)'R']!=~0U) _cimg_mp_return(reserved_label[(int)'R']);
            need_input_copy = true;
            _cimg_mp_scalar6(mp_ixyzc,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,0,0,0);
          case 'G' :
            if (reserved_label[(int)'G']!=~0U) _cimg_mp_return(reserved_label[(int)'G']);
            need_input_copy = true;
            _cimg_mp_scalar6(mp_ixyzc,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,1,0,0);
          case 'B' :
            if (reserved_label[(int)'B']!=~0U) _cimg_mp_return(reserved_label[(int)'B']);
            need_input_copy = true;
            _cimg_mp_scalar6(mp_ixyzc,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,2,0,0);
          case 'A' :
            if (reserved_label[(int)'A']!=~0U) _cimg_mp_return(reserved_label[(int)'A']);
            need_input_copy = true;
            _cimg_mp_scalar6(mp_ixyzc,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,3,0,0);
          }
        else if (ss2==se) {
          arg1 = arg2 = ~0U;
          if (*ss=='w' && *ss1=='h')
            _cimg_mp_return(reserved_label[0]!=~0U?reserved_label[0]:23);
          if (*ss=='p' && *ss1=='i')
            _cimg_mp_return(reserved_label[3]!=~0U?reserved_label[3]:28);
          if (*ss=='i') {
            if (*ss1>='0' && *ss1<='9') {
              pos = 19 + *ss1 - '0';
              if (reserved_label[pos]!=~0U) _cimg_mp_return(reserved_label[pos]);
              need_input_copy = true;
              _cimg_mp_scalar6(mp_ixyzc,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,pos - 19,0,0);
            }
            switch (*ss1) {
            case 'm' : arg1 = 4; arg2 = 0; break;
            case 'M' : arg1 = 5; arg2 = 1; break;
            case 'a' : arg1 = 6; arg2 = 2; break;
            case 'v' : arg1 = 7; arg2 = 3; break;
            case 's' : arg1 = 8; arg2 = 12; break;
            case 'p' : arg1 = 9; arg2 = 13; break;
            case 'c' :
              if (reserved_label[10]!=~0U) _cimg_mp_return(reserved_label[10]);
              if (mem_img_median==~0U) mem_img_median = imgin?constant(imgin.median()):0;
              _cimg_mp_return(mem_img_median);
              break;
            }
          }
          else if (*ss1=='m') switch (*ss) {
            case 'x' : arg1 = 11; arg2 = 4; break;
            case 'y' : arg1 = 12; arg2 = 5; break;
            case 'z' : arg1 = 13; arg2 = 6; break;
            case 'c' : arg1 = 14; arg2 = 7; break;
            }
          else if (*ss1=='M') switch (*ss) {
            case 'x' : arg1 = 15; arg2 = 8; break;
            case 'y' : arg1 = 16; arg2 = 9; break;
            case 'z' : arg1 = 17; arg2 = 10; break;
            case 'c' : arg1 = 18; arg2 = 11; break;
            }
          if (arg1!=~0U) {
            if (reserved_label[arg1]!=~0U) _cimg_mp_return(reserved_label[arg1]);
            if (!img_stats) {
              img_stats.assign(1,14,1,1,0).fill(imgin.get_stats(),false);
              mem_img_stats.assign(1,14,1,1,~0U);
            }
            if (mem_img_stats[arg2]==~0U) mem_img_stats[arg2] = constant(img_stats[arg2]);
            _cimg_mp_return(mem_img_stats[arg2]);
          }
        } else if (ss3==se) {
          if (*ss=='w' && *ss1=='h' && *ss2=='d')
            _cimg_mp_return(reserved_label[1]!=~0U?reserved_label[1]:24);
        } else if (ss4==se) {
          if (*ss=='w' && *ss1=='h' && *ss2=='d' && *ss3=='s')
            _cimg_mp_return(reserved_label[2]!=~0U?reserved_label[2]:25);
        }

        pos = ~0U;
        is_sth = false;
        for (s0 = ss, s = ss1; s<se1; ++s)
          if (*s==';' && level[s - expr._data]==clevel) {
            arg1 = code_end._width;
            arg2 = compile(s0,s++,depth,0,is_single);
            if (code_end._width==arg1) pos = arg2;
            is_sth = true;
            while (*s && (cimg::is_blank(*s) || *s==';')) ++s;
            s0 = s;
          }
        if (is_sth) {
          arg1 = code_end._width;
          arg2 = compile(s0,se,depth,p_ref,is_single);
          if (code_end._width==arg1) pos = arg2;
          _cimg_mp_return(pos);
        }


        for (s = ss1, ps = ss, ns = ss2; s<se1; ++s, ++ps, ++ns)
          if (*s=='=' && *ns!='=' && *ps!='=' && *ps!='>' && *ps!='<' && *ps!='!' &&
              *ps!='+' && *ps!='-' && *ps!='*' && *ps!='/' && *ps!='%' &&
              *ps!='>' && *ps!='<' && *ps!='&' && *ps!='|' && *ps!='^' &&
              level[s - expr._data]==clevel) {
            variable_name.assign(ss,(unsigned int)(s + 1 - ss)).back() = 0;
            cimg::strpare(variable_name,false,true);
            const unsigned int l_variable_name = (unsigned int)std::strlen(variable_name);
            char *const ve1 = ss + l_variable_name - 1;
            _cimg_mp_op("Operator '='");


            if (l_variable_name>2 && (*ss=='i' || *ss=='j' || *ss=='I' || *ss=='J') && (*ss1=='(' || *ss1=='[') &&
                (reserved_label[(int)*ss]==~0U || *ss1=='(' || !_cimg_mp_is_vector(reserved_label[(int)*ss]))) {
              is_relative = *ss=='j' || *ss=='J';

              if (*ss1=='[' && *ve1==']') {
                if (!is_single) is_parallelizable = false;
                if (*ss2=='#') {
                  s0 = ss3; while (s0<ve1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                  p1 = compile(ss3,s0++,depth1,0,is_single);
                  _cimg_mp_check_list(true);
                } else { p1 = ~0U; s0 = ss2; }
                arg1 = compile(s0,ve1,depth1,0,is_single);
                _cimg_mp_check_type(arg1,0,1,0);
                arg2 = compile(s + 1,se,depth1,0,is_single);
                if (_cimg_mp_is_vector(arg2)) {
                  p2 = ~0U;
                  if (p1==~0U) p2 = imgin._spectrum;
                  else if (_cimg_mp_is_constant(p1)) {
                    p3 = (unsigned int)cimg::mod((int)mem[p1],listin.width());
                    p2 = listin[p3]._spectrum;
                  }
                  if (!p2) _cimg_mp_return(0);
                } else p2 = 0;
                _cimg_mp_check_type(arg2,2,*ss>='i'?1:3,p2);

                if (p_ref) {
                  *p_ref = _cimg_mp_is_vector(arg2)?4:2;
                  p_ref[1] = p1;
                  p_ref[2] = (unsigned int)is_relative;
                  p_ref[3] = arg1;
                  if (_cimg_mp_is_vector(arg2))
                    set_variable_vector(arg2);
                  else if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2;
                  if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2;
                  if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
                }

                if (p1!=~0U) {
                  if (!listout) _cimg_mp_return(arg2);
                  if (*ss>='i')
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_joff:mp_list_set_ioff),
                                        arg2,p1,arg1).move_to(code);
                  else if (_cimg_mp_is_scalar(arg2))
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_s:mp_list_set_Ioff_s),
                                        arg2,p1,arg1).move_to(code);
                  else
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_v:mp_list_set_Ioff_v),
                                        arg2,p1,arg1,_cimg_mp_size(arg2)).move_to(code);
                } else {
                  if (!imgout) _cimg_mp_return(arg2);
                  if (*ss>='i')
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_set_joff:mp_set_ioff),
                                        arg2,arg1).move_to(code);
                  else if (_cimg_mp_is_scalar(arg2))
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_s:mp_set_Ioff_s),
                                        arg2,arg1).move_to(code);
                  else
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_v:mp_set_Ioff_v),
                                        arg2,arg1,_cimg_mp_size(arg2)).move_to(code);
                }
                _cimg_mp_return(arg2);
              }

              if (*ss1=='(' && *ve1==')') {
                if (!is_single) is_parallelizable = false;
                if (*ss2=='#') {
                  s0 = ss3; while (s0<ve1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                  p1 = compile(ss3,s0++,depth1,0,is_single);
                  _cimg_mp_check_list(true);
                } else { p1 = ~0U; s0 = ss2; }
                arg1 = is_relative?0U:(unsigned int)_cimg_mp_slot_x;
                arg2 = is_relative?0U:(unsigned int)_cimg_mp_slot_y;
                arg3 = is_relative?0U:(unsigned int)_cimg_mp_slot_z;
                arg4 = is_relative?0U:(unsigned int)_cimg_mp_slot_c;
                arg5 = compile(s + 1,se,depth1,0,is_single);
                if (s0<ve1) {
                  s1 = s0; while (s1<ve1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                  arg1 = compile(s0,s1,depth1,0,is_single);
                  if (_cimg_mp_is_vector(arg1)) {
                    p2 = _cimg_mp_size(arg1);
                    ++arg1;
                    if (p2>1) {
                      arg2 = arg1 + 1;
                      if (p2>2) {
                        arg3 = arg2 + 1;
                        if (p2>3) arg4 = arg3 + 1;
                      }
                    }
                  } else if (s1<ve1) {
                    s2 = ++s1; while (s2<ve1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                    arg2 = compile(s1,s2,depth1,0,is_single);
                    if (s2<ve1) {
                      s3 = ++s2; while (s3<ve1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
                      arg3 = compile(s2,s3,depth1,0,is_single);
                      if (s3<ve1) arg4 = compile(++s3,ve1,depth1,0,is_single);
                    }
                  }
                }

                if (_cimg_mp_is_vector(arg5)) {
                  p2 = ~0U;
                  if (p1==~0U) p2 = imgin._spectrum;
                  else if (_cimg_mp_is_constant(p1)) {
                    p3 = (unsigned int)cimg::mod((int)mem[p1],listin.width());
                    p2 = listin[p3]._spectrum;
                  }
                  if (!p2) _cimg_mp_return(0);
                } else p2 = 0;
                _cimg_mp_check_type(arg5,2,*ss>='i'?1:3,p2);

                if (p_ref) {
                  *p_ref = _cimg_mp_is_vector(arg5)?5:3;
                  p_ref[1] = p1;
                  p_ref[2] = (unsigned int)is_relative;
                  p_ref[3] = arg1;
                  p_ref[4] = arg2;
                  p_ref[5] = arg3;
                  p_ref[6] = arg4;
                  if (_cimg_mp_is_vector(arg5))
                    set_variable_vector(arg5);
                  else if (_cimg_mp_is_comp(arg5)) memtype[arg5] = -2;
                  if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2;
                  if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
                  if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2;
                  if (_cimg_mp_is_comp(arg3)) memtype[arg3] = -2;
                  if (_cimg_mp_is_comp(arg4)) memtype[arg4] = -2;
                }
                if (p1!=~0U) {
                  if (!listout) _cimg_mp_return(arg5);
                  if (*ss>='i')
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_jxyzc:mp_list_set_ixyzc),
                                        arg5,p1,arg1,arg2,arg3,arg4).move_to(code);
                  else if (_cimg_mp_is_scalar(arg5))
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_s:mp_list_set_Ixyz_s),
                                        arg5,p1,arg1,arg2,arg3).move_to(code);
                  else
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_v:mp_list_set_Ixyz_v),
                                        arg5,p1,arg1,arg2,arg3,_cimg_mp_size(arg5)).move_to(code);
                } else {
                  if (!imgout) _cimg_mp_return(arg5);
                  if (*ss>='i')
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_set_jxyzc:mp_set_ixyzc),
                                        arg5,arg1,arg2,arg3,arg4).move_to(code);
                  else if (_cimg_mp_is_scalar(arg5))
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_s:mp_set_Ixyz_s),
                                        arg5,arg1,arg2,arg3).move_to(code);
                  else
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_v:mp_set_Ixyz_v),
                                        arg5,arg1,arg2,arg3,_cimg_mp_size(arg5)).move_to(code);
                }
                _cimg_mp_return(arg5);
              }
            }


            if (l_variable_name>3 && *ve1==']' && *ss!='[') {
              s0 = ve1; while (s0>ss && (*s0!='[' || level[s0 - expr._data]!=clevel)) --s0;
              is_sth = true;
              if (*ss>='0' && *ss<='9') is_sth = false;
              else for (ns = ss; ns<s0; ++ns)
                     if (!is_varchar(*ns)) { is_sth = false; break; }
              if (is_sth && s0>ss) {
                variable_name[s0 - ss] = 0;
                arg1 = ~0U;
                arg2 = compile(++s0,ve1,depth1,0,is_single);
                arg3 = compile(s + 1,se,depth1,0,is_single);
                _cimg_mp_check_type(arg3,2,1,0);

                if (variable_name[1]) {
                  cimglist_for(variable_def,i) if (!std::strcmp(variable_name,variable_def[i])) {
                    arg1 = variable_pos[i]; break;
                  }
                } else arg1 = reserved_label[(int)*variable_name];
                if (arg1==~0U) compile(ss,s0 - 1,depth1,0,is_single);
                else {
                  if (_cimg_mp_is_scalar(arg1)) compile(ss,s,depth1,0,is_single);
                  if (_cimg_mp_is_constant(arg2)) {
                    nb = (int)mem[arg2];
                    if (nb>=0 && nb<(int)_cimg_mp_size(arg1)) {
                      arg1+=nb + 1;
                      CImg<ulongT>::vector((ulongT)mp_copy,arg1,arg3).move_to(code);
                      _cimg_mp_return(arg1);
                    }
                    compile(ss,s,depth1,0,is_single);
                  }


                  if (p_ref) {
                    *p_ref = 1;
                    p_ref[1] = arg1;
                    p_ref[2] = arg2;
                    if (_cimg_mp_is_comp(arg3)) memtype[arg3] = -2;
                    if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2;
                  }
                  CImg<ulongT>::vector((ulongT)mp_vector_set_off,arg3,arg1,(ulongT)_cimg_mp_size(arg1),
                                       arg2,arg3).
                    move_to(code);
                  _cimg_mp_return(arg3);
                }
              }
            }


            if (l_variable_name>2 && *ve1==')' && *ss!='(') {
              s0 = ve1; while (s0>ss && *s0!='(') --s0;
              is_sth = std::strncmp(variable_name,"debug(",6) &&
                std::strncmp(variable_name,"print(",6);
              if (*ss>='0' && *ss<='9') is_sth = false;
              else for (ns = ss; ns<s0; ++ns)
                     if (!is_varchar(*ns)) { is_sth = false; break; }

              if (is_sth && s0>ss) {
                s0 = variable_name._data + (s0 - ss);
                *s0 = 0;
                s1 = variable_name._data + l_variable_name - 1;
                CImg<charT>(variable_name._data,(unsigned int)(s0 - variable_name._data + 1)).move_to(macro_def,0);
                ++s; while (*s && cimg::is_blank(*s)) ++s;
                CImg<charT>(s,(unsigned int)(se - s + 1)).move_to(macro_body,0);

                p1 = 1;
                for (s = s0 + 1; s<=s1; ++p1, s = ns + 1) {
                  if (p1>24) {
                    *se = saved_char;
                    cimg::strellipsize(variable_name,64);
                    s0 = ss - 4>expr._data?ss - 4:expr._data;
                    cimg::strellipsize(s0,64);
                    throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                                "CImg<%s>::%s: %s: Too much specified arguments (>24) in macro "
                                                "definition '%s()', in expression '%s%s%s'.",
                                                pixel_type(),_cimg_mp_calling_function,s_op,
                                                variable_name._data,
                                                s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
                  }
                  while (*s && cimg::is_blank(*s)) ++s;
                  if (*s==')' && p1==1) break;

                  s2 = s;
                  is_sth = true;
                  if (*s>='0' && *s<='9') is_sth = false;
                  else for (ns = s; ns<s1 && *ns!=',' && !cimg::is_blank(*ns); ++ns)
                         if (!is_varchar(*ns)) { is_sth = false; break; }
                  s3 = ns;
                  while (*ns && cimg::is_blank(*ns)) ++ns;
                  if (!is_sth || s2==s3 || (*ns!=',' && ns!=s1)) {
                    *se = saved_char;
                    cimg::strellipsize(variable_name,64);
                    s0 = ss - 4>expr._data?ss - 4:expr._data;
                    cimg::strellipsize(s0,64);
                    throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                                "CImg<%s>::%s: %s: %s name specified for argument %u when defining "
                                                "macro '%s()', in expression '%s%s%s'.",
                                                pixel_type(),_cimg_mp_calling_function,s_op,
                                                is_sth?"Empty":"Invalid",p1,
                                                variable_name._data,
                                                s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
                  }
                  if (ns==s1 || *ns==',') {
                    *s3 = 0;
                    p2 = (unsigned int)(s3 - s2);
                    for (ps = std::strstr(macro_body[0],s2); ps; ps = std::strstr(ps,s2)) {
                      if (!((ps>macro_body[0]._data && is_varchar(*(ps - 1))) ||
                            (ps + p2<macro_body[0].end() && is_varchar(*(ps + p2))))) {
                        if (ps>macro_body[0]._data && *(ps - 1)=='#') {
                          *(ps - 1) = (char)p1;
                          if (ps + p2<macro_body[0].end() && *(ps + p2)=='#') {
                            std::memmove(ps,ps + p2 + 1,macro_body[0].end() - ps - p2 - 1);
                            macro_body[0]._width-=p2 + 1;
                          } else {
                            std::memmove(ps,ps + p2,macro_body[0].end() - ps - p2);
                            macro_body[0]._width-=p2;
                          }
                        } else if (ps + p2<macro_body[0].end() && *(ps + p2)=='#') {
                          *(ps++) = (char)p1;
                          std::memmove(ps,ps + p2,macro_body[0].end() - ps - p2);
                          macro_body[0]._width-=p2;
                        } else {
                          if (p2<3) {
                            ps-=(ulongT)macro_body[0]._data;
                            macro_body[0].resize(macro_body[0]._width - p2 + 3,1,1,1,0);
                            ps+=(ulongT)macro_body[0]._data;
                          } else macro_body[0]._width-=p2 - 3;
                          std::memmove(ps + 3,ps + p2,macro_body[0].end() - ps - 3);
                          *(ps++) = '(';
                          *(ps++) = (char)p1;
                          *(ps++) = ')';
                        }
                      } else ++ps;
                    }
                  }
                }


                macro_def[0].resize(macro_def[0]._width + 1,1,1,1,0).back() = (char)(p1 - 1);


                is_inside_string(macro_body[0]).move_to(macro_body_is_string,0);
                _cimg_mp_return_nan();
              }
            }


            is_sth = true;
            const bool is_const = l_variable_name>6 && !std::strncmp(variable_name,"const ",6);

            s0 = variable_name._data;
            if (is_const) {
              s0+=6; while (cimg::is_blank(*s0)) ++s0;
              variable_name.resize(variable_name.end() - s0,1,1,1,0,0,1);
            }

            if (*variable_name>='0' && *variable_name<='9') is_sth = false;
            else for (ns = variable_name._data; *ns; ++ns)
                   if (!is_varchar(*ns)) { is_sth = false; break; }


            if (is_sth) {
              arg3 = variable_name[1]?~0U:*variable_name;
              if (variable_name[1] && !variable_name[2]) {
                c1 = variable_name[0];
                c2 = variable_name[1];
                if (c1=='w' && c2=='h') arg3 = 0;
                else if (c1=='p' && c2=='i') arg3 = 3;
                else if (c1=='i') {
                  if (c2>='0' && c2<='9') arg3 = 19 + c2 - '0';
                  else if (c2=='m') arg3 = 4;
                  else if (c2=='M') arg3 = 5;
                  else if (c2=='a') arg3 = 6;
                  else if (c2=='v') arg3 = 7;
                  else if (c2=='s') arg3 = 8;
                  else if (c2=='p') arg3 = 9;
                  else if (c2=='c') arg3 = 10;
                } else if (c2=='m') {
                  if (c1=='x') arg3 = 11;
                  else if (c1=='y') arg3 = 12;
                  else if (c1=='z') arg3 = 13;
                  else if (c1=='c') arg3 = 14;
                } else if (c2=='M') {
                  if (c1=='x') arg3 = 15;
                  else if (c1=='y') arg3 = 16;
                  else if (c1=='z') arg3 = 17;
                  else if (c1=='c') arg3 = 18;
                }
              } else if (variable_name[1] && variable_name[2] && !variable_name[3]) {
                c1 = variable_name[0];
                c2 = variable_name[1];
                c3 = variable_name[2];
                if (c1=='w' && c2=='h' && c3=='d') arg3 = 1;
              } else if (variable_name[1] && variable_name[2] && variable_name[3] &&
                         !variable_name[4]) {
                c1 = variable_name[0];
                c2 = variable_name[1];
                c3 = variable_name[2];
                c4 = variable_name[3];
                if (c1=='w' && c2=='h' && c3=='d' && c4=='s') arg3 = 2;
              } else if (!std::strcmp(variable_name,"interpolation")) arg3 = 29;
              else if (!std::strcmp(variable_name,"boundary")) arg3 = 30;

              arg1 = ~0U;
              arg2 = compile(s + 1,se,depth1,0,is_single);
              if (is_const) _cimg_mp_check_constant(arg2,2,0);

              if (arg3!=~0U)
                arg1 = reserved_label[arg3];
              else
                cimglist_for(variable_def,i)
                  if (!std::strcmp(variable_name,variable_def[i])) { arg1 = variable_pos[i]; break; }

              if (arg1==~0U) {
                if (_cimg_mp_is_vector(arg2)) {
                  arg1 = is_comp_vector(arg2)?arg2:vector_copy(arg2);
                  set_variable_vector(arg1);
                } else {
                  if (is_const) arg1 = arg2;
                  else {
                    arg1 = _cimg_mp_is_comp(arg2)?arg2:scalar1(mp_copy,arg2);
                    memtype[arg1] = -1;
                  }
                }

                if (arg3!=~0U) reserved_label[arg3] = arg1;
                else {
                  if (variable_def._width>=variable_pos._width) variable_pos.resize(-200,1,1,1,0);
                  variable_pos[variable_def._width] = arg1;
                  variable_name.move_to(variable_def);
                }

              } else {
                if (is_const || _cimg_mp_is_constant(arg1)) {
                  *se = saved_char;
                  cimg::strellipsize(variable_name,64);
                  s0 = ss - 4>expr._data?ss - 4:expr._data;
                  cimg::strellipsize(s0,64);
                  throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                              "CImg<%s>::%s: %s: Invalid assignment of %sconst variable '%s'%s, "
                                              "in expression '%s%s%s'.",
                                              pixel_type(),_cimg_mp_calling_function,s_op,
                                              _cimg_mp_is_constant(arg1)?"already-defined ":"non-",
                                              variable_name._data,
                                              !_cimg_mp_is_constant(arg1) && is_const?" as a new const variable":"",
                                              s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
                }
                _cimg_mp_check_type(arg2,2,_cimg_mp_is_vector(arg1)?3:1,_cimg_mp_size(arg1));
                if (_cimg_mp_is_vector(arg1)) {
                  if (_cimg_mp_is_vector(arg2))
                    CImg<ulongT>::vector((ulongT)mp_vector_copy,arg1,arg2,(ulongT)_cimg_mp_size(arg1)).
                      move_to(code);
                  else
                    CImg<ulongT>::vector((ulongT)mp_vector_init,arg1,1,(ulongT)_cimg_mp_size(arg1),arg2).
                      move_to(code);
                } else
                  CImg<ulongT>::vector((ulongT)mp_copy,arg1,arg2).move_to(code);
              }
              _cimg_mp_return(arg1);
            }


            arg1 = ~0U;
            is_sth = (bool)std::strchr(variable_name,'?');
            if (is_sth) break;

            if (l_variable_name>2 && (std::strchr(variable_name,'(') || std::strchr(variable_name,'['))) {
              ref.assign(7);
              arg1 = compile(ss,s,depth1,ref,is_single);
              arg2 = compile(s + 1,se,depth1,0,is_single);

              if (*ref==1) {
                _cimg_mp_check_type(arg2,2,1,0);
                arg3 = ref[1];
                arg4 = ref[2];
                if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
                CImg<ulongT>::vector((ulongT)mp_vector_set_off,arg2,arg3,(ulongT)_cimg_mp_size(arg3),arg4,arg2).
                  move_to(code);
                _cimg_mp_return(arg2);
              }

              if (*ref==2) {
                if (!is_single) is_parallelizable = false;
                _cimg_mp_check_type(arg2,2,1,0);
                p1 = ref[1];
                is_relative = (bool)ref[2];
                arg3 = ref[3];
                if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
                if (p1!=~0U) {
                  if (!listout) _cimg_mp_return(arg2);
                  CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_joff:mp_list_set_ioff),
                                      arg2,p1,arg3).move_to(code);
                } else {
                  if (!imgout) _cimg_mp_return(arg2);
                  CImg<ulongT>::vector((ulongT)(is_relative?mp_set_joff:mp_set_ioff),
                                      arg2,arg3).move_to(code);
                }
                _cimg_mp_return(arg2);
              }

              if (*ref==3) {
                if (!is_single) is_parallelizable = false;
                _cimg_mp_check_type(arg2,2,1,0);
                p1 = ref[1];
                is_relative = (bool)ref[2];
                arg3 = ref[3];
                arg4 = ref[4];
                arg5 = ref[5];
                arg6 = ref[6];
                if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
                if (p1!=~0U) {
                  if (!listout) _cimg_mp_return(arg2);
                  CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_jxyzc:mp_list_set_ixyzc),
                                      arg2,p1,arg3,arg4,arg5,arg6).move_to(code);
                } else {
                  if (!imgout) _cimg_mp_return(arg2);
                  CImg<ulongT>::vector((ulongT)(is_relative?mp_set_jxyzc:mp_set_ixyzc),
                                      arg2,arg3,arg4,arg5,arg6).move_to(code);
                }
                _cimg_mp_return(arg2);
              }

              if (*ref==4) {
                if (!is_single) is_parallelizable = false;
                _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
                p1 = ref[1];
                is_relative = (bool)ref[2];
                arg3 = ref[3];
                if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
                if (p1!=~0U) {
                  if (!listout) _cimg_mp_return(arg2);
                  if (_cimg_mp_is_scalar(arg2))
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_s:mp_list_set_Ioff_s),
                                        arg2,p1,arg3).move_to(code);
                  else
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_v:mp_list_set_Ioff_v),
                                        arg2,p1,arg3,_cimg_mp_size(arg2)).move_to(code);
                } else {
                  if (!imgout) _cimg_mp_return(arg2);
                  if (_cimg_mp_is_scalar(arg2))
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_s:mp_set_Ioff_s),
                                        arg2,arg3).move_to(code);
                  else
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_v:mp_set_Ioff_v),
                                        arg2,arg3,_cimg_mp_size(arg2)).move_to(code);
                }
                _cimg_mp_return(arg2);
              }

              if (*ref==5) {
                if (!is_single) is_parallelizable = false;
                _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
                p1 = ref[1];
                is_relative = (bool)ref[2];
                arg3 = ref[3];
                arg4 = ref[4];
                arg5 = ref[5];
                if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
                if (p1!=~0U) {
                  if (!listout) _cimg_mp_return(arg2);
                  if (_cimg_mp_is_scalar(arg2))
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_s:mp_list_set_Ixyz_s),
                                        arg2,p1,arg3,arg4,arg5).move_to(code);
                  else
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_v:mp_list_set_Ixyz_v),
                                        arg2,p1,arg3,arg4,arg5,_cimg_mp_size(arg2)).move_to(code);
                } else {
                  if (!imgout) _cimg_mp_return(arg2);
                  if (_cimg_mp_is_scalar(arg2))
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_s:mp_set_Ixyz_s),
                                        arg2,arg3,arg4,arg5).move_to(code);
                  else
                    CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_v:mp_set_Ixyz_v),
                                        arg2,arg3,arg4,arg5,_cimg_mp_size(arg2)).move_to(code);
                }
                _cimg_mp_return(arg2);
              }

              if (_cimg_mp_is_vector(arg1)) {
                _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
                if (_cimg_mp_is_vector(arg2))
                  CImg<ulongT>::vector((ulongT)mp_vector_copy,arg1,arg2,(ulongT)_cimg_mp_size(arg1)).
                    move_to(code);
                else
                  CImg<ulongT>::vector((ulongT)mp_vector_init,arg1,1,(ulongT)_cimg_mp_size(arg1),arg2).
                    move_to(code);
                _cimg_mp_return(arg1);
              }

              if (_cimg_mp_is_variable(arg1)) {
                _cimg_mp_check_type(arg2,2,1,0);
                CImg<ulongT>::vector((ulongT)mp_copy,arg1,arg2).move_to(code);
                _cimg_mp_return(arg1);
              }
            }


            *se = saved_char;
            cimg::strellipsize(variable_name,64);
            s0 = ss - 4>expr._data?ss - 4:expr._data;
            cimg::strellipsize(s0,64);
            throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                        "CImg<%s>::%s: %s: Invalid %slvalue '%s', "
                                        "in expression '%s%s%s'.",
                                        pixel_type(),_cimg_mp_calling_function,s_op,
                                        arg1!=~0U && _cimg_mp_is_constant(arg1)?"const ":"",
                                        variable_name._data,
                                        s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
          }


        for (s = se2, ps = se3, ns = ps - 1; s>ss1; --s, --ps, --ns)
          if (*s=='=' && (*ps=='*' || *ps=='/' || *ps=='^') && *ns==*ps &&
              level[s - expr._data]==clevel) {
            _cimg_mp_op(*ps=='*'?"Operator '**='":*ps=='/'?"Operator '//='":"Operator '^^='");

            ref.assign(7);
            arg1 = compile(ss,ns,depth1,ref,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);
            _cimg_mp_check_type(arg1,1,2,2);
            _cimg_mp_check_type(arg2,2,3,2);
            if (_cimg_mp_is_vector(arg2)) {
              if (*ps=='*')
                CImg<ulongT>::vector((ulongT)mp_complex_mul,arg1,arg1,arg2).move_to(code);
              else if (*ps=='/')
                CImg<ulongT>::vector((ulongT)mp_complex_div_vv,arg1,arg1,arg2).move_to(code);
              else
                CImg<ulongT>::vector((ulongT)mp_complex_pow_vv,arg1,arg1,arg2).move_to(code);
            } else {
              if (*ps=='*') {
                if (arg2==1) _cimg_mp_return(arg1);
                self_vector_s(arg1,mp_self_mul,arg2);
              } else if (*ps=='/') {
                if (arg2==1) _cimg_mp_return(arg1);
                self_vector_s(arg1,mp_self_div,arg2);
              } else {
                if (arg2==1) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)mp_complex_pow_vs,arg1,arg1,arg2).move_to(code);
              }
            }


            if (*ref==4) {
              if (!is_single) is_parallelizable = false;
              p1 = ref[1];
              is_relative = (bool)ref[2];
              arg3 = ref[3];
              if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
              if (p1!=~0U) {
                if (!listout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_v:mp_list_set_Ioff_v),
                                    arg1,p1,arg3,_cimg_mp_size(arg1)).move_to(code);
              } else {
                if (!imgout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_v:mp_set_Ioff_v),
                                    arg1,arg3,_cimg_mp_size(arg1)).move_to(code);
              }

            } else if (*ref==5) {
              if (!is_single) is_parallelizable = false;
              p1 = ref[1];
              is_relative = (bool)ref[2];
              arg3 = ref[3];
              arg4 = ref[4];
              arg5 = ref[5];
              if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
              if (p1!=~0U) {
                if (!listout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_v:mp_list_set_Ixyz_v),
                                    arg1,p1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
              } else {
                if (!imgout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_v:mp_set_Ixyz_v),
                                    arg1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
              }
            }

            _cimg_mp_return(arg1);
          }

        for (s = se2, ps = se3, ns = ps - 1; s>ss1; --s, --ps, --ns)
          if (*s=='=' && (*ps=='+' || *ps=='-' || *ps=='*' || *ps=='/' || *ps=='%' ||
                          *ps=='&' || *ps=='^' || *ps=='|' ||
                          (*ps=='>' && *ns=='>') || (*ps=='<' && *ns=='<')) &&
              level[s - expr._data]==clevel) {
            switch (*ps) {
            case '+' : op = mp_self_add; _cimg_mp_op("Operator '+='"); break;
            case '-' : op = mp_self_sub; _cimg_mp_op("Operator '-='"); break;
            case '*' : op = mp_self_mul; _cimg_mp_op("Operator '*='"); break;
            case '/' : op = mp_self_div; _cimg_mp_op("Operator '/='"); break;
            case '%' : op = mp_self_modulo; _cimg_mp_op("Operator '%='"); break;
            case '<' : op = mp_self_bitwise_left_shift; _cimg_mp_op("Operator '<<='"); break;
            case '>' : op = mp_self_bitwise_right_shift; _cimg_mp_op("Operator '>>='"); break;
            case '&' : op = mp_self_bitwise_and; _cimg_mp_op("Operator '&='"); break;
            case '|' : op = mp_self_bitwise_or; _cimg_mp_op("Operator '|='"); break;
            default : op = mp_self_pow; _cimg_mp_op("Operator '^='"); break;
            }
            s1 = *ps=='>' || *ps=='<'?ns:ps;

            ref.assign(7);
            arg1 = compile(ss,s1,depth1,ref,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);


            if ((op==mp_self_add || op==mp_self_sub) && !arg2) _cimg_mp_return(arg1);
            if ((op==mp_self_mul || op==mp_self_div) && arg2==1) _cimg_mp_return(arg1);


            if (*ref && (_cimg_mp_is_constant(arg1) || _cimg_mp_is_vector(arg1) || _cimg_mp_is_variable(arg1))) {
              if (_cimg_mp_is_vector(arg1)) arg1 = vector_copy(arg1);
              else arg1 = scalar1(mp_copy,arg1);
            }

            if (*ref==1) {
              _cimg_mp_check_type(arg2,2,1,0);
              arg3 = ref[1];
              arg4 = ref[2];
              if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
              CImg<ulongT>::vector((ulongT)op,arg1,arg2).move_to(code);
              CImg<ulongT>::vector((ulongT)mp_vector_set_off,arg1,arg3,(ulongT)_cimg_mp_size(arg3),arg4,arg1).
                move_to(code);
              _cimg_mp_return(arg1);
            }

            if (*ref==2) {
              if (!is_single) is_parallelizable = false;
              _cimg_mp_check_type(arg2,2,1,0);
              p1 = ref[1];
              is_relative = (bool)ref[2];
              arg3 = ref[3];
              if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
              CImg<ulongT>::vector((ulongT)op,arg1,arg2).move_to(code);
              if (p1!=~0U) {
                if (!listout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_joff:mp_list_set_ioff),
                                    arg1,p1,arg3).move_to(code);
              } else {
                if (!imgout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_set_joff:mp_set_ioff),
                                    arg1,arg3).move_to(code);
              }
              _cimg_mp_return(arg1);
            }

            if (*ref==3) {
              if (!is_single) is_parallelizable = false;
              _cimg_mp_check_type(arg2,2,1,0);
              p1 = ref[1];
              is_relative = (bool)ref[2];
              arg3 = ref[3];
              arg4 = ref[4];
              arg5 = ref[5];
              arg6 = ref[6];
              if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
              CImg<ulongT>::vector((ulongT)op,arg1,arg2).move_to(code);
              if (p1!=~0U) {
                if (!listout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_jxyzc:mp_list_set_ixyzc),
                                    arg1,p1,arg3,arg4,arg5,arg6).move_to(code);
              } else {
                if (!imgout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_set_jxyzc:mp_set_ixyzc),
                                    arg1,arg3,arg4,arg5,arg6).move_to(code);
              }
              _cimg_mp_return(arg1);
            }

            if (*ref==4) {
              if (!is_single) is_parallelizable = false;
              _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
              p1 = ref[1];
              is_relative = (bool)ref[2];
              arg3 = ref[3];
              if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
              if (_cimg_mp_is_scalar(arg2)) self_vector_s(arg1,op,arg2); else self_vector_v(arg1,op,arg2);
              if (p1!=~0U) {
                if (!listout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_v:mp_list_set_Ioff_v),
                                    arg1,p1,arg3,_cimg_mp_size(arg1)).move_to(code);
              } else {
                if (!imgout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_v:mp_set_Ioff_v),
                                    arg1,arg3,_cimg_mp_size(arg1)).move_to(code);
              }
              _cimg_mp_return(arg1);
            }

            if (*ref==5) {
              if (!is_single) is_parallelizable = false;
              _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
              p1 = ref[1];
              is_relative = (bool)ref[2];
              arg3 = ref[3];
              arg4 = ref[4];
              arg5 = ref[5];
              if (p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
              if (_cimg_mp_is_scalar(arg2)) self_vector_s(arg1,op,arg2); else self_vector_v(arg1,op,arg2);
              if (p1!=~0U) {
                if (!listout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_v:mp_list_set_Ixyz_v),
                                    arg1,p1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
              } else {
                if (!imgout) _cimg_mp_return(arg1);
                CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_v:mp_set_Ixyz_v),
                                    arg1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
              }
              _cimg_mp_return(arg1);
            }

            if (_cimg_mp_is_vector(arg1)) {
              _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
              if (_cimg_mp_is_vector(arg2)) self_vector_v(arg1,op,arg2);
              else self_vector_s(arg1,op,arg2);
              _cimg_mp_return(arg1);
            }

            if (_cimg_mp_is_variable(arg1)) {
              _cimg_mp_check_type(arg2,2,1,0);
              CImg<ulongT>::vector((ulongT)op,arg1,arg2).move_to(code);
              _cimg_mp_return(arg1);
            }

            variable_name.assign(ss,(unsigned int)(s - ss)).back() = 0;
            cimg::strpare(variable_name,false,true);
            *se = saved_char;
            s0 = ss - 4>expr._data?ss - 4:expr._data;
            cimg::strellipsize(s0,64);
            throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                        "CImg<%s>::%s: %s: Invalid %slvalue '%s', "
                                        "in expression '%s%s%s'.",
                                        pixel_type(),_cimg_mp_calling_function,s_op,
                                        _cimg_mp_is_constant(arg1)?"const ":"",
                                        variable_name._data,
                                        s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
          }

        for (s = ss1; s<se1; ++s)
          if (*s=='?' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '?:'");
            s1 = s + 1; while (s1<se1 && (*s1!=':' || level[s1 - expr._data]!=clevel)) ++s1;
            arg1 = compile(ss,s,depth1,0,is_single);
            _cimg_mp_check_type(arg1,1,1,0);
            if (_cimg_mp_is_constant(arg1)) {
              if ((bool)mem[arg1]) return compile(s + 1,*s1!=':'?se:s1,depth1,0,is_single);
              else return *s1!=':'?0:compile(++s1,se,depth1,0,is_single);
            }
            p2 = code._width;
            arg2 = compile(s + 1,*s1!=':'?se:s1,depth1,0,is_single);
            p3 = code._width;
            arg3 = *s1==':'?compile(++s1,se,depth1,0,is_single):
              _cimg_mp_is_vector(arg2)?vector(_cimg_mp_size(arg2),0):0;
            _cimg_mp_check_type(arg3,3,_cimg_mp_is_vector(arg2)?2:1,_cimg_mp_size(arg2));
            arg4 = _cimg_mp_size(arg2);
            if (arg4) pos = vector(arg4); else pos = scalar();
            CImg<ulongT>::vector((ulongT)mp_if,pos,arg1,arg2,arg3,
                                p3 - p2,code._width - p3,arg4).move_to(code,p2);
            _cimg_mp_return(pos);
          }

        for (s = se3, ns = se2; s>ss; --s, --ns)
          if (*s=='|' && *ns=='|' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '||'");
            arg1 = compile(ss,s,depth1,0,is_single);
            _cimg_mp_check_type(arg1,1,1,0);
            if (arg1>0 && arg1<=16) _cimg_mp_return(1);
            p2 = code._width;
            arg2 = compile(s + 2,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,1,0);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
              _cimg_mp_constant(mem[arg1] || mem[arg2]);
            if (!arg1) _cimg_mp_return(arg2);
            pos = scalar();
            CImg<ulongT>::vector((ulongT)mp_logical_or,pos,arg1,arg2,code._width - p2).
              move_to(code,p2);
            _cimg_mp_return(pos);
          }

        for (s = se3, ns = se2; s>ss; --s, --ns)
          if (*s=='&' && *ns=='&' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '&&'");
            arg1 = compile(ss,s,depth1,0,is_single);
            _cimg_mp_check_type(arg1,1,1,0);
            if (!arg1) _cimg_mp_return(0);
            p2 = code._width;
            arg2 = compile(s + 2,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,1,0);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
              _cimg_mp_constant(mem[arg1] && mem[arg2]);
            if (arg1>0 && arg1<=16) _cimg_mp_return(arg2);
            pos = scalar();
            CImg<ulongT>::vector((ulongT)mp_logical_and,pos,arg1,arg2,code._width - p2).
              move_to(code,p2);
            _cimg_mp_return(pos);
          }

        for (s = se2; s>ss; --s)
          if (*s=='|' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '|'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_bitwise_or,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) {
              if (!arg2) _cimg_mp_return(arg1);
              _cimg_mp_vector2_vs(mp_bitwise_or,arg1,arg2);
            }
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) {
              if (!arg1) _cimg_mp_return(arg2);
              _cimg_mp_vector2_sv(mp_bitwise_or,arg1,arg2);
            }
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
              _cimg_mp_constant((longT)mem[arg1] | (longT)mem[arg2]);
            if (!arg2) _cimg_mp_return(arg1);
            if (!arg1) _cimg_mp_return(arg2);
            _cimg_mp_scalar2(mp_bitwise_or,arg1,arg2);
          }

        for (s = se2; s>ss; --s)
          if (*s=='&' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '&'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_bitwise_and,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_bitwise_and,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_bitwise_and,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
              _cimg_mp_constant((longT)mem[arg1] & (longT)mem[arg2]);
            if (!arg1 || !arg2) _cimg_mp_return(0);
            _cimg_mp_scalar2(mp_bitwise_and,arg1,arg2);
          }

        for (s = se3, ns = se2; s>ss; --s, --ns)
          if (*s=='!' && *ns=='=' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '!='");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 2,se,depth1,0,is_single);
            if (arg1==arg2) _cimg_mp_return(0);
            p1 = _cimg_mp_size(arg1);
            p2 = _cimg_mp_size(arg2);
            if (p1 || p2) {
              if (p1 && p2 && p1!=p2) _cimg_mp_return(1);
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_vector_neq,pos,arg1,p1,arg2,p2,11,1).move_to(code);
              _cimg_mp_return(pos);
            }
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]!=mem[arg2]);
            _cimg_mp_scalar2(mp_neq,arg1,arg2);
          }

        for (s = se3, ns = se2; s>ss; --s, --ns)
          if (*s=='=' && *ns=='=' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '=='");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 2,se,depth1,0,is_single);
            if (arg1==arg2) _cimg_mp_return(1);
            p1 = _cimg_mp_size(arg1);
            p2 = _cimg_mp_size(arg2);
            if (p1 || p2) {
              if (p1 && p2 && p1!=p2) _cimg_mp_return(0);
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_vector_eq,pos,arg1,p1,arg2,p2,11,1).move_to(code);
              _cimg_mp_return(pos);
            }
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]==mem[arg2]);
            _cimg_mp_scalar2(mp_eq,arg1,arg2);
          }

        for (s = se3, ns = se2; s>ss; --s, --ns)
          if (*s=='<' && *ns=='=' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '<='");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 2,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_lte,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_lte,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_lte,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]<=mem[arg2]);
            if (arg1==arg2) _cimg_mp_return(1);
            _cimg_mp_scalar2(mp_lte,arg1,arg2);
          }

        for (s = se3, ns = se2; s>ss; --s, --ns)
          if (*s=='>' && *ns=='=' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '>='");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 2,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_gte,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_gte,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_gte,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]>=mem[arg2]);
            if (arg1==arg2) _cimg_mp_return(1);
            _cimg_mp_scalar2(mp_gte,arg1,arg2);
          }

        for (s = se2, ns = se1, ps = se3; s>ss; --s, --ns, --ps)
          if (*s=='<' && *ns!='<' && *ps!='<' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '<'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_lt,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_lt,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_lt,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]<mem[arg2]);
            if (arg1==arg2) _cimg_mp_return(0);
            _cimg_mp_scalar2(mp_lt,arg1,arg2);
          }

        for (s = se2, ns = se1, ps = se3; s>ss; --s, --ns, --ps)
          if (*s=='>' && *ns!='>' && *ps!='>' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '>'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_gt,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_gt,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_gt,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]>mem[arg2]);
            if (arg1==arg2) _cimg_mp_return(0);
            _cimg_mp_scalar2(mp_gt,arg1,arg2);
          }

        for (s = se3, ns = se2; s>ss; --s, --ns)
          if (*s=='<' && *ns=='<' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '<<'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 2,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2))
              _cimg_mp_vector2_vv(mp_bitwise_left_shift,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) {
              if (!arg2) _cimg_mp_return(arg1);
              _cimg_mp_vector2_vs(mp_bitwise_left_shift,arg1,arg2);
            }
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2))
              _cimg_mp_vector2_sv(mp_bitwise_left_shift,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
              _cimg_mp_constant((longT)mem[arg1]<<(unsigned int)mem[arg2]);
            if (!arg1) _cimg_mp_return(0);
            if (!arg2) _cimg_mp_return(arg1);
            _cimg_mp_scalar2(mp_bitwise_left_shift,arg1,arg2);
          }

        for (s = se3, ns = se2; s>ss; --s, --ns)
          if (*s=='>' && *ns=='>' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '>>'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 2,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2))
              _cimg_mp_vector2_vv(mp_bitwise_right_shift,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) {
              if (!arg2) _cimg_mp_return(arg1);
              _cimg_mp_vector2_vs(mp_bitwise_right_shift,arg1,arg2);
            }
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2))
              _cimg_mp_vector2_sv(mp_bitwise_right_shift,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
              _cimg_mp_constant((longT)mem[arg1]>>(unsigned int)mem[arg2]);
            if (!arg1) _cimg_mp_return(0);
            if (!arg2) _cimg_mp_return(arg1);
            _cimg_mp_scalar2(mp_bitwise_right_shift,arg1,arg2);
          }

        for (ns = se1, s = se2, ps = pexpr._data + (se3 - expr._data); s>ss; --ns, --s, --ps)
          if (*s=='+' && (*ns!='+' || ns!=se1) && *ps!='-' && *ps!='+' && *ps!='*' && *ps!='/' && *ps!='%' &&
              *ps!='&' && *ps!='|' && *ps!='^' && *ps!='!' && *ps!='~' && *ps!='#' &&
              (*ps!='e' || !(ps - pexpr._data>ss - expr._data && (*(ps - 1)=='.' || (*(ps - 1)>='0' &&
                                                                                     *(ps - 1)<='9')))) &&
              level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '+'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (!arg2) _cimg_mp_return(arg1);
            if (!arg1) _cimg_mp_return(arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_add,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_add,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_add,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1] + mem[arg2]);
            if (code) {
              CImg<ulongT> &pop = code.back();
              if (pop[0]==(ulongT)mp_mul && _cimg_mp_is_comp(pop[1]) && (pop[1]==arg1 || pop[1]==arg2)) {
                arg3 = (unsigned int)pop[1];
                arg4 = (unsigned int)pop[2];
                arg5 = (unsigned int)pop[3];
                code.remove();
                CImg<ulongT>::vector((ulongT)mp_linear_add,arg3,arg4,arg5,arg3==arg2?arg1:arg2).move_to(code);
                _cimg_mp_return(arg3);
              }
            }
            if (arg2==1) _cimg_mp_scalar1(mp_increment,arg1);
            if (arg1==1) _cimg_mp_scalar1(mp_increment,arg2);
            _cimg_mp_scalar2(mp_add,arg1,arg2);
          }

        for (ns = se1, s = se2, ps = pexpr._data + (se3 - expr._data); s>ss; --ns, --s, --ps)
          if (*s=='-' && (*ns!='-' || ns!=se1) && *ps!='-' && *ps!='+' && *ps!='*' && *ps!='/' && *ps!='%' &&
              *ps!='&' && *ps!='|' && *ps!='^' && *ps!='!' && *ps!='~' && *ps!='#' &&
              (*ps!='e' || !(ps - pexpr._data>ss - expr._data && (*(ps - 1)=='.' || (*(ps - 1)>='0' &&
                                                                                     *(ps - 1)<='9')))) &&
              level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '-'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (!arg2) _cimg_mp_return(arg1);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_sub,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_sub,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) {
              if (!arg1) _cimg_mp_vector1_v(mp_minus,arg2);
              _cimg_mp_vector2_sv(mp_sub,arg1,arg2);
            }
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1] - mem[arg2]);
            if (!arg1) _cimg_mp_scalar1(mp_minus,arg2);
            if (code) {
              CImg<ulongT> &pop = code.back();
              if (pop[0]==(ulongT)mp_mul && _cimg_mp_is_comp(pop[1]) && (pop[1]==arg1 || pop[1]==arg2)) {
                arg3 = (unsigned int)pop[1];
                arg4 = (unsigned int)pop[2];
                arg5 = (unsigned int)pop[3];
                code.remove();
                CImg<ulongT>::vector((ulongT)(arg3==arg1?mp_linear_sub_left:mp_linear_sub_right),
                                     arg3,arg4,arg5,arg3==arg1?arg2:arg1).move_to(code);
                _cimg_mp_return(arg3);
              }
            }
            if (arg2==1) _cimg_mp_scalar1(mp_decrement,arg1);
            _cimg_mp_scalar2(mp_sub,arg1,arg2);
          }

        for (s = se3, ns = se2; s>ss; --s, --ns)
          if (*s=='*' && *ns=='*' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '**'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 2,se,depth1,0,is_single);
            _cimg_mp_check_type(arg1,1,3,2);
            _cimg_mp_check_type(arg2,2,3,2);
            if (arg2==1) _cimg_mp_return(arg1);
            if (arg1==1) _cimg_mp_return(arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) {
              pos = vector(2);
              CImg<ulongT>::vector((ulongT)mp_complex_mul,pos,arg1,arg2).move_to(code);
              _cimg_mp_return(pos);
            }
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_mul,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_mul,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]*mem[arg2]);
            if (!arg1 || !arg2) _cimg_mp_return(0);
            _cimg_mp_scalar2(mp_mul,arg1,arg2);
          }

        for (s = se3, ns = se2; s>ss; --s, --ns)
          if (*s=='/' && *ns=='/' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '//'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 2,se,depth1,0,is_single);
            _cimg_mp_check_type(arg1,1,3,2);
            _cimg_mp_check_type(arg2,2,3,2);
            if (arg2==1) _cimg_mp_return(arg1);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) {
              pos = vector(2);
              CImg<ulongT>::vector((ulongT)mp_complex_div_vv,pos,arg1,arg2).move_to(code);
              _cimg_mp_return(pos);
            }
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_div,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) {
              pos = vector(2);
              CImg<ulongT>::vector((ulongT)mp_complex_div_sv,pos,arg1,arg2).move_to(code);
              _cimg_mp_return(pos);
            }
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]/mem[arg2]);
            if (!arg1) _cimg_mp_return(0);
            _cimg_mp_scalar2(mp_div,arg1,arg2);
          }

        for (s = se2; s>ss; --s) if (*s=='*' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '*'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);
            p2 = _cimg_mp_size(arg2);
            if (p2>0 && _cimg_mp_size(arg1)==p2*p2) {
              pos = vector(p2);
              CImg<ulongT>::vector((ulongT)mp_matrix_mul,pos,arg1,arg2,p2,p2,1).move_to(code);
              _cimg_mp_return(pos);
            }
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (arg2==1) _cimg_mp_return(arg1);
            if (arg1==1) _cimg_mp_return(arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_mul,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_mul,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_mul,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]*mem[arg2]);

            if (code) {
              CImg<ulongT> &pop = code.back();
              if (pop[0]==(ulongT)mp_mul && _cimg_mp_is_comp(pop[1]) && (pop[1]==arg1 || pop[1]==arg2)) {
                arg3 = (unsigned int)pop[1];
                arg4 = (unsigned int)pop[2];
                arg5 = (unsigned int)pop[3];
                code.remove();
                CImg<ulongT>::vector((ulongT)mp_mul2,arg3,arg4,arg5,arg3==arg2?arg1:arg2).move_to(code);
                _cimg_mp_return(arg3);
              }
            }
            if (!arg1 || !arg2) _cimg_mp_return(0);
            _cimg_mp_scalar2(mp_mul,arg1,arg2);
          }

        for (s = se2; s>ss; --s) if (*s=='/' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '/'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (arg2==1) _cimg_mp_return(arg1);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_div,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_div,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_div,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2)) _cimg_mp_constant(mem[arg1]/mem[arg2]);
            if (!arg1) _cimg_mp_return(0);
            _cimg_mp_scalar2(mp_div,arg1,arg2);
          }

        for (s = se2, ns = se1; s>ss; --s, --ns)
          if (*s=='%' && *ns!='^' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '%'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_modulo,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_modulo,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_modulo,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
              _cimg_mp_constant(cimg::mod(mem[arg1],mem[arg2]));
            _cimg_mp_scalar2(mp_modulo,arg1,arg2);
          }

        if (se1>ss) {
          if (*ss=='+' && (*ss1!='+' || (ss2<se && *ss2>='0' && *ss2<='9'))) {
            _cimg_mp_op("Operator '+'");
            _cimg_mp_return(compile(ss1,se,depth1,0,is_single));
          }

          if (*ss=='-' && (*ss1!='-' || (ss2<se && *ss2>='0' && *ss2<='9'))) {
            _cimg_mp_op("Operator '-'");
            arg1 = compile(ss1,se,depth1,0,is_single);
            if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_minus,arg1);
            if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(-mem[arg1]);
            _cimg_mp_scalar1(mp_minus,arg1);
          }

          if (*ss=='!') {
            _cimg_mp_op("Operator '!'");
            if (*ss1=='!') {
              arg1 = compile(ss2,se,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_bool,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant((bool)mem[arg1]);
              _cimg_mp_scalar1(mp_bool,arg1);
            }
            arg1 = compile(ss1,se,depth1,0,is_single);
            if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_logical_not,arg1);
            if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(!mem[arg1]);
            _cimg_mp_scalar1(mp_logical_not,arg1);
          }

          if (*ss=='~') {
            _cimg_mp_op("Operator '~'");
            arg1 = compile(ss1,se,depth1,0,is_single);
            if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_bitwise_not,arg1);
            if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(~(unsigned int)mem[arg1]);
            _cimg_mp_scalar1(mp_bitwise_not,arg1);
          }
        }

        for (s = se3, ns = se2; s>ss; --s, --ns)
          if (*s=='^' && *ns=='^' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '^^'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 2,se,depth1,0,is_single);
            _cimg_mp_check_type(arg1,1,3,2);
            _cimg_mp_check_type(arg2,2,3,2);
            if (arg2==1) _cimg_mp_return(arg1);
            pos = vector(2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) {
              CImg<ulongT>::vector((ulongT)mp_complex_pow_vv,pos,arg1,arg2).move_to(code);
              _cimg_mp_return(pos);
            }
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) {
              CImg<ulongT>::vector((ulongT)mp_complex_pow_vs,pos,arg1,arg2).move_to(code);
              _cimg_mp_return(pos);
            }
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) {
              CImg<ulongT>::vector((ulongT)mp_complex_pow_sv,pos,arg1,arg2).move_to(code);
              _cimg_mp_return(pos);
            }
            CImg<ulongT>::vector((ulongT)mp_complex_pow_ss,pos,arg1,arg2).move_to(code);
            _cimg_mp_return(pos);
          }

        for (s = se2; s>ss; --s)
          if (*s=='^' && level[s - expr._data]==clevel) {
            _cimg_mp_op("Operator '^'");
            arg1 = compile(ss,s,depth1,0,is_single);
            arg2 = compile(s + 1,se,depth1,0,is_single);
            _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
            if (arg2==1) _cimg_mp_return(arg1);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_pow,arg1,arg2);
            if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_pow,arg1,arg2);
            if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_pow,arg1,arg2);
            if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
              _cimg_mp_constant(std::pow(mem[arg1],mem[arg2]));
            switch (arg2) {
            case 0 : _cimg_mp_return(1);
            case 2 : _cimg_mp_scalar1(mp_sqr,arg1);
            case 3 : _cimg_mp_scalar1(mp_pow3,arg1);
            case 4 : _cimg_mp_scalar1(mp_pow4,arg1);
            default :
              if (_cimg_mp_is_constant(arg2)) {
                if (mem[arg2]==0.5) { _cimg_mp_scalar1(mp_sqrt,arg1); }
                else if (mem[arg2]==0.25) { _cimg_mp_scalar1(mp_pow0_25,arg1); }
              }
              _cimg_mp_scalar2(mp_pow,arg1,arg2);
            }
          }


        if (*se1=='%') {
          arg1 = compile(ss,se1,depth1,0,is_single);
          arg2 = _cimg_mp_is_constant(arg1)?0:constant(100);
          if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector2_vs(mp_div,arg1,arg2);
          if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(mem[arg1]/100);
          _cimg_mp_scalar2(mp_div,arg1,arg2);
        }

        is_sth = ss1<se1 && (*ss=='+' || *ss=='-') && *ss1==*ss;
        if (is_sth || (se2>ss && (*se1=='+' || *se1=='-') && *se2==*se1)) {
          if ((is_sth && *ss=='+') || (!is_sth && *se1=='+')) {
            _cimg_mp_op("Operator '++'");
            op = mp_self_increment;
          } else {
            _cimg_mp_op("Operator '--'");
            op = mp_self_decrement;
          }
          ref.assign(7);
          arg1 = is_sth?compile(ss2,se,depth1,ref,is_single):
            compile(ss,se2,depth1,ref,is_single);


          if (*ref && (_cimg_mp_is_constant(arg1) || _cimg_mp_is_vector(arg1) || _cimg_mp_is_variable(arg1))) {
            if (_cimg_mp_is_vector(arg1)) arg1 = vector_copy(arg1);
            else arg1 = scalar1(mp_copy,arg1);
          }

          if (is_sth) pos = arg1;
          else {
            if (_cimg_mp_is_vector(arg1)) pos = vector_copy(arg1);
            else pos = scalar1(mp_copy,arg1);
          }

          if (*ref==1) {
            arg3 = ref[1];
            arg4 = ref[2];
            if (is_sth && p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
            CImg<ulongT>::vector((ulongT)op,arg1,1).move_to(code);
            CImg<ulongT>::vector((ulongT)mp_vector_set_off,arg1,arg3,(ulongT)_cimg_mp_size(arg3),arg4,arg1).
              move_to(code);
            _cimg_mp_return(pos);
          }

          if (*ref==2) {
            if (!is_single) is_parallelizable = false;
            p1 = ref[1];
            is_relative = (bool)ref[2];
            arg3 = ref[3];
            if (is_sth && p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
            CImg<ulongT>::vector((ulongT)op,arg1).move_to(code);
            if (p1!=~0U) {
              if (!listout) _cimg_mp_return(pos);
              CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_joff:mp_list_set_ioff),
                                  arg1,p1,arg3).move_to(code);
            } else {
              if (!imgout) _cimg_mp_return(pos);
              CImg<ulongT>::vector((ulongT)(is_relative?mp_set_joff:mp_set_ioff),
                                  arg1,arg3).move_to(code);
            }
            _cimg_mp_return(pos);
          }

          if (*ref==3) {
            if (!is_single) is_parallelizable = false;
            p1 = ref[1];
            is_relative = (bool)ref[2];
            arg3 = ref[3];
            arg4 = ref[4];
            arg5 = ref[5];
            arg6 = ref[6];
            if (is_sth && p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
            CImg<ulongT>::vector((ulongT)op,arg1).move_to(code);
            if (p1!=~0U) {
              if (!listout) _cimg_mp_return(pos);
              CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_jxyzc:mp_list_set_ixyzc),
                                  arg1,p1,arg3,arg4,arg5,arg6).move_to(code);
            } else {
              if (!imgout) _cimg_mp_return(pos);
              CImg<ulongT>::vector((ulongT)(is_relative?mp_set_jxyzc:mp_set_ixyzc),
                                  arg1,arg3,arg4,arg5,arg6).move_to(code);
            }
            _cimg_mp_return(pos);
          }

          if (*ref==4) {
            if (!is_single) is_parallelizable = false;
            p1 = ref[1];
            is_relative = (bool)ref[2];
            arg3 = ref[3];
            if (is_sth && p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
            self_vector_s(arg1,op==mp_self_increment?mp_self_add:mp_self_sub,1);
            if (p1!=~0U) {
              if (!listout) _cimg_mp_return(pos);
              CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Joff_v:mp_list_set_Ioff_v),
                                  arg1,p1,arg3,_cimg_mp_size(arg1)).move_to(code);
            } else {
              if (!imgout) _cimg_mp_return(pos);
              CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Joff_v:mp_set_Ioff_v),
                                  arg1,arg3,_cimg_mp_size(arg1)).move_to(code);
            }
            _cimg_mp_return(pos);
          }

          if (*ref==5) {
            if (!is_single) is_parallelizable = false;
            p1 = ref[1];
            is_relative = (bool)ref[2];
            arg3 = ref[3];
            arg4 = ref[4];
            arg5 = ref[5];
            if (is_sth && p_ref) std::memcpy(p_ref,ref,ref._width*sizeof(unsigned int));
            self_vector_s(arg1,op==mp_self_increment?mp_self_add:mp_self_sub,1);
            if (p1!=~0U) {
              if (!listout) _cimg_mp_return(pos);
              CImg<ulongT>::vector((ulongT)(is_relative?mp_list_set_Jxyz_v:mp_list_set_Ixyz_v),
                                  arg1,p1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
            } else {
              if (!imgout) _cimg_mp_return(pos);
              CImg<ulongT>::vector((ulongT)(is_relative?mp_set_Jxyz_v:mp_set_Ixyz_v),
                                  arg1,arg3,arg4,arg5,_cimg_mp_size(arg1)).move_to(code);
            }
            _cimg_mp_return(pos);
          }

          if (_cimg_mp_is_vector(arg1)) {
            self_vector_s(arg1,op==mp_self_increment?mp_self_add:mp_self_sub,1);
            _cimg_mp_return(pos);
          }

          if (_cimg_mp_is_variable(arg1)) {
            CImg<ulongT>::vector((ulongT)op,arg1).move_to(code);
            _cimg_mp_return(pos);
          }

          if (is_sth) variable_name.assign(ss2,(unsigned int)(se - ss1));
          else variable_name.assign(ss,(unsigned int)(se1 - ss));
          variable_name.back() = 0;
          cimg::strpare(variable_name,false,true);
          *se = saved_char;
          cimg::strellipsize(variable_name,64);
          s0 = ss - 4>expr._data?ss - 4:expr._data;
          cimg::strellipsize(s0,64);
          throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                      "CImg<%s>::%s: %s: Invalid %slvalue '%s', "
                                      "in expression '%s%s%s'.",
                                      pixel_type(),_cimg_mp_calling_function,s_op,
                                      _cimg_mp_is_constant(arg1)?"const ":"",
                                      variable_name._data,
                                      s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
        }


        if (*se1==']' && *ss!='[') {
          _cimg_mp_op("Value accessor '[]'");
          is_relative = *ss=='j' || *ss=='J';
          s0 = s1 = std::strchr(ss,'['); if (s0) { do { --s1; } while (cimg::is_blank(*s1)); cimg::swap(*s0,*++s1); }

          if ((*ss=='I' || *ss=='J') && *ss1=='[' &&
              (reserved_label[(int)*ss]==~0U ||
               !_cimg_mp_is_vector(reserved_label[(int)*ss]))) {
            if (*ss2=='#') {
              s0 = ss3; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
              p1 = compile(ss3,s0++,depth1,0,is_single);
              _cimg_mp_check_list(false);
            } else { p1 = ~0U; s0 = ss2; }
            s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
            p2 = 1 + (p1!=~0U);
            arg1 = compile(s0,s1,depth1,0,is_single);
            _cimg_mp_check_type(arg1,p2,1,0);
            arg2 = ~0U;
            if (s1<se1) {
              arg2 = compile(++s1,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg2,p2 + 1,1,0);
            }
            if (p_ref && arg2==~0U) {
              *p_ref = 4;
              p_ref[1] = p1;
              p_ref[2] = (unsigned int)is_relative;
              p_ref[3] = arg1;
              if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2;
              if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
            }
            p2 = ~0U;
            if (p1==~0U) p2 = imgin._spectrum;
            else if (_cimg_mp_is_constant(p1)) {
              p3 = (unsigned int)cimg::mod((int)mem[p1],listin.width());
              p2 = listin[p3]._spectrum;
            }
            if (!p2) _cimg_mp_return(0);
            pos = vector(p2);
            if (p1!=~0U) {
              CImg<ulongT>::vector((ulongT)(is_relative?mp_list_Joff:mp_list_Ioff),
                                  pos,p1,arg1,arg2==~0U?_cimg_mp_boundary:arg2,p2).move_to(code);
            } else {
              need_input_copy = true;
              CImg<ulongT>::vector((ulongT)(is_relative?mp_Joff:mp_Ioff),
                                  pos,arg1,arg2==~0U?_cimg_mp_boundary:arg2,p2).move_to(code);
            }
            _cimg_mp_return(pos);
          }

          if ((*ss=='i' || *ss=='j') && *ss1=='[' &&
              (reserved_label[(int)*ss]==~0U ||
               !_cimg_mp_is_vector(reserved_label[(int)*ss]))) {
            if (*ss2=='#') {
              s0 = ss3; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
              p1 = compile(ss3,s0++,depth1,0,is_single);
            } else { p1 = ~0U; s0 = ss2; }
            s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
            arg1 = compile(s0,s1,depth1,0,is_single);
            arg2 = s1<se1?compile(++s1,se1,depth1,0,is_single):~0U;
            if (p_ref && arg2==~0U) {
              *p_ref = 2;
              p_ref[1] = p1;
              p_ref[2] = (unsigned int)is_relative;
              p_ref[3] = arg1;
              if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2;
              if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
            }
            if (p1!=~0U) {
              if (!listin) _cimg_mp_return(0);
              pos = scalar3(is_relative?mp_list_joff:mp_list_ioff,p1,arg1,arg2==~0U?_cimg_mp_boundary:arg2);
            } else {
              if (!imgin) _cimg_mp_return(0);
              need_input_copy = true;
              pos = scalar2(is_relative?mp_joff:mp_ioff,arg1,arg2==~0U?_cimg_mp_boundary:arg2);
            }
            memtype[pos] = -2;
            _cimg_mp_return(pos);
          }

          s0 = se1; while (s0>ss && (*s0!='[' || level[s0 - expr._data]!=clevel)) --s0;
          if (s0>ss) {
            arg1 = compile(ss,s0,depth1,0,is_single);
            if (_cimg_mp_is_scalar(arg1)) {
              variable_name.assign(ss,(unsigned int)(s0 - ss + 1)).back() = 0;
              *se = saved_char;
              cimg::strellipsize(variable_name,64);
              s0 = ss - 4>expr._data?ss - 4:expr._data;
              cimg::strellipsize(s0,64);
              throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                          "CImg<%s>::%s: %s: Array brackets used on non-vector variable '%s', "
                                          "in expression '%s%s%s'.",
                                          pixel_type(),_cimg_mp_calling_function,s_op,
                                          variable_name._data,
                                          s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");

            }
            s1 = s0 + 1; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;

            if (s1<se1) {
              p1 = _cimg_mp_size(arg1);
              arg2 = compile(++s0,s1,depth1,0,is_single);
              s0 = ++s1; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
              arg3 = compile(s1,s0,depth1,0,is_single);
              arg4 = s0<se1?compile(++s0,se1,depth1,0,is_single):1;
              _cimg_mp_check_constant(arg3,2,3);
              arg3 = (unsigned int)mem[arg3];
              pos = vector(arg3);
              CImg<ulongT>::vector((ulongT)mp_vector_crop,pos,arg1,p1,arg2,arg3,arg4).move_to(code);
              _cimg_mp_return(pos);
            }


            arg2 = compile(++s0,se1,depth1,0,is_single);
            if (_cimg_mp_is_constant(arg2)) {
              nb = (int)mem[arg2];
              if (nb>=0 && nb<(int)_cimg_mp_size(arg1)) _cimg_mp_return(arg1 + 1 + nb);
              variable_name.assign(ss,(unsigned int)(s0 - ss)).back() = 0;
              *se = saved_char;
              cimg::strellipsize(variable_name,64);
              s0 = ss - 4>expr._data?ss - 4:expr._data;
              cimg::strellipsize(s0,64);
              throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                          "CImg<%s>::%s: Out-of-bounds reference '%s[%d]' "
                                          "(vector '%s' has dimension %u), "
                                          "in expression '%s%s%s'.",
                                          pixel_type(),_cimg_mp_calling_function,
                                          variable_name._data,nb,
                                          variable_name._data,_cimg_mp_size(arg1),
                                          s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
            }
            if (p_ref) {
              *p_ref = 1;
              p_ref[1] = arg1;
              p_ref[2] = arg2;
              if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2;
            }
            pos = scalar3(mp_vector_off,arg1,_cimg_mp_size(arg1),arg2);
            memtype[pos] = -2;
            _cimg_mp_return(pos);
          }
        }


        if (*se1==')') {
          if (*ss=='(') _cimg_mp_return(compile(ss1,se1,depth1,p_ref,is_single));
          _cimg_mp_op("Value accessor '()'");
          is_relative = *ss=='j' || *ss=='J';
          s0 = s1 = std::strchr(ss,'('); if (s0) { do { --s1; } while (cimg::is_blank(*s1)); cimg::swap(*s0,*++s1); }


          if ((*ss=='I' || *ss=='J') && *ss1=='(') {
            if (*ss2=='#') {
              s0 = ss3; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
              p1 = compile(ss3,s0++,depth1,0,is_single);
              _cimg_mp_check_list(false);
            } else { p1 = ~0U; s0 = ss2; }
            arg1 = is_relative?0U:(unsigned int)_cimg_mp_slot_x;
            arg2 = is_relative?0U:(unsigned int)_cimg_mp_slot_y;
            arg3 = is_relative?0U:(unsigned int)_cimg_mp_slot_z;
            arg4 = arg5 = ~0U;
            if (s0<se1) {
              s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(s0,s1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) {
                p2 = _cimg_mp_size(arg1);
                ++arg1;
                if (p2>1) {
                  arg2 = arg1 + 1;
                  if (p2>2) arg3 = arg2 + 1;
                }
                if (s1<se1) {
                  s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                  arg4 = compile(s1,s2,depth1,0,is_single);
                  arg5 = s2<se1?compile(++s2,se1,depth1,0,is_single):~0U;
                }
              } else if (s1<se1) {
                s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                arg2 = compile(s1,s2,depth1,0,is_single);
                if (s2<se1) {
                  s3 = ++s2; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
                  arg3 = compile(s2,s3,depth1,0,is_single);
                  if (s3<se1) {
                    s2 = ++s3; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                    arg4 = compile(s3,s2,depth1,0,is_single);
                    arg5 = s2<se1?compile(++s2,se1,depth1,0,is_single):~0U;
                  }
                }
              }
            }
            if (p_ref && arg4==~0U && arg5==~0U) {
              *p_ref = 5;
              p_ref[1] = p1;
              p_ref[2] = (unsigned int)is_relative;
              p_ref[3] = arg1;
              p_ref[4] = arg2;
              p_ref[5] = arg3;
              if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2;
              if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
              if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2;
              if (_cimg_mp_is_comp(arg3)) memtype[arg3] = -2;
            }
            p2 = ~0U;
            if (p1==~0U) p2 = imgin._spectrum;
            else if (_cimg_mp_is_constant(p1)) {
              p3 = (unsigned int)cimg::mod((int)mem[p1],listin.width());
              p2 = listin[p3]._spectrum;
            }
            if (!p2) _cimg_mp_return(0);
            pos = vector(p2);
            if (p1!=~0U)
              CImg<ulongT>::vector((ulongT)(is_relative?mp_list_Jxyz:mp_list_Ixyz),
                                   pos,p1,arg1,arg2,arg3,
                                   arg4==~0U?_cimg_mp_interpolation:arg4,
                                   arg5==~0U?_cimg_mp_boundary:arg5,p2).move_to(code);
            else {
              need_input_copy = true;
              CImg<ulongT>::vector((ulongT)(is_relative?mp_Jxyz:mp_Ixyz),
                                  pos,arg1,arg2,arg3,
                                  arg4==~0U?_cimg_mp_interpolation:arg4,
                                  arg5==~0U?_cimg_mp_boundary:arg5,p2).move_to(code);
            }
            _cimg_mp_return(pos);
          }


          if ((*ss=='i' || *ss=='j') && *ss1=='(') {
            if (*ss2=='#') {
              s0 = ss3; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
              p1 = compile(ss3,s0++,depth1,0,is_single);
            } else { p1 = ~0U; s0 = ss2; }
            arg1 = is_relative?0U:(unsigned int)_cimg_mp_slot_x;
            arg2 = is_relative?0U:(unsigned int)_cimg_mp_slot_y;
            arg3 = is_relative?0U:(unsigned int)_cimg_mp_slot_z;
            arg4 = is_relative?0U:(unsigned int)_cimg_mp_slot_c;
            arg5 = arg6 = ~0U;
            if (s0<se1) {
              s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(s0,s1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) {
                p2 = _cimg_mp_size(arg1);
                ++arg1;
                if (p2>1) {
                  arg2 = arg1 + 1;
                  if (p2>2) {
                    arg3 = arg2 + 1;
                    if (p2>3) arg4 = arg3 + 1;
                  }
                }
                if (s1<se1) {
                  s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                  arg5 = compile(s1,s2,depth1,0,is_single);
                  arg6 = s2<se1?compile(++s2,se1,depth1,0,is_single):~0U;
                }
              } else if (s1<se1) {
                s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                arg2 = compile(s1,s2,depth1,0,is_single);
                if (s2<se1) {
                  s3 = ++s2; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
                  arg3 = compile(s2,s3,depth1,0,is_single);
                  if (s3<se1) {
                    s2 = ++s3; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                    arg4 = compile(s3,s2,depth1,0,is_single);
                    if (s2<se1) {
                      s3 = ++s2; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
                      arg5 = compile(s2,s3,depth1,0,is_single);
                      arg6 = s3<se1?compile(++s3,se1,depth1,0,is_single):~0U;
                    }
                  }
                }
              }
            }
            if (p_ref && arg5==~0U && arg6==~0U) {
              *p_ref = 3;
              p_ref[1] = p1;
              p_ref[2] = (unsigned int)is_relative;
              p_ref[3] = arg1;
              p_ref[4] = arg2;
              p_ref[5] = arg3;
              p_ref[6] = arg4;
              if (p1!=~0U && _cimg_mp_is_comp(p1)) memtype[p1] = -2;
              if (_cimg_mp_is_comp(arg1)) memtype[arg1] = -2;
              if (_cimg_mp_is_comp(arg2)) memtype[arg2] = -2;
              if (_cimg_mp_is_comp(arg3)) memtype[arg3] = -2;
              if (_cimg_mp_is_comp(arg4)) memtype[arg4] = -2;
            }

            if (p1!=~0U) {
              if (!listin) _cimg_mp_return(0);
              pos = scalar7(is_relative?mp_list_jxyzc:mp_list_ixyzc,
                            p1,arg1,arg2,arg3,arg4,
                            arg5==~0U?_cimg_mp_interpolation:arg5,
                            arg6==~0U?_cimg_mp_boundary:arg6);
            } else {
              if (!imgin) _cimg_mp_return(0);
              need_input_copy = true;
              pos = scalar6(is_relative?mp_jxyzc:mp_ixyzc,
                            arg1,arg2,arg3,arg4,
                            arg5==~0U?_cimg_mp_interpolation:arg5,
                            arg6==~0U?_cimg_mp_boundary:arg6);
            }
            memtype[pos] = -2;
            _cimg_mp_return(pos);
          }


          switch (*ss) {

          case '_' :
            if (*ss1=='(')
              _cimg_mp_return_nan();
            break;

          case 'a' :
            if (!std::strncmp(ss,"abs(",4)) {
              _cimg_mp_op("Function 'abs()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_abs,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::abs(mem[arg1]));
              _cimg_mp_scalar1(mp_abs,arg1);
            }

            if (!std::strncmp(ss,"acos(",5)) {
              _cimg_mp_op("Function 'acos()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_acos,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::acos(mem[arg1]));
              _cimg_mp_scalar1(mp_acos,arg1);
            }

            if (!std::strncmp(ss,"acosh(",6)) {
              _cimg_mp_op("Function 'acosh()'");
              arg1 = compile(ss6,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_acosh,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::acosh(mem[arg1]));
              _cimg_mp_scalar1(mp_acosh,arg1);
            }

            if (!std::strncmp(ss,"asinh(",6)) {
              _cimg_mp_op("Function 'asinh()'");
              arg1 = compile(ss6,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_asinh,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::asinh(mem[arg1]));
              _cimg_mp_scalar1(mp_asinh,arg1);
            }

            if (!std::strncmp(ss,"atanh(",6)) {
              _cimg_mp_op("Function 'atanh()'");
              arg1 = compile(ss6,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_atanh,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::atanh(mem[arg1]));
              _cimg_mp_scalar1(mp_atanh,arg1);
            }

            if (!std::strncmp(ss,"arg(",4)) {
              _cimg_mp_op("Function 'arg()'");
              s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss4,s1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,1,1,0);
              s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
              arg2 = compile(s1,s2,depth1,0,is_single);
              p2 = _cimg_mp_size(arg2);
              p3 = 3;
              CImg<ulongT>::vector((ulongT)mp_arg,0,0,p2,arg1,arg2).move_to(l_opcode);
              for (s = ++s2; s<se; ++s) {
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                arg3 = compile(s,ns,depth1,0,is_single);
                _cimg_mp_check_type(arg3,p3,p2?2:1,p2);
                CImg<ulongT>::vector(arg3).move_to(l_opcode);
                ++p3;
                s = ns;
              }
              (l_opcode>'y').move_to(opcode);
              opcode[2] = opcode._height;
              if (_cimg_mp_is_constant(arg1)) {
                p3-=1;
                arg1 = (unsigned int)(mem[arg1]<0?mem[arg1] + p3:mem[arg1]);
                if (arg1<p3) _cimg_mp_return(opcode[4 + arg1]);
                if (p2) {
                  pos = vector(p2);
                  std::memset(&mem[pos] + 1,0,p2*sizeof(double));
                  _cimg_mp_return(pos);
                } else _cimg_mp_return(0);
              }
              pos = opcode[1] = p2?vector(p2):scalar();
              opcode.move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"asin(",5)) {
              _cimg_mp_op("Function 'asin()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_asin,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::asin(mem[arg1]));
              _cimg_mp_scalar1(mp_asin,arg1);
            }

            if (!std::strncmp(ss,"atan(",5)) {
              _cimg_mp_op("Function 'atan()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_atan,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::atan(mem[arg1]));
              _cimg_mp_scalar1(mp_atan,arg1);
            }

            if (!std::strncmp(ss,"atan2(",6)) {
              _cimg_mp_op("Function 'atan2()'");
              s1 = ss6; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss6,s1,depth1,0,is_single);
              arg2 = compile(++s1,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
              if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_atan2,arg1,arg2);
              if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_atan2,arg1,arg2);
              if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_atan2,arg1,arg2);
              if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
                _cimg_mp_constant(std::atan2(mem[arg1],mem[arg2]));
              _cimg_mp_scalar2(mp_atan2,arg1,arg2);
            }
            break;

          case 'b' :
            if (!std::strncmp(ss,"break(",6)) {
              if (pexpr[se2 - expr._data]=='(') {
                CImg<ulongT>::vector((ulongT)mp_break,_cimg_mp_slot_nan).move_to(code);
                _cimg_mp_return_nan();
              }
            }

            if (!std::strncmp(ss,"breakpoint(",11)) {
              _cimg_mp_op("Function 'breakpoint()'");
              if (pexpr[se2 - expr._data]=='(') {
                CImg<ulongT>::vector((ulongT)mp_breakpoint,_cimg_mp_slot_nan).move_to(code);
                _cimg_mp_return_nan();
              }
            }

            if (!std::strncmp(ss,"bool(",5)) {
              _cimg_mp_op("Function 'bool()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_bool,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant((bool)mem[arg1]);
              _cimg_mp_scalar1(mp_bool,arg1);
            }

            if (!std::strncmp(ss,"begin(",6)) {
              _cimg_mp_op("Function 'begin()'");
              code.swap(code_begin);
              arg1 = compile(ss6,se1,depth1,p_ref,true);
              code.swap(code_begin);
              _cimg_mp_return(arg1);
            }
            break;

          case 'c' :
            if (!std::strncmp(ss,"cabs(",5)) {
              _cimg_mp_op("Function 'cabs()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,0,2,2);
              _cimg_mp_scalar2(mp_complex_abs,arg1 + 1,arg1 + 2);
            }

            if (!std::strncmp(ss,"carg(",5)) {
              _cimg_mp_op("Function 'carg()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,0,2,2);
              _cimg_mp_scalar2(mp_atan2,arg1 + 2,arg1 + 1);
            }

            if (!std::strncmp(ss,"cats(",5)) {
              _cimg_mp_op("Function 'cats()'");
              CImg<ulongT>::vector((ulongT)mp_cats,0,0,0).move_to(l_opcode);
              arg1 = 0;
              for (s = ss5; s<se; ++s) {
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                arg1 = compile(s,ns,depth1,0,is_single);
                CImg<ulongT>::vector(arg1,_cimg_mp_size(arg1)).move_to(l_opcode);
                s = ns;
              }
              _cimg_mp_check_constant(arg1,1,3);
              l_opcode.remove();
              (l_opcode>'y').move_to(opcode);
              p1 = (unsigned int)mem[arg1];
              pos = vector(p1);
              opcode[1] = pos;
              opcode[2] = p1;
              opcode[3] = opcode._height;
              opcode.move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"cbrt(",5)) {
              _cimg_mp_op("Function 'cbrt()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_cbrt,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::cbrt(mem[arg1]));
              _cimg_mp_scalar1(mp_cbrt,arg1);
            }

            if (!std::strncmp(ss,"cconj(",6)) {
              _cimg_mp_op("Function 'cconj()'");
              arg1 = compile(ss6,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,0,2,2);
              pos = vector(2);
              CImg<ulongT>::vector((ulongT)mp_complex_conj,pos,arg1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"ceil(",5)) {
              _cimg_mp_op("Function 'ceil()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_ceil,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::ceil(mem[arg1]));
              _cimg_mp_scalar1(mp_ceil,arg1);
            }

            if (!std::strncmp(ss,"cexp(",5)) {
              _cimg_mp_op("Function 'cexp()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,0,2,2);
              pos = vector(2);
              CImg<ulongT>::vector((ulongT)mp_complex_exp,pos,arg1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"clog(",5)) {
              _cimg_mp_op("Function 'clog()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,0,2,2);
              pos = vector(2);
              CImg<ulongT>::vector((ulongT)mp_complex_log,pos,arg1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"continue(",9)) {
              if (pexpr[se2 - expr._data]=='(') {
                CImg<ulongT>::vector((ulongT)mp_continue,_cimg_mp_slot_nan).move_to(code);
                _cimg_mp_return_nan();
              }
            }

            if (!std::strncmp(ss,"copy(",5)) {
              _cimg_mp_op("Function 'copy()'");
              ref.assign(14);
              s1 = ss5; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = p1 = compile(ss5,s1,depth1,ref,is_single);
              s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
              arg2 = compile(s1,s2,depth1,ref._data + 7,is_single);
              arg3 = arg4 = arg5 = ~0U; arg6 = 1;
              if (s2<se1) {
                s3 = ++s2; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
                arg3 = compile(s2,s3,depth1,0,is_single);
                if (s3<se1) {
                  s1 = ++s3; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                  arg4 = compile(s3,s1,depth1,0,is_single);
                  if (s1<se1) {
                    s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                    arg5 = compile(s1,s2,depth1,0,is_single);
                    arg6 = s2<se1?compile(++s2,se1,depth1,0,is_single):1;
                  }
                }
              }
              if (_cimg_mp_is_vector(arg1)) {
                if (!ref[0]) ++arg1;
                else if (ref[0]>=4 && arg4==~0U) arg4 = scalar1(mp_image_whd,ref[1]);
              }
              if (_cimg_mp_is_vector(arg2)) {
                if (arg3==~0U) arg3 = constant(_cimg_mp_size(arg2));
                if (!ref[7]) ++arg2;
                if (ref[7]>=4 && arg5==~0U) arg5 = scalar1(mp_image_whd,ref[8]);
              }
              if (arg3==~0U) arg3 = 1;
              if (arg4==~0U) arg4 = 1;
              if (arg5==~0U) arg5 = 1;
              _cimg_mp_check_type(arg3,3,1,0);
              _cimg_mp_check_type(arg4,4,1,0);
              _cimg_mp_check_type(arg5,5,1,0);
              _cimg_mp_check_type(arg6,5,1,0);
              CImg<ulongT>(1,22).move_to(code);
              code.back().get_shared_rows(0,7).fill((ulongT)mp_memcopy,p1,arg1,arg2,arg3,arg4,arg5,arg6);
              code.back().get_shared_rows(8,21).fill(ref);
              _cimg_mp_return(p1);
            }

            if (!std::strncmp(ss,"cos(",4)) {
              _cimg_mp_op("Function 'cos()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_cos,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::cos(mem[arg1]));
              _cimg_mp_scalar1(mp_cos,arg1);
            }

            if (!std::strncmp(ss,"cosh(",5)) {
              _cimg_mp_op("Function 'cosh()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_cosh,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::cosh(mem[arg1]));
              _cimg_mp_scalar1(mp_cosh,arg1);
            }

            if (!std::strncmp(ss,"critical(",9)) {
              _cimg_mp_op("Function 'critical()'");
              p1 = code._width;
              arg1 = compile(ss + 9,se1,depth1,p_ref,true);
              CImg<ulongT>::vector((ulongT)mp_critical,arg1,code._width - p1).move_to(code,p1);
              _cimg_mp_return(arg1);
            }

            if (!std::strncmp(ss,"crop(",5)) {
              _cimg_mp_op("Function 'crop()'");
              if (*ss5=='#') {
                s0 = ss6; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                p1 = compile(ss6,s0++,depth1,0,is_single);
                _cimg_mp_check_list(false);
              } else { p1 = ~0U; s0 = ss5; need_input_copy = true; }
              pos = 0;
              is_sth = false;
              if (s0<se1) for (s = s0; s<se; ++s, ++pos) {
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                arg1 = compile(s,ns,depth1,0,is_single);
                if (!pos && _cimg_mp_is_vector(arg1)) {
                  opcode = CImg<ulongT>::sequence(_cimg_mp_size(arg1),arg1 + 1,
                                                  arg1 + (ulongT)_cimg_mp_size(arg1));
                  opcode.resize(1,std::min(opcode._height,4U),1,1,0).move_to(l_opcode);
                  is_sth = true;
                } else {
                  _cimg_mp_check_type(arg1,pos + 1,1,0);
                  CImg<ulongT>::vector(arg1).move_to(l_opcode);
                }
                s = ns;
              }
              (l_opcode>'y').move_to(opcode);

              arg1 = 0; arg2 = (p1!=~0U);
              switch (opcode._height) {
              case 0 : case 1 :
                CImg<ulongT>::vector(0,0,0,0,~0U,~0U,~0U,~0U,0).move_to(opcode);
                break;
              case 2 :
                CImg<ulongT>::vector(*opcode,0,0,0,opcode[1],~0U,~0U,~0U,_cimg_mp_boundary).move_to(opcode);
                arg1 = arg2 + 2;
                break;
              case 3 :
                CImg<ulongT>::vector(*opcode,0,0,0,opcode[1],~0U,~0U,~0U,opcode[2]).move_to(opcode);
                arg1 = arg2 + 2;
                break;
              case 4 :
                CImg<ulongT>::vector(*opcode,opcode[1],0,0,opcode[2],opcode[3],~0U,~0U,_cimg_mp_boundary).
                  move_to(opcode);
                arg1 = arg2 + (is_sth?2:3);
                break;
              case 5 :
                CImg<ulongT>::vector(*opcode,opcode[1],0,0,opcode[2],opcode[3],~0U,~0U,opcode[4]).
                  move_to(opcode);
                arg1 = arg2 + (is_sth?2:3);
                break;
              case 6 :
                CImg<ulongT>::vector(*opcode,opcode[1],opcode[2],0,opcode[3],opcode[4],opcode[5],~0U,
                                    _cimg_mp_boundary).move_to(opcode);
                arg1 = arg2 + (is_sth?2:4);
                break;
              case 7 :
                CImg<ulongT>::vector(*opcode,opcode[1],opcode[2],0,opcode[3],opcode[4],opcode[5],~0U,
                                    opcode[6]).move_to(opcode);
                arg1 = arg2 + (is_sth?2:4);
                break;
              case 8 :
                CImg<ulongT>::vector(*opcode,opcode[1],opcode[2],opcode[3],opcode[4],opcode[5],opcode[6],
                                    opcode[7],_cimg_mp_boundary).move_to(opcode);
                arg1 = arg2 + (is_sth?2:5);
                break;
              case 9 :
                arg1 = arg2 + (is_sth?2:5);
                break;
              default :
                *se = saved_char;
                s0 = ss - 4>expr._data?ss - 4:expr._data;
                cimg::strellipsize(s0,64);
                throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                            "CImg<%s>::%s: %s: Too much arguments specified, "
                                            "in expression '%s%s%s'.",
                                            pixel_type(),_cimg_mp_calling_function,s_op,
                                            s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
              }

              _cimg_mp_check_type((unsigned int)*opcode,arg2 + 1,1,0);
              _cimg_mp_check_type((unsigned int)opcode[1],arg2 + 1 + (is_sth?0:1),1,0);
              _cimg_mp_check_type((unsigned int)opcode[2],arg2 + 1 + (is_sth?0:2),1,0);
              _cimg_mp_check_type((unsigned int)opcode[3],arg2 + 1 + (is_sth?0:3),1,0);
              if (opcode[4]!=(ulongT)~0U) {
                _cimg_mp_check_constant((unsigned int)opcode[4],arg1,3);
                opcode[4] = (ulongT)mem[opcode[4]];
              }
              if (opcode[5]!=(ulongT)~0U) {
                _cimg_mp_check_constant((unsigned int)opcode[5],arg1 + 1,3);
                opcode[5] = (ulongT)mem[opcode[5]];
              }
              if (opcode[6]!=(ulongT)~0U) {
                _cimg_mp_check_constant((unsigned int)opcode[6],arg1 + 2,3);
                opcode[6] = (ulongT)mem[opcode[6]];
              }
              if (opcode[7]!=(ulongT)~0U) {
                _cimg_mp_check_constant((unsigned int)opcode[7],arg1 + 3,3);
                opcode[7] = (ulongT)mem[opcode[7]];
              }
              _cimg_mp_check_type((unsigned int)opcode[8],arg1 + 4,1,0);

              if (opcode[4]==(ulongT)~0U || opcode[5]==(ulongT)~0U ||
                  opcode[6]==(ulongT)~0U || opcode[7]==(ulongT)~0U) {
                if (p1!=~0U) {
                  _cimg_mp_check_constant(p1,1,1);
                  p1 = (unsigned int)cimg::mod((int)mem[p1],listin.width());
                }
                const CImg<T> &img = p1!=~0U?listin[p1]:imgin;
                if (!img) {
                  *se = saved_char;
                  s0 = ss - 4>expr._data?ss - 4:expr._data;
                  cimg::strellipsize(s0,64);
                  throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                              "CImg<%s>::%s: %s: Cannot crop empty image when "
                                              "some xyzc-coordinates are unspecified, in expression '%s%s%s'.",
                                              pixel_type(),_cimg_mp_calling_function,s_op,
                                              s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
                }
                if (opcode[4]==(ulongT)~0U) opcode[4] = (ulongT)img._width;
                if (opcode[5]==(ulongT)~0U) opcode[5] = (ulongT)img._height;
                if (opcode[6]==(ulongT)~0U) opcode[6] = (ulongT)img._depth;
                if (opcode[7]==(ulongT)~0U) opcode[7] = (ulongT)img._spectrum;
              }

              pos = vector((unsigned int)(opcode[4]*opcode[5]*opcode[6]*opcode[7]));
              CImg<ulongT>::vector((ulongT)mp_crop,
                                  pos,p1,
                                  *opcode,opcode[1],opcode[2],opcode[3],
                                  opcode[4],opcode[5],opcode[6],opcode[7],
                                  opcode[8]).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"cross(",6)) {
              _cimg_mp_op("Function 'cross()'");
              s1 = ss6; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss6,s1,depth1,0,is_single);
              arg2 = compile(++s1,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,1,2,3);
              _cimg_mp_check_type(arg2,2,2,3);
              pos = vector(3);
              CImg<ulongT>::vector((ulongT)mp_cross,pos,arg1,arg2).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"cut(",4)) {
              _cimg_mp_op("Function 'cut()'");
              s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss4,s1,depth1,0,is_single);
              s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
              arg2 = compile(++s1,s2,depth1,0,is_single);
              arg3 = compile(++s2,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg2,2,1,0);
              _cimg_mp_check_type(arg3,3,1,0);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector3_vss(mp_cut,arg1,arg2,arg3);
              if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2) && _cimg_mp_is_constant(arg3)) {
                val = mem[arg1];
                val1 = mem[arg2];
                val2 = mem[arg3];
                _cimg_mp_constant(val<val1?val1:val>val2?val2:val);
              }
              _cimg_mp_scalar3(mp_cut,arg1,arg2,arg3);
            }


            break;

          case 'd' :
            if (*ss1=='(') {
              _cimg_mp_op("Function 'd()'");
              if (*ss2=='#') {
                p1 = compile(ss3,se1,depth1,0,is_single);
                _cimg_mp_check_list(false);
              } else { if (ss2!=se1) break; p1 = ~0U; }
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_image_d,pos,p1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"date(",5)) {
              _cimg_mp_op("Function 'date()'");
              s1 = ss5; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = ss5!=se1?compile(ss5,s1,depth1,0,is_single):~0U;
              arg2 = s1<se1?compile(++s1,se1,depth1,0,is_single):~0U;
              if (arg2!=~0U) _cimg_mp_check_type(arg2,1,2,0);
              pos = arg1==~0U || _cimg_mp_is_vector(arg1)?vector(arg1==~0U?7:_cimg_mp_size(arg1)):scalar();
              CImg<ulongT>::vector((ulongT)mp_date,pos,_cimg_mp_size(pos),
                                   arg1,arg1==~0U?~0U:_cimg_mp_size(arg1),
                                   arg2,arg2==~0U?~0U:_cimg_mp_size(arg2)).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"debug(",6)) {
              _cimg_mp_op("Function 'debug()'");
              p1 = code._width;
              arg1 = compile(ss6,se1,depth1,p_ref,is_single);
              *se1 = 0;
              variable_name.assign(CImg<charT>::string(ss6,true,true).unroll('y'),true);
              cimg::strpare(variable_name,false,true);
              ((CImg<ulongT>::vector((ulongT)mp_debug,arg1,0,code._width - p1),
                variable_name)>'y').move_to(opcode);
              opcode[2] = opcode._height;
              opcode.move_to(code,p1);
              *se1 = ')';
              _cimg_mp_return(arg1);
            }

            if (!std::strncmp(ss,"display(",8)) {
              _cimg_mp_op("Function 'display()'");
              if (pexpr[se2 - expr._data]=='(') {
                CImg<ulongT>::vector((ulongT)mp_display_memory,_cimg_mp_slot_nan).move_to(code);
                _cimg_mp_return_nan();
              }
              if (*ss8!='#') {
                s1 = ss8; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                arg1 = compile(ss8,s1,depth1,0,is_single);
                arg2 = 0; arg3 = arg4 = arg5 = 1;
                if (s1<se1) {
                  s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                  arg2 = compile(s1 + 1,s2,depth1,0,is_single);
                  if (s2<se1) {
                    s3 = ++s2; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
                    arg3 = compile(s2,s3,depth1,0,is_single);
                    if (s3<se1) {
                      s2 = ++s3; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                      arg4 = compile(s3,s2,depth1,0,is_single);
                      arg5 = s2<se1?compile(++s2,se1,depth1,0,is_single):0;
                    }
                  }
                }
                _cimg_mp_check_type(arg2,2,1,0);
                _cimg_mp_check_type(arg3,3,1,0);
                _cimg_mp_check_type(arg4,4,1,0);
                _cimg_mp_check_type(arg5,5,1,0);

                c1 = *s1; *s1 = 0;
                variable_name.assign(CImg<charT>::string(ss8,true,true).unroll('y'),true);
                cimg::strpare(variable_name,false,true);
                if (_cimg_mp_is_vector(arg1))
                  ((CImg<ulongT>::vector((ulongT)mp_vector_print,arg1,0,(ulongT)_cimg_mp_size(arg1),0),
                    variable_name)>'y').move_to(opcode);
                else
                  ((CImg<ulongT>::vector((ulongT)mp_print,arg1,0,0),
                    variable_name)>'y').move_to(opcode);
                opcode[2] = opcode._height;
                opcode.move_to(code);

                ((CImg<ulongT>::vector((ulongT)mp_display,arg1,0,(ulongT)_cimg_mp_size(arg1),
                                       arg2,arg3,arg4,arg5),
                  variable_name)>'y').move_to(opcode);
                opcode[2] = opcode._height;
                opcode.move_to(code);
                *s1 = c1;
                _cimg_mp_return(arg1);

              } else {
                p1 = compile(ss8 + 1,se1,depth1,0,is_single);
                _cimg_mp_check_list(true);
                CImg<ulongT>::vector((ulongT)mp_image_display,_cimg_mp_slot_nan,p1).move_to(code);
                _cimg_mp_return_nan();
              }
            }

            if (!std::strncmp(ss,"det(",4)) {
              _cimg_mp_op("Function 'det()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              _cimg_mp_check_matrix_square(arg1,1);
              p1 = (unsigned int)cimg::round(std::sqrt((float)_cimg_mp_size(arg1)));
              _cimg_mp_scalar2(mp_det,arg1,p1);
            }

            if (!std::strncmp(ss,"diag(",5)) {
              _cimg_mp_op("Function 'diag()'");
              CImg<ulongT>::vector((ulongT)mp_diag,0,0).move_to(l_opcode);
              for (s = ss5; s<se; ++s) {
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                arg2 = compile(s,ns,depth1,0,is_single);
                if (_cimg_mp_is_vector(arg2))
                  CImg<ulongT>::sequence(_cimg_mp_size(arg2),arg2 + 1,
                                         arg2 + (ulongT)_cimg_mp_size(arg2)).
                    move_to(l_opcode);
                else CImg<ulongT>::vector(arg2).move_to(l_opcode);
                s = ns;
              }
              (l_opcode>'y').move_to(opcode);
              arg1 = opcode._height - 3;
              pos = vector(arg1*arg1);
              opcode[1] = pos;
              opcode[2] = opcode._height;
              opcode.move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"dot(",4)) {
              _cimg_mp_op("Function 'dot()'");
              s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss4,s1,depth1,0,is_single);
              arg2 = compile(++s1,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) {
                _cimg_mp_check_type(arg2,2,2,_cimg_mp_size(arg1));
                _cimg_mp_scalar3(mp_dot,arg1,arg2,_cimg_mp_size(arg1));
              }
              _cimg_mp_check_type(arg2,2,1,0);
              _cimg_mp_scalar2(mp_mul,arg1,arg2);
            }

            if (!std::strncmp(ss,"do(",3)) {
              _cimg_mp_op("Function 'do()'");
              s0 = *ss2=='('?ss3:ss8;
              s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = code._width;
              arg6 = mempos;
              p1 = compile(s0,s1,depth1,0,is_single);
              arg2 = code._width;
              p2 = s1<se1?compile(++s1,se1,depth1,0,is_single):p1;
              _cimg_mp_check_type(p2,2,1,0);
              CImg<ulongT>::vector((ulongT)mp_do,p1,p2,arg2 - arg1,code._width - arg2,_cimg_mp_size(p1),
                                   p1>=arg6 && !_cimg_mp_is_constant(p1),
                                   p2>=arg6 && !_cimg_mp_is_constant(p2)).move_to(code,arg1);
              _cimg_mp_return(p1);
            }

            if (!std::strncmp(ss,"draw(",5)) {
              if (!is_single) is_parallelizable = false;
              _cimg_mp_op("Function 'draw()'");
              if (*ss5=='#') {
                s0 = ss6; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                p1 = compile(ss6,s0++,depth1,0,is_single);
                _cimg_mp_check_list(true);
              } else { p1 = ~0U; s0 = ss5; }
              s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(s0,s1,depth1,0,is_single);
              arg2 = is_relative?0U:(unsigned int)_cimg_mp_slot_x;
              arg3 = is_relative?0U:(unsigned int)_cimg_mp_slot_y;
              arg4 = is_relative?0U:(unsigned int)_cimg_mp_slot_z;
              arg5 = is_relative?0U:(unsigned int)_cimg_mp_slot_c;
              s0 = se1;
              if (s1<se1) {
                s0 = s1 + 1; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                arg2 = compile(++s1,s0,depth1,0,is_single);
                if (_cimg_mp_is_vector(arg2)) {
                  p2 = _cimg_mp_size(arg2);
                  ++arg2;
                  if (p2>1) {
                    arg3 = arg2 + 1;
                    if (p2>2) {
                      arg4 = arg3 + 1;
                      if (p2>3) arg5 = arg4 + 1;
                    }
                  }
                  ++s0;
                  is_sth = true;
                } else {
                  if (s0<se1) {
                    is_sth = p1!=~0U;
                    s1 = s0 + 1; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                    arg3 = compile(++s0,s1,depth1,0,is_single);
                    _cimg_mp_check_type(arg3,is_sth?4:3,1,0);
                    if (s1<se1) {
                      s0 = s1 + 1; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                      arg4 = compile(++s1,s0,depth1,0,is_single);
                      _cimg_mp_check_type(arg4,is_sth?5:4,1,0);
                      if (s0<se1) {
                        s1 = s0 + 1; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                        arg5 = compile(++s0,s1,depth1,0,is_single);
                        _cimg_mp_check_type(arg5,is_sth?6:5,1,0);
                        s0 = ++s1;
                      }
                    }
                  }
                  is_sth = false;
                }
              }

              l_opcode.assign();
              CImg<ulongT>::vector((ulongT)mp_draw,arg1,(ulongT)_cimg_mp_size(arg1),p1,arg2,arg3,arg4,arg5,
                                   0,0,0,0,1,(ulongT)~0U,0,1).move_to(l_opcode);

              arg2 = arg3 = arg4 = arg5 = ~0U;
              p2 = p1!=~0U?0:1;
              if (s0<se1) {
                s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                arg2 = compile(s0,s1,depth1,0,is_single);
                _cimg_mp_check_type(arg2,p2 + (is_sth?3:6),1,0);
                if (s1<se1) {
                  s0 = s1 + 1; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                  arg3 = compile(++s1,s0,depth1,0,is_single);
                  _cimg_mp_check_type(arg3,p2 + (is_sth?4:7),1,0);
                  if (s0<se1) {
                    s1 = s0 + 1; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                    arg4 = compile(++s0,s1,depth1,0,is_single);
                    _cimg_mp_check_type(arg4,p2 + (is_sth?5:8),1,0);
                    if (s1<se1) {
                      s0 = s1 + 1; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                      arg5 = compile(++s1,s0,depth1,0,is_single);
                      _cimg_mp_check_type(arg5,p2 + (is_sth?6:9),1,0);
                    }
                  }
                }
              }
              if (s0<s1) s0 = s1;

              l_opcode(0,8) = (ulongT)arg2;
              l_opcode(0,9) = (ulongT)arg3;
              l_opcode(0,10) = (ulongT)arg4;
              l_opcode(0,11) = (ulongT)arg5;

              if (s0<se1) {
                s1 = s0 + 1; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                arg6 = compile(++s0,s1,depth1,0,is_single);
                _cimg_mp_check_type(arg6,0,1,0);
                l_opcode(0,12) = arg6;
                if (s1<se1) {
                  s0 = s1 + 1; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                  p2 = compile(++s1,s0,depth1,0,is_single);
                  _cimg_mp_check_type(p2,0,2,0);
                  l_opcode(0,13) = p2;
                  l_opcode(0,14) = _cimg_mp_size(p2);
                  p3 = s0<se1?compile(++s0,se1,depth1,0,is_single):1;
                  _cimg_mp_check_type(p3,0,1,0);
                  l_opcode(0,15) = p3;
                }
              }
              l_opcode[0].move_to(code);
              _cimg_mp_return(arg1);
            }

            break;

          case 'e' :
            if (!std::strncmp(ss,"echo(",5)) {
              _cimg_mp_op("Function 'echo()'");
              CImg<ulongT>::vector((ulongT)mp_echo,_cimg_mp_slot_nan,0).move_to(l_opcode);
              for (s = ss5; s<se; ++s) {
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                arg1 = compile(s,ns,depth1,0,is_single);
                CImg<ulongT>::vector(arg1,_cimg_mp_size(arg1)).move_to(l_opcode);
                s = ns;
              }
              (l_opcode>'y').move_to(opcode);
              opcode[2] = opcode._height;
              opcode.move_to(code);
              _cimg_mp_return_nan();
            }

            if (!std::strncmp(ss,"eig(",4)) {
              _cimg_mp_op("Function 'eig()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              _cimg_mp_check_matrix_square(arg1,1);
              p1 = (unsigned int)cimg::round(std::sqrt((float)_cimg_mp_size(arg1)));
              pos = vector((p1 + 1)*p1);
              CImg<ulongT>::vector((ulongT)mp_matrix_eig,pos,arg1,p1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"end(",4)) {
              _cimg_mp_op("Function 'end()'");
              code.swap(code_end);
              compile(ss4,se1,depth1,p_ref,true);
              code.swap(code_end);
              _cimg_mp_return_nan();
            }

            if (!std::strncmp(ss,"ellipse(",8)) {
              if (!is_single) is_parallelizable = false;
              _cimg_mp_op("Function 'ellipse()'");
              if (*ss8=='#') {
                s0 = ss + 9; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                p1 = compile(ss + 9,s0++,depth1,0,is_single);
                _cimg_mp_check_list(true);
              } else { p1 = ~0U; s0 = ss8; }
              if (s0==se1) compile(s0,se1,depth1,0,is_single);
              CImg<ulongT>::vector((ulongT)mp_ellipse,_cimg_mp_slot_nan,0,p1).move_to(l_opcode);
              for (s = s0; s<se; ++s) {
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                arg2 = compile(s,ns,depth1,0,is_single);
                if (_cimg_mp_is_vector(arg2))
                  CImg<ulongT>::sequence(_cimg_mp_size(arg2),arg2 + 1,
                                         arg2 + (ulongT)_cimg_mp_size(arg2)).
                    move_to(l_opcode);
                else CImg<ulongT>::vector(arg2).move_to(l_opcode);
                s = ns;
              }
              (l_opcode>'y').move_to(opcode);
              opcode[2] = opcode._height;
              opcode.move_to(code);
              _cimg_mp_return_nan();
            }

            if (!std::strncmp(ss,"ext(",4)) {
              _cimg_mp_op("Function 'ext()'");
              if (!is_single) is_parallelizable = false;
              CImg<ulongT>::vector((ulongT)mp_ext,0,0).move_to(l_opcode);
              pos = 1;
              for (s = ss4; s<se; ++s) {
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                arg1 = compile(s,ns,depth1,0,is_single);
                CImg<ulongT>::vector(arg1,_cimg_mp_size(arg1)).move_to(l_opcode);
                s = ns;
              }
              (l_opcode>'y').move_to(opcode);
              pos = scalar();
              opcode[1] = pos;
              opcode[2] = opcode._height;
              opcode.move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"exp(",4)) {
              _cimg_mp_op("Function 'exp()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_exp,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::exp(mem[arg1]));
              _cimg_mp_scalar1(mp_exp,arg1);
            }

            if (!std::strncmp(ss,"eye(",4)) {
              _cimg_mp_op("Function 'eye()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              _cimg_mp_check_constant(arg1,1,3);
              p1 = (unsigned int)mem[arg1];
              pos = vector(p1*p1);
              CImg<ulongT>::vector((ulongT)mp_eye,pos,p1).move_to(code);
              _cimg_mp_return(pos);
            }
            break;

          case 'f' :
            if (!std::strncmp(ss,"fact(",5)) {
              _cimg_mp_op("Function 'fact()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_factorial,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::factorial((int)mem[arg1]));
              _cimg_mp_scalar1(mp_factorial,arg1);
            }

            if (!std::strncmp(ss,"fibo(",5)) {
              _cimg_mp_op("Function 'fibo()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_fibonacci,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::fibonacci((int)mem[arg1]));
              _cimg_mp_scalar1(mp_fibonacci,arg1);
            }

            if (!std::strncmp(ss,"find(",5)) {
              _cimg_mp_op("Function 'find()'");


              s0 = ss5; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
              if (*ss5=='#') {
                p1 = compile(ss6,s0,depth1,0,is_single);
                _cimg_mp_check_list(false);
                arg1 = ~0U;
              } else {
                arg1 = compile(ss5,s0,depth1,0,is_single);
                _cimg_mp_check_type(arg1,1,2,0);
                p1 = ~0U;
              }


              s1 = ++s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg2 = compile(s0,s1,depth1,0,is_single);


              arg3 = 1; arg4 = _cimg_mp_slot_nan;
              if (s1<se1) {
                s0 = s1 + 1; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                arg3 = compile(++s1,s0,depth1,0,is_single);
                _cimg_mp_check_type(arg3,3,1,0);
                if (s0<se1) {
                  arg4 = compile(++s0,se1,depth1,0,is_single);
                  _cimg_mp_check_type(arg4,4,1,0);
                }
              }
              if (p1!=~0U) {
                if (_cimg_mp_is_vector(arg2))
                  _cimg_mp_scalar5(mp_list_find_seq,p1,arg2,_cimg_mp_size(arg2),arg3,arg4);
                _cimg_mp_scalar4(mp_list_find,p1,arg2,arg3,arg4);
              }
              if (_cimg_mp_is_vector(arg2))
                _cimg_mp_scalar6(mp_find_seq,arg1,_cimg_mp_size(arg1),arg2,_cimg_mp_size(arg2),arg3,arg4);
              _cimg_mp_scalar5(mp_find,arg1,_cimg_mp_size(arg1),arg2,arg3,arg4);
            }

            if (*ss1=='o' && *ss2=='r' && *ss3=='(') {
              _cimg_mp_op("Function 'for()'");
              s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
              s3 = s2 + 1; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
              arg1 = code._width;
              p1 = compile(ss4,s1,depth1,0,is_single);
              arg2 = code._width;
              p2 = compile(++s1,s2,depth1,0,is_single);
              arg3 = code._width;
              arg6 = mempos;
              if (s3<se1) {
                p3 = compile(s3 + 1,se1,depth1,0,is_single);
                arg4 = code._width;
                pos = compile(++s2,s3,depth1,0,is_single);
              } else {
                p3 = compile(++s2,se1,depth1,0,is_single);
                arg4 = pos = code._width;
              }
              _cimg_mp_check_type(p2,2,1,0);
              arg5 = _cimg_mp_size(pos);
              CImg<ulongT>::vector((ulongT)mp_for,p3,(ulongT)_cimg_mp_size(p3),p2,arg2 - arg1,arg3 - arg2,
                                   arg4 - arg3,code._width - arg4,
                                   p3>=arg6 && !_cimg_mp_is_constant(p3),
                                   p2>=arg6 && !_cimg_mp_is_constant(p2)).move_to(code,arg1);
              _cimg_mp_return(p3);
            }

            if (!std::strncmp(ss,"floor(",6)) {
              _cimg_mp_op("Function 'floor()'");
              arg1 = compile(ss6,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_floor,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::floor(mem[arg1]));
              _cimg_mp_scalar1(mp_floor,arg1);
            }

            if (!std::strncmp(ss,"fsize(",6)) {
              _cimg_mp_op("Function 'fsize()'");
              arg1 = compile(ss6,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,1,2,0);
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_fsize,pos,arg1,(ulongT)_cimg_mp_size(arg1)).move_to(code);
              _cimg_mp_return(pos);
            }
            break;

          case 'g' :
            if (!std::strncmp(ss,"gauss(",6)) {
              _cimg_mp_op("Function 'gauss()'");
              s1 = ss6; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss6,s1,depth1,0,is_single);
              arg2 = arg3 = 1;
              if (s1<se1) {
                s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                arg2 = compile(++s1,s2,depth1,0,is_single);
                arg3 = s2<se1?compile(++s2,se1,depth1,0,is_single):1;
              }
              _cimg_mp_check_type(arg2,2,1,0);
              _cimg_mp_check_type(arg3,3,1,0);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector3_vss(mp_gauss,arg1,arg2,arg3);
              if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2) && _cimg_mp_is_constant(arg3)) {
                val1 = mem[arg1];
                val2 = mem[arg2];
                _cimg_mp_constant(std::exp(-val1*val1/(2*val2*val2))/(mem[arg3]?std::sqrt(2*val2*val2*cimg::PI):1));
              }
              _cimg_mp_scalar3(mp_gauss,arg1,arg2,arg3);
            }

            if (!std::strncmp(ss,"gcd(",4)) {
              _cimg_mp_op("Function 'gcd()'");
              s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss4,s1,depth1,0,is_single);
              arg2 = compile(++s1,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,1,1,0);
              _cimg_mp_check_type(arg2,2,1,0);
              if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
                _cimg_mp_constant(cimg::gcd((long)mem[arg1],(long)mem[arg2]));
              _cimg_mp_scalar2(mp_gcd,arg1,arg2);
            }
            break;

          case 'h' :
            if (*ss1=='(') {
              _cimg_mp_op("Function 'h()'");
              if (*ss2=='#') {
                p1 = compile(ss3,se1,depth1,0,is_single);
                _cimg_mp_check_list(false);
              } else { if (ss2!=se1) break; p1 = ~0U; }
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_image_h,pos,p1).move_to(code);
              _cimg_mp_return(pos);
            }
            break;

          case 'i' :
            if (*ss1=='c' && *ss2=='(') {
              _cimg_mp_op("Function 'ic()'");
              if (*ss3=='#') {
                p1 = compile(ss4,se1,depth1,0,is_single);
                _cimg_mp_check_list(false);
              } else { if (ss3!=se1) break; p1 = ~0U; }
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_image_median,pos,p1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (*ss1=='f' && *ss2=='(') {
              _cimg_mp_op("Function 'if()'");
              s1 = ss3; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
              arg1 = compile(ss3,s1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,1,1,0);
              if (_cimg_mp_is_constant(arg1)) {
                if ((bool)mem[arg1]) return compile(++s1,s2,depth1,0,is_single);
                else return s2<se1?compile(++s2,se1,depth1,0,is_single):0;
              }
              p2 = code._width;
              arg2 = compile(++s1,s2,depth1,0,is_single);
              p3 = code._width;
              arg3 = s2<se1?compile(++s2,se1,depth1,0,is_single):
                _cimg_mp_is_vector(arg2)?vector(_cimg_mp_size(arg2),0):0;
              _cimg_mp_check_type(arg3,3,_cimg_mp_is_vector(arg2)?2:1,_cimg_mp_size(arg2));
              arg4 = _cimg_mp_size(arg2);
              if (arg4) pos = vector(arg4); else pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_if,pos,arg1,arg2,arg3,
                                  p3 - p2,code._width - p3,arg4).move_to(code,p2);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"int(",4)) {
              _cimg_mp_op("Function 'int()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_int,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant((longT)mem[arg1]);
              _cimg_mp_scalar1(mp_int,arg1);
            }

            if (!std::strncmp(ss,"inv(",4)) {
              _cimg_mp_op("Function 'inv()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) {
                _cimg_mp_check_matrix_square(arg1,1);
                p1 = (unsigned int)cimg::round(std::sqrt((float)_cimg_mp_size(arg1)));
                pos = vector(p1*p1);
                CImg<ulongT>::vector((ulongT)mp_matrix_inv,pos,arg1,p1).move_to(code);
                _cimg_mp_return(pos);
              }
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(1/mem[arg1]);
              _cimg_mp_scalar2(mp_div,1,arg1);
            }

            if (*ss1=='s') {

              if (!std::strncmp(ss,"isbool(",7)) {
                _cimg_mp_op("Function 'isbool()'");
                if (ss7==se1) _cimg_mp_return(0);
                try { arg1 = compile(ss7,se1,depth1,0,is_single); }
                catch(CImgException&) { _cimg_mp_return(0); }
                if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_isbool,arg1);
                if (_cimg_mp_is_constant(arg1)) _cimg_mp_return(mem[arg1]==0. || mem[arg1]==1.);
                _cimg_mp_scalar1(mp_isbool,arg1);
              }

              if (!std::strncmp(ss,"isdir(",6)) {
                _cimg_mp_op("Function 'isdir()'");
                arg1 = compile(ss6,se1,depth1,0,is_single);
                if (_cimg_mp_is_scalar(arg1)) _cimg_mp_return(0);
                pos = scalar();
                CImg<ulongT>::vector((ulongT)mp_isdir,pos,arg1,(ulongT)_cimg_mp_size(arg1)).move_to(code);
                _cimg_mp_return(pos);
              }

              if (!std::strncmp(ss,"isfile(",7)) {
                _cimg_mp_op("Function 'isfile()'");
                arg1 = compile(ss7,se1,depth1,0,is_single);
                if (_cimg_mp_is_scalar(arg1)) _cimg_mp_return(0);
                pos = scalar();
                CImg<ulongT>::vector((ulongT)mp_isfile,pos,arg1,(ulongT)_cimg_mp_size(arg1)).move_to(code);
                _cimg_mp_return(pos);
              }

              if (!std::strncmp(ss,"isin(",5)) {
                if (ss5>=se1) _cimg_mp_return(0);
                _cimg_mp_op("Function 'isin()'");
                pos = scalar();
                CImg<ulongT>::vector((ulongT)mp_isin,pos,0).move_to(l_opcode);
                for (s = ss5; s<se; ++s) {
                  ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                                 (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                  arg1 = compile(s,ns,depth1,0,is_single);
                  if (_cimg_mp_is_vector(arg1))
                    CImg<ulongT>::sequence(_cimg_mp_size(arg1),arg1 + 1,
                                           arg1 + (ulongT)_cimg_mp_size(arg1)).
                      move_to(l_opcode);
                  else CImg<ulongT>::vector(arg1).move_to(l_opcode);
                  s = ns;
                }
                (l_opcode>'y').move_to(opcode);
                opcode[2] = opcode._height;
                opcode.move_to(code);
                _cimg_mp_return(pos);
              }

              if (!std::strncmp(ss,"isinf(",6)) {
                _cimg_mp_op("Function 'isinf()'");
                if (ss6==se1) _cimg_mp_return(0);
                arg1 = compile(ss6,se1,depth1,0,is_single);
                if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_isinf,arg1);
                if (_cimg_mp_is_constant(arg1)) _cimg_mp_return((unsigned int)cimg::type<double>::is_inf(mem[arg1]));
                _cimg_mp_scalar1(mp_isinf,arg1);
              }

              if (!std::strncmp(ss,"isint(",6)) {
                _cimg_mp_op("Function 'isint()'");
                if (ss6==se1) _cimg_mp_return(0);
                try { arg1 = compile(ss6,se1,depth1,0,is_single); }
                catch(CImgException&) { _cimg_mp_return(0); }
                if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_isint,arg1);
                if (_cimg_mp_is_constant(arg1)) _cimg_mp_return((unsigned int)(cimg::mod(mem[arg1],1.)==0));
                _cimg_mp_scalar1(mp_isint,arg1);
              }

              if (!std::strncmp(ss,"isnan(",6)) {
                _cimg_mp_op("Function 'isnan()'");
                if (ss6==se1) _cimg_mp_return(0);
                arg1 = compile(ss6,se1,depth1,0,is_single);
                if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_isnan,arg1);
                if (_cimg_mp_is_constant(arg1)) _cimg_mp_return((unsigned int)cimg::type<double>::is_nan(mem[arg1]));
                _cimg_mp_scalar1(mp_isnan,arg1);
              }

              if (!std::strncmp(ss,"isnum(",6)) {
                _cimg_mp_op("Function 'isnum()'");
                val = 0;
                if (cimg_sscanf(ss6,"%lf%c%c",&val,&sep,&end)==2 && sep==')') _cimg_mp_return(1);
                _cimg_mp_return(0);
              }

              if (!std::strncmp(ss,"isexpr(",7)) {
                _cimg_mp_op("Function 'isexpr()'");
                if (ss7==se1) _cimg_mp_return(0);
                try { arg1 = compile(ss7,se1,depth1,0,is_single); }
                catch (CImgException&) { _cimg_mp_return(0); }
                _cimg_mp_return(1);
              }
            }
            break;

          case 'l' :
            if (*ss1=='(') {
              _cimg_mp_op("Function 'l()'");
              if (ss2!=se1) break;
              _cimg_mp_scalar0(mp_list_l);
            }

            if (!std::strncmp(ss,"log(",4)) {
              _cimg_mp_op("Function 'log()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_log,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::log(mem[arg1]));
              _cimg_mp_scalar1(mp_log,arg1);
            }

            if (!std::strncmp(ss,"log2(",5)) {
              _cimg_mp_op("Function 'log2()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_log2,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::log2(mem[arg1]));
              _cimg_mp_scalar1(mp_log2,arg1);
            }

            if (!std::strncmp(ss,"log10(",6)) {
              _cimg_mp_op("Function 'log10()'");
              arg1 = compile(ss6,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_log10,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::log10(mem[arg1]));
              _cimg_mp_scalar1(mp_log10,arg1);
            }

            if (!std::strncmp(ss,"lowercase(",10)) {
              _cimg_mp_op("Function 'lowercase()'");
              arg1 = compile(ss + 10,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_lowercase,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::lowercase(mem[arg1]));
              _cimg_mp_scalar1(mp_lowercase,arg1);
            }
            break;

          case 'm' :
            if (!std::strncmp(ss,"mul(",4)) {
              _cimg_mp_op("Function 'mul()'");
              s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss4,s1,depth1,0,is_single);
              s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
              arg2 = compile(++s1,s2,depth1,0,is_single);
              arg3 = s2<se1?compile(++s2,se1,depth1,0,is_single):1;
              _cimg_mp_check_type(arg1,1,2,0);
              _cimg_mp_check_type(arg2,2,2,0);
              _cimg_mp_check_constant(arg3,3,3);
              p1 = _cimg_mp_size(arg1);
              p2 = _cimg_mp_size(arg2);
              p3 = (unsigned int)mem[arg3];
              arg5 = p2/p3;
              arg4 = p1/arg5;
              if (arg4*arg5!=p1 || arg5*p3!=p2) {
                *se = saved_char;
                s0 = ss - 4>expr._data?ss - 4:expr._data;
                cimg::strellipsize(s0,64);
                throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                            "CImg<%s>::%s: %s: Types of first and second arguments ('%s' and '%s') "
                                            "do not match with third argument 'nb_colsB=%u', "
                                            "in expression '%s%s%s'.",
                                            pixel_type(),_cimg_mp_calling_function,s_op,
                                            s_type(arg1)._data,s_type(arg2)._data,p3,
                                            s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
              }
              pos = vector(arg4*p3);
              CImg<ulongT>::vector((ulongT)mp_matrix_mul,pos,arg1,arg2,arg4,arg5,p3).move_to(code);
              _cimg_mp_return(pos);
            }
            break;

          case 'n' :
            if (!std::strncmp(ss,"narg(",5)) {
              _cimg_mp_op("Function 'narg()'");
              if (ss5>=se1) _cimg_mp_return(0);
              arg1 = 0;
              for (s = ss5; s<se; ++s) {
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                ++arg1; s = ns;
              }
              _cimg_mp_constant(arg1);
            }

            if ((cimg_sscanf(ss,"norm%u%c",&(arg1=~0U),&sep)==2 && sep=='(') ||
                !std::strncmp(ss,"norminf(",8) || !std::strncmp(ss,"norm(",5) ||
                (!std::strncmp(ss,"norm",4) && ss5<se1 && (s=std::strchr(ss5,'('))!=0)) {
              _cimg_mp_op("Function 'normP()'");
              if (*ss4=='(') { arg1 = 2; s = ss5; }
              else if (*ss4=='i' && *ss5=='n' && *ss6=='f' && *ss7=='(') { arg1 = ~0U; s = ss8; }
              else if (arg1==~0U) {
                arg1 = compile(ss4,s++,depth1,0,is_single);
                _cimg_mp_check_constant(arg1,0,2);
                arg1 = (unsigned int)mem[arg1];
              } else s = std::strchr(ss4,'(') + 1;
              pos = scalar();
              switch (arg1) {
              case 0 :
                CImg<ulongT>::vector((ulongT)mp_norm0,pos,0).move_to(l_opcode); break;
              case 1 :
                CImg<ulongT>::vector((ulongT)mp_norm1,pos,0).move_to(l_opcode); break;
              case 2 :
                CImg<ulongT>::vector((ulongT)mp_norm2,pos,0).move_to(l_opcode); break;
              case ~0U :
                CImg<ulongT>::vector((ulongT)mp_norminf,pos,0).move_to(l_opcode); break;
              default :
                CImg<ulongT>::vector((ulongT)mp_normp,pos,0,(ulongT)(arg1==~0U?-1:(int)arg1)).
                  move_to(l_opcode);
              }
              for ( ; s<se; ++s) {
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                arg2 = compile(s,ns,depth1,0,is_single);
                if (_cimg_mp_is_vector(arg2))
                  CImg<ulongT>::sequence(_cimg_mp_size(arg2),arg2 + 1,
                                         arg2 + (ulongT)_cimg_mp_size(arg2)).
                    move_to(l_opcode);
                else CImg<ulongT>::vector(arg2).move_to(l_opcode);
                s = ns;
              }

              (l_opcode>'y').move_to(opcode);
              if (arg1>0 && opcode._height==4)
                _cimg_mp_scalar1(mp_abs,opcode[3]);
              opcode[2] = opcode._height;
              opcode.move_to(code);
              _cimg_mp_return(pos);
            }
            break;

          case 'p' :
            if (!std::strncmp(ss,"permut(",7)) {
              _cimg_mp_op("Function 'permut()'");
              s1 = ss7; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
              arg1 = compile(ss7,s1,depth1,0,is_single);
              arg2 = compile(++s1,s2,depth1,0,is_single);
              arg3 = compile(++s2,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,1,1,0);
              _cimg_mp_check_type(arg2,2,1,0);
              _cimg_mp_check_type(arg3,3,1,0);
              if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2) && _cimg_mp_is_constant(arg3))
                _cimg_mp_constant(cimg::permutations((int)mem[arg1],(int)mem[arg2],(bool)mem[arg3]));
              _cimg_mp_scalar3(mp_permutations,arg1,arg2,arg3);
            }

            if (!std::strncmp(ss,"polygon(",8)) {
              if (!is_single) is_parallelizable = false;
              _cimg_mp_op("Function 'polygon()'");
              if (*ss8=='#') {
                s0 = ss + 9; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                p1 = compile(ss + 9,s0++,depth1,0,is_single);
                _cimg_mp_check_list(true);
              } else { p1 = ~0U; s0 = ss8; }
              if (s0==se1) compile(s0,se1,depth1,0,is_single);
              CImg<ulongT>::vector((ulongT)mp_polygon,_cimg_mp_slot_nan,0,p1).move_to(l_opcode);
              for (s = s0; s<se; ++s) {
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                arg2 = compile(s,ns,depth1,0,is_single);
                if (_cimg_mp_is_vector(arg2))
                  CImg<ulongT>::sequence(_cimg_mp_size(arg2),arg2 + 1,
                                         arg2 + (ulongT)_cimg_mp_size(arg2)).
                    move_to(l_opcode);
                else CImg<ulongT>::vector(arg2).move_to(l_opcode);
                s = ns;
              }
              (l_opcode>'y').move_to(opcode);
              opcode[2] = opcode._height;
              opcode.move_to(code);
              _cimg_mp_return_nan();
            }

            if (!std::strncmp(ss,"print(",6) || !std::strncmp(ss,"prints(",7)) {
              is_sth = ss[5]=='s';
              _cimg_mp_op(is_sth?"Function 'prints()'":"Function 'print()'");
              s0 = is_sth?ss7:ss6;
              if (*s0!='#' || is_sth) {
                for (s = s0; s<se; ++s) {
                  ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                                 (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                  pos = compile(s,ns,depth1,p_ref,is_single);
                  c1 = *ns; *ns = 0;
                  variable_name.assign(CImg<charT>::string(s,true,true).unroll('y'),true);
                  cimg::strpare(variable_name,false,true);
                  if (_cimg_mp_is_vector(pos))
                    ((CImg<ulongT>::vector((ulongT)mp_vector_print,pos,0,(ulongT)_cimg_mp_size(pos),is_sth?1:0),
                      variable_name)>'y').move_to(opcode);
                  else
                    ((CImg<ulongT>::vector((ulongT)mp_print,pos,0,is_sth?1:0),
                      variable_name)>'y').move_to(opcode);
                  opcode[2] = opcode._height;
                  opcode.move_to(code);
                  *ns = c1; s = ns;
                }
                _cimg_mp_return(pos);
              } else {
                p1 = compile(ss7,se1,depth1,0,is_single);
                _cimg_mp_check_list(true);
                CImg<ulongT>::vector((ulongT)mp_image_print,_cimg_mp_slot_nan,p1).move_to(code);
                _cimg_mp_return_nan();
              }
            }

            if (!std::strncmp(ss,"pseudoinv(",10)) {
              _cimg_mp_op("Function 'pseudoinv()'");
              s1 = ss + 10; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss + 10,s1,depth1,0,is_single);
              arg2 = s1<se1?compile(++s1,se1,depth1,0,is_single):1;
              _cimg_mp_check_type(arg1,1,2,0);
              _cimg_mp_check_constant(arg2,2,3);
              p1 = _cimg_mp_size(arg1);
              p2 = (unsigned int)mem[arg2];
              p3 = p1/p2;
              if (p3*p2!=p1) {
                *se = saved_char;
                s0 = ss - 4>expr._data?ss - 4:expr._data;
                cimg::strellipsize(s0,64);
                throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                            "CImg<%s>::%s: %s: Type of first argument ('%s') "
                                            "does not match with second argument 'nb_colsA=%u', "
                                            "in expression '%s%s%s'.",
                                            pixel_type(),_cimg_mp_calling_function,s_op,
                                            s_type(arg1)._data,p2,
                                            s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
              }
              pos = vector(p1);
              CImg<ulongT>::vector((ulongT)mp_matrix_pseudoinv,pos,arg1,p2,p3).move_to(code);
              _cimg_mp_return(pos);
            }
            break;

          case 'r' :
            if (!std::strncmp(ss,"resize(",7)) {
              _cimg_mp_op("Function 'resize()'");
              if (*ss7!='#') {
                s1 = ss7; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                arg1 = compile(ss7,s1,depth1,0,is_single);
                s2 = ++s1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                arg2 = compile(s1,s2,depth1,0,is_single);
                arg3 = 1;
                arg4 = 0;
                if (s2<se1) {
                  s1 = ++s2; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                  arg3 = compile(s2,s1,depth1,0,is_single);
                  arg4 = s1<se1?compile(++s1,se1,depth1,0,is_single):0;
                }
                _cimg_mp_check_constant(arg2,2,3);
                arg2 = (unsigned int)mem[arg2];
                _cimg_mp_check_type(arg3,3,1,0);
                _cimg_mp_check_type(arg4,4,1,0);
                pos = vector(arg2);
                CImg<ulongT>::vector((ulongT)mp_vector_resize,pos,arg2,arg1,(ulongT)_cimg_mp_size(arg1),
                                     arg3,arg4).move_to(code);
                _cimg_mp_return(pos);

              } else {
                if (!is_single) is_parallelizable = false;
                s0 = ss8; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                p1 = compile(ss8,s0++,depth1,0,is_single);
                _cimg_mp_check_list(true);
                l_opcode.assign();
                CImg<ulongT>::vector((ulongT)mp_image_resize,_cimg_mp_slot_nan,p1,~0U,~0U,~0U,~0U,1,0,0,0,0,0).
                  move_to(l_opcode);
                pos = 0;
                for (s = s0; s<se && pos<10; ++s) {
                  ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                                 (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                  arg1 = compile(s,ns,depth1,0,is_single);
                  _cimg_mp_check_type(arg1,pos + 2,1,0);
                  l_opcode(0,pos + 3) = arg1;
                  s = ns;
                  ++pos;
                }
                if (pos<1 || pos>10) {
                  *se = saved_char;
                  s0 = ss - 4>expr._data?ss - 4:expr._data;
                  cimg::strellipsize(s0,64);
                  throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                              "CImg<%s>::%s: %s: %s arguments, in expression '%s%s%s'.",
                                              pixel_type(),_cimg_mp_calling_function,s_op,
                                              pos<1?"Missing":"Too much",
                                              s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
                }
                l_opcode[0].move_to(code);
                _cimg_mp_return_nan();
              }
            }

            if (!std::strncmp(ss,"reverse(",8)) {
              _cimg_mp_op("Function 'reverse()'");
              arg1 = compile(ss8,se1,depth1,0,is_single);
              if (!_cimg_mp_is_vector(arg1)) _cimg_mp_return(arg1);
              p1 = _cimg_mp_size(arg1);
              pos = vector(p1);
              CImg<ulongT>::vector((ulongT)mp_vector_reverse,pos,arg1,p1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"rol(",4) || !std::strncmp(ss,"ror(",4)) {
              _cimg_mp_op(ss[2]=='l'?"Function 'rol()'":"Function 'ror()'");
              s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1-expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss4,s1,depth1,0,is_single);
              arg2 = s1<se1?compile(++s1,se1,depth1,0,is_single):1;
              _cimg_mp_check_type(arg2,2,1,0);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector2_vs(*ss2=='l'?mp_rol:mp_ror,arg1,arg2);
              if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
                _cimg_mp_constant(*ss2=='l'?cimg::rol(mem[arg1],(unsigned int)mem[arg2]):
                                  cimg::ror(mem[arg1],(unsigned int)mem[arg2]));
              _cimg_mp_scalar2(*ss2=='l'?mp_rol:mp_ror,arg1,arg2);
            }

            if (!std::strncmp(ss,"rot(",4)) {
              _cimg_mp_op("Function 'rot()'");
              s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss4,s1,depth1,0,is_single);
              if (s1<se1) {
                _cimg_mp_check_type(arg1,1,3,3);
                is_sth = false;
                if (_cimg_mp_is_vector(arg1)) {
                  is_sth = true;
                  p2 = _cimg_mp_size(arg1);
                  ++arg1;
                  arg2 = arg3 = 0;
                  if (p2>1) {
                    arg2 = arg1 + 1;
                    if (p2>2) arg3 = arg2 + 1;
                  }
                  arg4 = compile(++s1,se1,depth1,0,is_single);
                } else {
                  s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                  arg2 = compile(++s1,s2,depth1,0,is_single);
                  s3 = s2 + 1; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
                  arg3 = compile(++s2,s3,depth1,0,is_single);
                  arg4 = compile(++s3,se1,depth1,0,is_single);
                  _cimg_mp_check_type(arg2,2,1,0);
                  _cimg_mp_check_type(arg3,3,1,0);
                }
                _cimg_mp_check_type(arg4,is_sth?2:4,1,0);
                pos = vector(9);
                CImg<ulongT>::vector((ulongT)mp_rot3d,pos,arg1,arg2,arg3,arg4).move_to(code);
              } else {
                _cimg_mp_check_type(arg1,1,1,0);
                pos = vector(4);
                CImg<ulongT>::vector((ulongT)mp_rot2d,pos,arg1).move_to(code);
              }
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"round(",6)) {
              _cimg_mp_op("Function 'round()'");
              s1 = ss6; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss6,s1,depth1,0,is_single);
              arg2 = 1;
              arg3 = 0;
              if (s1<se1) {
                s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                arg2 = compile(++s1,s2,depth1,0,is_single);
                arg3 = s2<se1?compile(++s2,se1,depth1,0,is_single):0;
              }
              _cimg_mp_check_type(arg2,2,1,0);
              _cimg_mp_check_type(arg3,3,1,0);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector3_vss(mp_round,arg1,arg2,arg3);
              if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2) && _cimg_mp_is_constant(arg3))
                _cimg_mp_constant(cimg::round(mem[arg1],mem[arg2],(int)mem[arg3]));
              _cimg_mp_scalar3(mp_round,arg1,arg2,arg3);
            }
            break;

          case 's' :
            if (*ss1=='(') {
              _cimg_mp_op("Function 's()'");
              if (*ss2=='#') {
                p1 = compile(ss3,se1,depth1,0,is_single);
                _cimg_mp_check_list(false);
              } else { if (ss2!=se1) break; p1 = ~0U; }
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_image_s,pos,p1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"same(",5)) {
              _cimg_mp_op("Function 'same()'");
              s1 = ss5; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss5,s1,depth1,0,is_single);
              s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
              arg2 = compile(++s1,s2,depth1,0,is_single);
              arg3 = 11;
              arg4 = 1;
              if (s2<se1) {
                s3 = s2 + 1; while (s3<se1 && (*s3!=',' || level[s3 - expr._data]!=clevel1)) ++s3;
                arg3 = compile(++s2,s3,depth1,0,is_single);
                _cimg_mp_check_type(arg3,3,1,0);
                arg4 = s3<se1?compile(++s3,se1,depth1,0,is_single):1;
              }
              p1 = _cimg_mp_size(arg1);
              p2 = _cimg_mp_size(arg2);
              _cimg_mp_scalar6(mp_vector_eq,arg1,p1,arg2,p2,arg3,arg4);
            }

            if (!std::strncmp(ss,"shift(",6)) {
              _cimg_mp_op("Function 'shift()'");
              s1 = ss6; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss6,s1,depth1,0,is_single);
              arg2 = 1; arg3 = 0;
              if (s1<se1) {
                s0 = ++s1; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                arg2 = compile(s1,s0,depth1,0,is_single);
                arg3 = s0<se1?compile(++s0,se1,depth1,0,is_single):0;
              }
              _cimg_mp_check_type(arg1,1,2,0);
              _cimg_mp_check_type(arg2,2,1,0);
              _cimg_mp_check_type(arg3,3,1,0);
              p1 = _cimg_mp_size(arg1);
              pos = vector(p1);
              CImg<ulongT>::vector((ulongT)mp_shift,pos,arg1,p1,arg2,arg3).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"sign(",5)) {
              _cimg_mp_op("Function 'sign()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_sign,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::sign(mem[arg1]));
              _cimg_mp_scalar1(mp_sign,arg1);
            }

            if (!std::strncmp(ss,"sin(",4)) {
              _cimg_mp_op("Function 'sin()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_sin,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::sin(mem[arg1]));
              _cimg_mp_scalar1(mp_sin,arg1);
            }

            if (!std::strncmp(ss,"sinc(",5)) {
              _cimg_mp_op("Function 'sinc()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_sinc,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::sinc(mem[arg1]));
              _cimg_mp_scalar1(mp_sinc,arg1);
            }

            if (!std::strncmp(ss,"sinh(",5)) {
              _cimg_mp_op("Function 'sinh()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_sinh,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::sinh(mem[arg1]));
              _cimg_mp_scalar1(mp_sinh,arg1);
            }

            if (!std::strncmp(ss,"size(",5)) {
              _cimg_mp_op("Function 'size()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              _cimg_mp_constant(_cimg_mp_is_scalar(arg1)?0:_cimg_mp_size(arg1));
            }

            if (!std::strncmp(ss,"solve(",6)) {
              _cimg_mp_op("Function 'solve()'");
              s1 = ss6; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss6,s1,depth1,0,is_single);
              s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
              arg2 = compile(++s1,s2,depth1,0,is_single);
              arg3 = s2<se1?compile(++s2,se1,depth1,0,is_single):1;
              _cimg_mp_check_type(arg1,1,2,0);
              _cimg_mp_check_type(arg2,2,2,0);
              _cimg_mp_check_constant(arg3,3,3);
              p1 = _cimg_mp_size(arg1);
              p2 = _cimg_mp_size(arg2);
              p3 = (unsigned int)mem[arg3];
              arg5 = p2/p3;
              arg4 = p1/arg5;
              if (arg4*arg5!=p1 || arg5*p3!=p2) {
                *se = saved_char;
                s0 = ss - 4>expr._data?ss - 4:expr._data;
                cimg::strellipsize(s0,64);
                throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                            "CImg<%s>::%s: %s: Types of first and second arguments ('%s' and '%s') "
                                            "do not match with third argument 'nb_colsB=%u', "
                                            "in expression '%s%s%s'.",
                                            pixel_type(),_cimg_mp_calling_function,s_op,
                                            s_type(arg1)._data,s_type(arg2)._data,p3,
                                            s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
              }
              pos = vector(arg4*p3);
              CImg<ulongT>::vector((ulongT)mp_solve,pos,arg1,arg2,arg4,arg5,p3).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"sort(",5)) {
              _cimg_mp_op("Function 'sort()'");
              if (*ss5!='#') {
                s1 = ss5; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                arg1 = compile(ss5,s1,depth1,0,is_single);
                arg2 = arg3 = 1;
                if (s1<se1) {
                  s0 = ++s1; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                  arg2 = compile(s1,s0,depth1,0,is_single);
                  arg3 = s0<se1?compile(++s0,se1,depth1,0,is_single):1;
                }
                _cimg_mp_check_type(arg1,1,2,0);
                _cimg_mp_check_type(arg2,2,1,0);
                _cimg_mp_check_constant(arg3,3,3);
                arg3 = (unsigned int)mem[arg3];
                p1 = _cimg_mp_size(arg1);
                if (p1%arg3) {
                  *se = saved_char;
                  s0 = ss - 4>expr._data?ss - 4:expr._data;
                  cimg::strellipsize(s0,64);
                  throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                              "CImg<%s>::%s: %s: Invalid specified chunk size (%u) for first argument "
                                              "('%s'), in expression '%s%s%s'.",
                                              pixel_type(),_cimg_mp_calling_function,s_op,
                                              arg3,s_type(arg1)._data,
                                              s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
                }
                pos = vector(p1);
                CImg<ulongT>::vector((ulongT)mp_sort,pos,arg1,p1,arg2,arg3).move_to(code);
                _cimg_mp_return(pos);

              } else {
                s1 = ss6; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
                p1 = compile(ss6,s1,depth1,0,is_single);
                arg1 = 1;
                arg2 = constant(-1.);
                if (s1<se1) {
                  s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                  arg1 = compile(++s1,s2,depth1,0,is_single);
                  if (s2<se1) arg2 = compile(++s2,se1,depth1,0,is_single);
                }
                _cimg_mp_check_type(arg1,2,1,0);
                _cimg_mp_check_type(arg2,3,1,0);
                _cimg_mp_check_list(true);
                CImg<ulongT>::vector((ulongT)mp_image_sort,_cimg_mp_slot_nan,p1,arg1,arg2).move_to(code);
                _cimg_mp_return_nan();
              }
            }

            if (!std::strncmp(ss,"sqr(",4)) {
              _cimg_mp_op("Function 'sqr()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_sqr,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::sqr(mem[arg1]));
              _cimg_mp_scalar1(mp_sqr,arg1);
            }

            if (!std::strncmp(ss,"sqrt(",5)) {
              _cimg_mp_op("Function 'sqrt()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_sqrt,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::sqrt(mem[arg1]));
              _cimg_mp_scalar1(mp_sqrt,arg1);
            }

            if (!std::strncmp(ss,"srand(",6)) {
              _cimg_mp_op("Function 'srand()'");
              arg1 = ss6<se1?compile(ss6,se1,depth1,0,is_single):~0U;
              if (arg1!=~0U) { _cimg_mp_check_type(arg1,1,1,0); _cimg_mp_scalar1(mp_srand,arg1); }
              _cimg_mp_scalar0(mp_srand0);
            }

            if (!std::strncmp(ss,"stats(",6)) {
              _cimg_mp_op("Function 'stats()'");
              if (*ss6=='#') {
                p1 = compile(ss7,se1,depth1,0,is_single);
                _cimg_mp_check_list(false);
              } else { if (ss6!=se1) break; p1 = ~0U; }
              pos = vector(14);
              CImg<ulongT>::vector((ulongT)mp_image_stats,pos,p1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"stov(",5)) {
              _cimg_mp_op("Function 'stov()'");
              s1 = ss5; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss5,s1,depth1,0,is_single);
              arg2 = arg3 = 0;
              if (s1<se1) {
                s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                arg2 = compile(++s1,s2,depth1,0,is_single);
                arg3 = s2<se1?compile(++s2,se1,depth1,0,is_single):0;
              }
              _cimg_mp_check_type(arg2,2,1,0);
              _cimg_mp_check_type(arg3,3,1,0);
              p1 = _cimg_mp_size(arg1);
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_stov,pos,arg1,p1,arg2,arg3).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"svd(",4)) {
              _cimg_mp_op("Function 'svd()'");
              s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss4,s1,depth1,0,is_single);
              arg2 = s1<se1?compile(++s1,se1,depth1,0,is_single):1;
              _cimg_mp_check_type(arg1,1,2,0);
              _cimg_mp_check_constant(arg2,2,3);
              p1 = _cimg_mp_size(arg1);
              p2 = (unsigned int)mem[arg2];
              p3 = p1/p2;
              if (p3*p2!=p1) {
                *se = saved_char;
                s0 = ss - 4>expr._data?ss - 4:expr._data;
                cimg::strellipsize(s0,64);
                throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                            "CImg<%s>::%s: %s: Type of first argument ('%s') "
                                            "does not match with second argument 'nb_colsA=%u', "
                                            "in expression '%s%s%s'.",
                                            pixel_type(),_cimg_mp_calling_function,s_op,
                                            s_type(arg1)._data,p2,
                                            s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
              }
              pos = vector(p1 + p2 + p2*p2);
              CImg<ulongT>::vector((ulongT)mp_matrix_svd,pos,arg1,p2,p3).move_to(code);
              _cimg_mp_return(pos);
            }
            break;

          case 't' :
            if (!std::strncmp(ss,"tan(",4)) {
              _cimg_mp_op("Function 'tan()'");
              arg1 = compile(ss4,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_tan,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::tan(mem[arg1]));
              _cimg_mp_scalar1(mp_tan,arg1);
            }

            if (!std::strncmp(ss,"tanh(",5)) {
              _cimg_mp_op("Function 'tanh()'");
              arg1 = compile(ss5,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_tanh,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(std::tanh(mem[arg1]));
              _cimg_mp_scalar1(mp_tanh,arg1);
            }

            if (!std::strncmp(ss,"trace(",6)) {
              _cimg_mp_op("Function 'trace()'");
              arg1 = compile(ss6,se1,depth1,0,is_single);
              _cimg_mp_check_matrix_square(arg1,1);
              p1 = (unsigned int)cimg::round(std::sqrt((float)_cimg_mp_size(arg1)));
              _cimg_mp_scalar2(mp_trace,arg1,p1);
            }

            if (!std::strncmp(ss,"transp(",7)) {
              _cimg_mp_op("Function 'transp()'");
              s1 = ss7; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss7,s1,depth1,0,is_single);
              arg2 = compile(++s1,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,1,2,0);
              _cimg_mp_check_constant(arg2,2,3);
              p1 = _cimg_mp_size(arg1);
              p2 = (unsigned int)mem[arg2];
              p3 = p1/p2;
              if (p2*p3!=p1) {
                *se = saved_char;
                s0 = ss - 4>expr._data?ss - 4:expr._data;
                cimg::strellipsize(s0,64);
                throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                            "CImg<%s>::%s: %s: Size of first argument ('%s') does not match "
                                            "second argument 'nb_cols=%u', in expression '%s%s%s'.",
                                            pixel_type(),_cimg_mp_calling_function,s_op,
                                            s_type(arg1)._data,p2,
                                            s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
              }
              pos = vector(p3*p2);
              CImg<ulongT>::vector((ulongT)mp_transp,pos,arg1,p2,p3).move_to(code);
              _cimg_mp_return(pos);
            }
            break;

          case 'u' :
            if (*ss1=='(') {
              _cimg_mp_op("Function 'u()'");
              if (*ss2==')') _cimg_mp_scalar2(mp_u,0,1);
              s1 = ss2; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss2,s1,depth1,0,is_single);
              if (s1<se1) arg2 = compile(++s1,se1,depth1,0,is_single); else { arg2 = arg1; arg1 = 0; }
              _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
              if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_u,arg1,arg2);
              if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_u,arg1,arg2);
              if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_u,arg1,arg2);
              _cimg_mp_scalar2(mp_u,arg1,arg2);
            }

            if (!std::strncmp(ss,"unref(",6)) {
              _cimg_mp_op("Function 'unref()'");
              arg1 = ~0U;
              for (s0 = ss6; s0<se1; s0 = s1) {
                if (s0>ss6 && *s0==',') ++s0;
                s1 = s0; while (s1<se1 && *s1!=',') ++s1;
                c1 = *s1;
                if (s1>s0) {
                  *s1 = 0;
                  arg2 = arg3 = ~0U;
                  if (s0[0]=='w' && s0[1]=='h' && !s0[2]) arg1 = reserved_label[arg3 = 0];
                  else if (s0[0]=='w' && s0[1]=='h' && s0[2]=='d' && !s0[3]) arg1 = reserved_label[arg3 = 1];
                  else if (s0[0]=='w' && s0[1]=='h' && s0[2]=='d' && s0[3]=='s' && !s0[4])
                    arg1 = reserved_label[arg3 = 2];
                  else if (s0[0]=='p' && s0[1]=='i' && !s0[2]) arg1 = reserved_label[arg3 = 3];
                  else if (s0[0]=='i' && s0[1]=='m' && !s0[2]) arg1 = reserved_label[arg3 = 4];
                  else if (s0[0]=='i' && s0[1]=='M' && !s0[2]) arg1 = reserved_label[arg3 = 5];
                  else if (s0[0]=='i' && s0[1]=='a' && !s0[2]) arg1 = reserved_label[arg3 = 6];
                  else if (s0[0]=='i' && s0[1]=='v' && !s0[2]) arg1 = reserved_label[arg3 = 7];
                  else if (s0[0]=='i' && s0[1]=='s' && !s0[2]) arg1 = reserved_label[arg3 = 8];
                  else if (s0[0]=='i' && s0[1]=='p' && !s0[2]) arg1 = reserved_label[arg3 = 9];
                  else if (s0[0]=='i' && s0[1]=='c' && !s0[2]) arg1 = reserved_label[arg3 = 10];
                  else if (s0[0]=='x' && s0[1]=='m' && !s0[2]) arg1 = reserved_label[arg3 = 11];
                  else if (s0[0]=='y' && s0[1]=='m' && !s0[2]) arg1 = reserved_label[arg3 = 12];
                  else if (s0[0]=='z' && s0[1]=='m' && !s0[2]) arg1 = reserved_label[arg3 = 13];
                  else if (s0[0]=='c' && s0[1]=='m' && !s0[2]) arg1 = reserved_label[arg3 = 14];
                  else if (s0[0]=='x' && s0[1]=='M' && !s0[2]) arg1 = reserved_label[arg3 = 15];
                  else if (s0[0]=='y' && s0[1]=='M' && !s0[2]) arg1 = reserved_label[arg3 = 16];
                  else if (s0[0]=='z' && s0[1]=='M' && !s0[2]) arg1 = reserved_label[arg3 = 17];
                  else if (s0[0]=='c' && s0[1]=='M' && !s0[2]) arg1 = reserved_label[arg3 = 18];
                  else if (s0[0]=='i' && s0[1]>='0' && s0[1]<='9' && !s0[2])
                    arg1 = reserved_label[arg3 = 19 + s0[1] - '0'];
                  else if (!std::strcmp(s0,"interpolation")) arg1 = reserved_label[arg3 = 29];
                  else if (!std::strcmp(s0,"boundary")) arg1 = reserved_label[arg3 = 30];
                  else if (s0[1]) {
                    cimglist_for(variable_def,i) if (!std::strcmp(s0,variable_def[i])) {
                      arg1 = variable_pos[i]; arg2 = i; break;
                    }
                  } else arg1 = reserved_label[arg3 = *s0];

                  if (arg1!=~0U) {
                    if (arg2==~0U) { if (arg3!=~0U) reserved_label[arg3] = ~0U; }
                    else {
                      variable_def.remove(arg2);
                      if (arg2<variable_pos._width - 1)
                        std::memmove(variable_pos._data + arg2,variable_pos._data + arg2 + 1,
                                     sizeof(uintT)*(variable_pos._width - arg2 - 1));
                      --variable_pos._width;
                    }
                  }
                  *s1 = c1;
                } else compile(s0,s1,depth1,0,is_single);
              }
              _cimg_mp_return(arg1!=~0U?arg1:_cimg_mp_slot_nan);
            }

            if (!std::strncmp(ss,"uppercase(",10)) {
              _cimg_mp_op("Function 'uppercase()'");
              arg1 = compile(ss + 10,se1,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg1)) _cimg_mp_vector1_v(mp_uppercase,arg1);
              if (_cimg_mp_is_constant(arg1)) _cimg_mp_constant(cimg::uppercase(mem[arg1]));
              _cimg_mp_scalar1(mp_uppercase,arg1);
            }
            break;

          case 'v' :
            if ((cimg_sscanf(ss,"vector%u%c",&(arg1=~0U),&sep)==2 && sep=='(' && arg1>0) ||
                !std::strncmp(ss,"vector(",7) ||
                (!std::strncmp(ss,"vector",6) && ss7<se1 && (s=std::strchr(ss7,'('))!=0)) {
              _cimg_mp_op("Function 'vector()'");
              arg2 = 0;
              if (arg1==~0U && *ss6!='(') {
                arg1 = compile(ss6,s++,depth1,0,is_single);
                _cimg_mp_check_constant(arg1,0,3);
                arg1 = (unsigned int)mem[arg1];
              } else s = std::strchr(ss6,'(') + 1;

              if (arg1==~0U && *s=='#') {
                s0 = ++s; while (s0<se1 && (*s0!=',' || level[s0 - expr._data]!=clevel1)) ++s0;
                arg1 = compile(s,s0++,depth1,0,is_single);
                _cimg_mp_check_constant(arg1,1,3);
                arg1 = (unsigned int)mem[arg1];
                s = s0;
              }

              if (s<se1 || arg1==~0U) for ( ; s<se; ++s) {
                  ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                                 (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                  arg3 = compile(s,ns,depth1,0,is_single);
                  if (_cimg_mp_is_vector(arg3)) {
                    arg4 = _cimg_mp_size(arg3);
                    CImg<ulongT>::sequence(arg4,arg3 + 1,arg3 + arg4).move_to(l_opcode);
                    arg2+=arg4;
                  } else { CImg<ulongT>::vector(arg3).move_to(l_opcode); ++arg2; }
                  s = ns;
                }
              if (arg1==~0U) arg1 = arg2;
              if (!arg1) _cimg_mp_return(0);
              pos = vector(arg1);
              l_opcode.insert(CImg<ulongT>::vector((ulongT)mp_vector_init,pos,0,arg1),0);
              (l_opcode>'y').move_to(opcode);
              opcode[2] = opcode._height;
              opcode.move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"vtos(",5)) {
              _cimg_mp_op("Function 'vtos()'");
              s1 = ss5; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss5,s1,depth1,0,is_single);
              arg2 = 0; arg3 = ~0U;
              if (s1<se1) {
                s2 = s1 + 1; while (s2<se1 && (*s2!=',' || level[s2 - expr._data]!=clevel1)) ++s2;
                arg2 = compile(++s1,s2,depth1,0,is_single);
                arg3 = s2<se1?compile(++s2,se1,depth1,0,is_single):~0U;
              }
              _cimg_mp_check_type(arg2,2,1,0);
              if (arg3==~0U) {
                p1 = _cimg_mp_size(arg1);
                p1 = p1?22*p1 - 1:18;
              } else {
                _cimg_mp_check_constant(arg3,3,3);
                p1 = (unsigned int)mem[arg3];
              }
              pos = vector(p1);
              CImg<ulongT>::vector((ulongT)mp_vtos,pos,p1,arg1,_cimg_mp_size(arg1),arg2).move_to(code);
              _cimg_mp_return(pos);
            }
            break;

          case 'w' :
            if (*ss1=='(') {
              _cimg_mp_op("Function 'w()'");
              if (*ss2=='#') {
                p1 = compile(ss3,se1,depth1,0,is_single);
                _cimg_mp_check_list(false);
              } else { if (ss2!=se1) break; p1 = ~0U; }
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_image_w,pos,p1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (*ss1=='h' && *ss2=='(') {
              _cimg_mp_op("Function 'wh()'");
              if (*ss3=='#') {
                p1 = compile(ss4,se1,depth1,0,is_single);
                _cimg_mp_check_list(false);
              } else { if (ss3!=se1) break; p1 = ~0U; }
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_image_wh,pos,p1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (*ss1=='h' && *ss2=='d' && *ss3=='(') {
              _cimg_mp_op("Function 'whd()'");
              if (*ss4=='#') {
                p1 = compile(ss5,se1,depth1,0,is_single);
                _cimg_mp_check_list(false);
              } else { if (ss4!=se1) break; p1 = ~0U; }
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_image_whd,pos,p1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (*ss1=='h' && *ss2=='d' && *ss3=='s' && *ss4=='(') {
              _cimg_mp_op("Function 'whds()'");
              if (*ss5=='#') {
                p1 = compile(ss6,se1,depth1,0,is_single);
                _cimg_mp_check_list(false);
              } else { if (ss5!=se1) break; p1 = ~0U; }
              pos = scalar();
              CImg<ulongT>::vector((ulongT)mp_image_whds,pos,p1).move_to(code);
              _cimg_mp_return(pos);
            }

            if (!std::strncmp(ss,"while(",6)) {
              _cimg_mp_op("Function 'while()'");
              s0 = *ss5=='('?ss6:ss8;
              s1 = s0; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              p1 = code._width;
              arg1 = compile(s0,s1,depth1,0,is_single);
              p2 = code._width;
              arg6 = mempos;
              pos = compile(++s1,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg1,1,1,0);
              arg2 = _cimg_mp_size(pos);
              CImg<ulongT>::vector((ulongT)mp_while,pos,arg1,p2 - p1,code._width - p2,arg2,
                                   pos>=arg6 && !_cimg_mp_is_constant(pos),
                                   arg1>=arg6 && !_cimg_mp_is_constant(arg1)).move_to(code,p1);
              _cimg_mp_return(pos);
            }
            break;

          case 'x' :
            if (!std::strncmp(ss,"xor(",4)) {
              _cimg_mp_op("Function 'xor()'");
              s1 = ss4; while (s1<se1 && (*s1!=',' || level[s1 - expr._data]!=clevel1)) ++s1;
              arg1 = compile(ss4,s1,depth1,0,is_single);
              arg2 = compile(++s1,se1,depth1,0,is_single);
              _cimg_mp_check_type(arg2,2,3,_cimg_mp_size(arg1));
              if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_vv(mp_bitwise_xor,arg1,arg2);
              if (_cimg_mp_is_vector(arg1) && _cimg_mp_is_scalar(arg2)) _cimg_mp_vector2_vs(mp_bitwise_xor,arg1,arg2);
              if (_cimg_mp_is_scalar(arg1) && _cimg_mp_is_vector(arg2)) _cimg_mp_vector2_sv(mp_bitwise_xor,arg1,arg2);
              if (_cimg_mp_is_constant(arg1) && _cimg_mp_is_constant(arg2))
                _cimg_mp_constant((longT)mem[arg1] ^ (longT)mem[arg2]);
              _cimg_mp_scalar2(mp_bitwise_xor,arg1,arg2);
            }
            break;
          }

          if (!std::strncmp(ss,"min(",4) || !std::strncmp(ss,"max(",4) ||
              !std::strncmp(ss,"med(",4) || !std::strncmp(ss,"kth(",4) ||
              !std::strncmp(ss,"sum(",4) || !std::strncmp(ss,"avg(",4) ||
              !std::strncmp(ss,"std(",4) || !std::strncmp(ss,"var(",4) ||
              !std::strncmp(ss,"prod(",5) ||
              !std::strncmp(ss,"argmin(",7) || !std::strncmp(ss,"argmax(",7) ||
              !std::strncmp(ss,"argkth(",7)) {
            _cimg_mp_op(*ss=='a'?(ss[1]=='v'?"Function 'avg()'":
                                  ss[3]=='k'?"Function 'argkth()'":
                                  ss[4]=='i'?"Function 'argmin()'":
                                  "Function 'argmax()'"):
                        *ss=='s'?(ss[1]=='u'?"Function 'sum()'":"Function 'std()'"):
                        *ss=='k'?"Function 'kth()'":
                        *ss=='p'?"Function 'prod()'":
                        *ss=='v'?"Function 'var()'":
                        ss[1]=='i'?"Function 'min()'":
                        ss[1]=='a'?"Function 'max()'":"Function 'med()'");
            op = *ss=='a'?(ss[1]=='v'?mp_avg:ss[3]=='k'?mp_argkth:ss[4]=='i'?mp_argmin:mp_argmax):
              *ss=='s'?(ss[1]=='u'?mp_sum:mp_std):
              *ss=='k'?mp_kth:
              *ss=='p'?mp_prod:
              *ss=='v'?mp_var:
              ss[1]=='i'?mp_min:
              ss[1]=='a'?mp_max:
              ss[2]=='a'?mp_avg:
              mp_median;
            is_sth = true;
            pos = scalar();
            CImg<ulongT>::vector((ulongT)op,pos,0).move_to(l_opcode);
            for (s = std::strchr(ss,'(') + 1; s<se; ++s) {
              ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                             (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
              arg2 = compile(s,ns,depth1,0,is_single);
              if (_cimg_mp_is_vector(arg2))
                CImg<ulongT>::sequence(_cimg_mp_size(arg2),arg2 + 1,
                                       arg2 + (ulongT)_cimg_mp_size(arg2)).
                  move_to(l_opcode);
              else CImg<ulongT>::vector(arg2).move_to(l_opcode);
              is_sth&=_cimg_mp_is_constant(arg2);
              s = ns;
            }
            (l_opcode>'y').move_to(opcode);
            opcode[2] = opcode._height;
            if (is_sth) _cimg_mp_constant(op(*this));
            opcode.move_to(code);
            _cimg_mp_return(pos);
          }


          s0 = strchr(ss,'(');
          if (s0) {
            variable_name.assign(ss,(unsigned int)(s0 - ss + 1)).back() = 0;


            p1 = 0;
            for (s = s0 + 1; s<=se1; ++p1, s = ns + 1) {
              while (*s && cimg::is_blank(*s)) ++s;
              if (*s==')' && !p1) break;
              ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                             (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
            }

            arg3 = 0;
            cimglist_for(macro_def,l) if (!std::strcmp(macro_def[l],variable_name) && ++arg3 &&
                                          macro_def[l].back()==(char)p1) {
              p2 = (unsigned int)macro_def[l].back();
              CImg<charT> _expr = macro_body[l];

              p1 = 1;
              for (s = s0 + 1; s<=se1; ++p1, s = ns + 1) {
                while (*s && cimg::is_blank(*s)) ++s;
                if (*s==')' && p1==1) break;
                if (p1>p2) { ++p1; break; }
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=')' || level[ns - expr._data]!=clevel)) ++ns;
                variable_name.assign(s,(unsigned int)(ns - s + 1)).back() = 0;
                arg2 = 0;
                cimg_forX(_expr,k) {
                  if (_expr[k]==(char)p1) {
                    arg1 = _expr._width;
                    _expr.resize(arg1 + variable_name._width - 2,1,1,1,0);
                    std::memmove(_expr._data + k + variable_name._width - 1,_expr._data + k + 1,arg1 - k - 1);
                    std::memcpy(_expr._data + k,variable_name,variable_name._width - 1);
                    k+=variable_name._width - 2;
                  }
                  ++arg2;
                }
              }


              CImg<charT> _pexpr(_expr._width);
              ns = _pexpr._data;
              for (ps = _expr._data, c1 = ' '; *ps; ++ps) {
                if (!cimg::is_blank(*ps)) c1 = *ps;
                *(ns++) = c1;
              }
              *ns = 0;

              CImg<uintT> _level = get_level(_expr);
              expr.swap(_expr);
              pexpr.swap(_pexpr);
              level.swap(_level);
              s0 = user_macro;
              user_macro = macro_def[l];
              pos = compile(expr._data,expr._data + expr._width - 1,depth1,p_ref,is_single);
              user_macro = s0;
              level.swap(_level);
              pexpr.swap(_pexpr);
              expr.swap(_expr);
              _cimg_mp_return(pos);
            }

            if (arg3) {
              CImg<uintT> sig_nargs(arg3);
              arg1 = 0;
              cimglist_for(macro_def,l) if (!std::strcmp(macro_def[l],variable_name))
                sig_nargs[arg1++] = (unsigned int)macro_def[l].back();
              *se = saved_char;
              cimg::strellipsize(variable_name,64);
              s0 = ss - 4>expr._data?ss - 4:expr._data;
              cimg::strellipsize(s0,64);
              if (sig_nargs._width>1) {
                sig_nargs.sort();
                arg1 = sig_nargs.back();
                --sig_nargs._width;
                throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                            "CImg<%s>::%s: Function '%s()': Number of specified arguments (%u) "
                                            "does not match macro declaration (defined for %s or %u arguments), "
                                            "in expression '%s%s%s'.",
                                            pixel_type(),_cimg_mp_calling_function,variable_name._data,
                                            p1,sig_nargs.value_string()._data,arg1,
                                            s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
              } else
                throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                            "CImg<%s>::%s: Function '%s()': Number of specified arguments (%u) "
                                            "does not match macro declaration (defined for %u argument%s), "
                                            "in expression '%s%s%s'.",
                                            pixel_type(),_cimg_mp_calling_function,variable_name._data,
                                            p1,*sig_nargs,*sig_nargs!=1?"s":"",
                                            s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
            }
          }
        }


        if (*se1=='\'' &&
            ((se1>ss && *ss=='\'') ||
            (se1>ss1 && *ss=='_' && *ss1=='\''))) {
          if (*ss=='_') { _cimg_mp_op("Char initializer"); s1 = ss2; }
          else { _cimg_mp_op("String initializer"); s1 = ss1; }
          arg1 = (unsigned int)(se1 - s1);
          if (arg1) {
            CImg<charT>(s1,arg1 + 1).move_to(variable_name).back() = 0;
            cimg::strunescape(variable_name);
            arg1 = (unsigned int)std::strlen(variable_name);
          }
          if (!arg1) _cimg_mp_return(0);
          if (*ss=='_') {
            if (arg1==1) _cimg_mp_constant(*variable_name);
            *se = saved_char;
            cimg::strellipsize(variable_name,64);
            s0 = ss - 4>expr._data?ss - 4:expr._data;
            cimg::strellipsize(s0,64);
            throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                        "CImg<%s>::%s: %s: Literal %s contains more than one character, "
                                        "in expression '%s%s%s'.",
                                        pixel_type(),_cimg_mp_calling_function,s_op,
                                        ss1,
                                        s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
          }
          pos = vector(arg1);
          CImg<ulongT>::vector((ulongT)mp_string_init,pos,arg1).move_to(l_opcode);
          CImg<ulongT>(1,arg1/sizeof(ulongT) + (arg1%sizeof(ulongT)?1:0)).move_to(l_opcode);
          std::memcpy((char*)l_opcode[1]._data,variable_name,arg1);
          (l_opcode>'y').move_to(code);
          _cimg_mp_return(pos);
        }


        if (*ss=='[' && *se1==']') {
          _cimg_mp_op("Vector initializer");
          s1 = ss1; while (s1<se2 && cimg::is_blank(*s1)) ++s1;
          s2 = se2; while (s2>s1 && cimg::is_blank(*s2)) --s2;
          if (s2>s1 && *s1=='\'' && *s2=='\'') {
            arg1 = (unsigned int)(s2 - s1 - 1);
            if (arg1) {
              CImg<charT>(s1 + 1,arg1 + 1).move_to(variable_name).back() = 0;
              cimg::strunescape(variable_name);
              arg1 = (unsigned int)std::strlen(variable_name);
            }
            if (!arg1) _cimg_mp_return(0);
            pos = vector(arg1);
            CImg<ulongT>::vector((ulongT)mp_string_init,pos,arg1).move_to(l_opcode);
            CImg<ulongT>(1,arg1/sizeof(ulongT) + (arg1%sizeof(ulongT)?1:0)).move_to(l_opcode);
            std::memcpy((char*)l_opcode[1]._data,variable_name,arg1);
            (l_opcode>'y').move_to(code);
          } else {
            arg1 = 0;
            if (*ss1!=']') for (s = ss1; s<se; ++s) {
                ns = s; while (ns<se && (*ns!=',' || level[ns - expr._data]!=clevel1) &&
                               (*ns!=']' || level[ns - expr._data]!=clevel)) ++ns;
                arg2 = compile(s,ns,depth1,0,is_single);
                if (_cimg_mp_is_vector(arg2)) {
                  arg3 = _cimg_mp_size(arg2);
                  CImg<ulongT>::sequence(arg3,arg2 + 1,arg2 + arg3).move_to(l_opcode);
                  arg1+=arg3;
                } else { CImg<ulongT>::vector(arg2).move_to(l_opcode); ++arg1; }
                s = ns;
              }
            if (!arg1) _cimg_mp_return(0);
            pos = vector(arg1);
            l_opcode.insert(CImg<ulongT>::vector((ulongT)mp_vector_init,pos,0,arg1),0);
            (l_opcode>'y').move_to(opcode);
            opcode[2] = opcode._height;
            opcode.move_to(code);
          }
          _cimg_mp_return(pos);
        }


        if (*ss1=='#' && ss2<se) {
          arg1 = compile(ss2,se,depth1,0,is_single);
          p1 = (unsigned int)(listin._width && _cimg_mp_is_constant(arg1)?cimg::mod((int)mem[arg1],listin.width()):~0U);
          switch (*ss) {
          case 'w' :
            if (!listin) _cimg_mp_return(0);
            if (p1!=~0U) _cimg_mp_constant(listin[p1]._width);
            _cimg_mp_scalar1(mp_list_width,arg1);
          case 'h' :
            if (!listin) _cimg_mp_return(0);
            if (p1!=~0U) _cimg_mp_constant(listin[p1]._height);
            _cimg_mp_scalar1(mp_list_height,arg1);
          case 'd' :
            if (!listin) _cimg_mp_return(0);
            if (p1!=~0U) _cimg_mp_constant(listin[p1]._depth);
            _cimg_mp_scalar1(mp_list_depth,arg1);
          case 'r' :
            if (!listin) _cimg_mp_return(0);
            if (p1!=~0U) _cimg_mp_constant(listin[p1]._is_shared);
            _cimg_mp_scalar1(mp_list_is_shared,arg1);
          case 's' :
            if (!listin) _cimg_mp_return(0);
            if (p1!=~0U) _cimg_mp_constant(listin[p1]._spectrum);
            _cimg_mp_scalar1(mp_list_spectrum,arg1);
          case 'i' :
            if (!listin) _cimg_mp_return(0);
            _cimg_mp_scalar7(mp_list_ixyzc,arg1,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,_cimg_mp_slot_c,
                             0,_cimg_mp_boundary);
          case 'I' :
            p2 = p1!=~0U?listin[p1]._spectrum:listin._width?~0U:0;
            if (!p2) _cimg_mp_return(0);
            pos = vector(p2);
            CImg<ulongT>::vector((ulongT)mp_list_Joff,pos,p1,0,0,p2).move_to(code);
            _cimg_mp_return(pos);
          case 'R' :
            if (!listin) _cimg_mp_return(0);
            _cimg_mp_scalar7(mp_list_ixyzc,arg1,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,0,
                             0,_cimg_mp_boundary);
          case 'G' :
            if (!listin) _cimg_mp_return(0);
            _cimg_mp_scalar7(mp_list_ixyzc,arg1,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,1,
                             0,_cimg_mp_boundary);
          case 'B' :
            if (!listin) _cimg_mp_return(0);
            _cimg_mp_scalar7(mp_list_ixyzc,arg1,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,2,
                             0,_cimg_mp_boundary);
          case 'A' :
            if (!listin) _cimg_mp_return(0);
            _cimg_mp_scalar7(mp_list_ixyzc,arg1,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,3,
                             0,_cimg_mp_boundary);
          }
        }

        if (*ss1 && *ss2=='#' && ss3<se) {
          arg1 = compile(ss3,se,depth1,0,is_single);
          p1 = (unsigned int)(listin._width && _cimg_mp_is_constant(arg1)?cimg::mod((int)mem[arg1],listin.width()):~0U);
          if (*ss=='w' && *ss1=='h') {
            if (!listin) _cimg_mp_return(0);
            if (p1!=~0U) _cimg_mp_constant(listin[p1]._width*listin[p1]._height);
            _cimg_mp_scalar1(mp_list_wh,arg1);
          }
          arg2 = ~0U;

          if (*ss=='i') {
            if (*ss1=='c') {
              if (!listin) _cimg_mp_return(0);
              if (_cimg_mp_is_constant(arg1)) {
                if (!list_median) list_median.assign(listin._width);
                if (!list_median[p1]) CImg<doubleT>::vector(listin[p1].median()).move_to(list_median[p1]);
                _cimg_mp_constant(*list_median[p1]);
              }
              _cimg_mp_scalar1(mp_list_median,arg1);
            }
            if (*ss1>='0' && *ss1<='9') {
              if (!listin) _cimg_mp_return(0);
              _cimg_mp_scalar7(mp_list_ixyzc,arg1,_cimg_mp_slot_x,_cimg_mp_slot_y,_cimg_mp_slot_z,*ss1 - '0',
                               0,_cimg_mp_boundary);
            }
            switch (*ss1) {
            case 'm' : arg2 = 0; break;
            case 'M' : arg2 = 1; break;
            case 'a' : arg2 = 2; break;
            case 'v' : arg2 = 3; break;
            case 's' : arg2 = 12; break;
            case 'p' : arg2 = 13; break;
            }
          } else if (*ss1=='m') switch (*ss) {
            case 'x' : arg2 = 4; break;
            case 'y' : arg2 = 5; break;
            case 'z' : arg2 = 6; break;
            case 'c' : arg2 = 7; break;
            } else if (*ss1=='M') switch (*ss) {
            case 'x' : arg2 = 8; break;
            case 'y' : arg2 = 9; break;
            case 'z' : arg2 = 10; break;
            case 'c' : arg2 = 11; break;
            }
          if (arg2!=~0U) {
            if (!listin) _cimg_mp_return(0);
            if (_cimg_mp_is_constant(arg1)) {
              if (!list_stats) list_stats.assign(listin._width);
              if (!list_stats[p1]) list_stats[p1].assign(1,14,1,1,0).fill(listin[p1].get_stats(),false);
              _cimg_mp_constant(list_stats(p1,arg2));
            }
            _cimg_mp_scalar2(mp_list_stats,arg1,arg2);
          }
        }

        if (*ss=='w' && *ss1=='h' && *ss2=='d' && *ss3=='#' && ss4<se) {
          arg1 = compile(ss4,se,depth1,0,is_single);
          if (!listin) _cimg_mp_return(0);
          p1 = (unsigned int)(_cimg_mp_is_constant(arg1)?cimg::mod((int)mem[arg1],listin.width()):~0U);
          if (p1!=~0U) _cimg_mp_constant(listin[p1]._width*listin[p1]._height*listin[p1]._depth);
          _cimg_mp_scalar1(mp_list_whd,arg1);
        }
        if (*ss=='w' && *ss1=='h' && *ss2=='d' && *ss3=='s' && *ss4=='#' && ss5<se) {
          arg1 = compile(ss5,se,depth1,0,is_single);
          if (!listin) _cimg_mp_return(0);
          p1 = (unsigned int)(_cimg_mp_is_constant(arg1)?cimg::mod((int)mem[arg1],listin.width()):~0U);
          if (p1!=~0U) _cimg_mp_constant(listin[p1]._width*listin[p1]._height*listin[p1]._depth*listin[p1]._spectrum);
          _cimg_mp_scalar1(mp_list_whds,arg1);
        }

        if (!std::strcmp(ss,"interpolation")) _cimg_mp_return(_cimg_mp_interpolation);
        if (!std::strcmp(ss,"boundary")) _cimg_mp_return(_cimg_mp_boundary);


        variable_name.assign(ss,(unsigned int)(se - ss + 1)).back() = 0;
        if (variable_name[1]) {
          cimglist_for(variable_def,i) if (!std::strcmp(variable_name,variable_def[i]))
            _cimg_mp_return(variable_pos[i]);
        } else if (reserved_label[(int)*variable_name]!=~0U)
          _cimg_mp_return(reserved_label[(int)*variable_name]);


        is_sth = true;
        if (*variable_name>='0' && *variable_name<='9') is_sth = false;
        else for (ns = variable_name._data; *ns; ++ns)
               if (!is_varchar(*ns)) { is_sth = false; break; }

        *se = saved_char;
        c1 = *se1;
        cimg::strellipsize(variable_name,64);
        s0 = ss - 4>expr._data?ss - 4:expr._data;
        cimg::strellipsize(s0,64);
        if (is_sth)
          throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                      "CImg<%s>::%s: Undefined variable '%s' in expression '%s%s%s'.",
                                      pixel_type(),_cimg_mp_calling_function,
                                      variable_name._data,
                                      s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
        s1 = std::strchr(ss,'(');
        s_op = s1 && c1==')'?"function call":"item";
        throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                    "CImg<%s>::%s: Unrecognized %s '%s' in expression '%s%s%s'.",
                                    pixel_type(),_cimg_mp_calling_function,
                                    s_op,variable_name._data,
                                    s0!=expr._data?"...":"",s0,se<&expr.back()?"...":"");
}
