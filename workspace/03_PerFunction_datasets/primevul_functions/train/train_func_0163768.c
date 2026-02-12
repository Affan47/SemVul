
      CImg<boolT> is_inside_string(CImg<charT>& expr) const {
        bool is_escaped = false, next_is_escaped = false;
        unsigned int mode = 0, next_mode = 0;
        CImg<boolT> res = CImg<charT>::string(expr);
        bool *pd = res._data;
        for (const char *ps = expr._data; *ps; ++ps) {
          if (!next_is_escaped && *ps=='\\') next_is_escaped = true;
          if (!is_escaped && *ps=='\'') {
            if (!mode && ps>expr._data && *(ps - 1)=='[') next_mode = mode = 2;
            else if (mode==2 && *(ps + 1)==']') next_mode = !mode;
            else if (mode<2) next_mode = mode?(mode = 0):1;
          }
          *(pd++) = mode>=1 || is_escaped;
          mode = next_mode;
          is_escaped = next_is_escaped;
          next_is_escaped = false;
        }
        return res;
}
