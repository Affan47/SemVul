
      CImg<uintT> get_level(CImg<charT>& expr) const {
        bool is_escaped = false, next_is_escaped = false;
        unsigned int mode = 0, next_mode = 0;
        CImg<uintT> res(expr._width - 1);
        unsigned int *pd = res._data;
        int level = 0;
        for (const char *ps = expr._data; *ps && level>=0; ++ps) {
          if (!is_escaped && !next_is_escaped && *ps=='\\') next_is_escaped = true;
          if (!is_escaped && *ps=='\'') {
            if (!mode && ps>expr._data && *(ps - 1)=='[') next_mode = mode = 2;
            else if (mode==2 && *(ps + 1)==']') next_mode = !mode;
            else if (mode<2) next_mode = mode?(mode = 0):1;
          }
          *(pd++) = (unsigned int)(mode>=1 || is_escaped?level + (mode==1):
                                   *ps=='(' || *ps=='['?level++:
                                   *ps==')' || *ps==']'?--level:
                                   level);
          mode = next_mode;
          is_escaped = next_is_escaped;
          next_is_escaped = false;
        }
        if (mode) {
          cimg::strellipsize(expr,64);
          throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                      "CImg<%s>::%s: Unterminated string literal, in expression '%s'.",
                                      pixel_type(),_cimg_mp_calling_function,
                                      expr._data);
        }
        if (level) {
          cimg::strellipsize(expr,64);
          throw CImgArgumentException("[" cimg_appname "_math_parser] "
                                      "CImg<%s>::%s: Unbalanced parentheses/brackets, in expression '%s'.",
                                      pixel_type(),_cimg_mp_calling_function,
                                      expr._data);
        }
        return res;
}
