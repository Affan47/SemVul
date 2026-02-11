invalid_word_e(const Language & l,
                                     ParmStr word,
                                     const char * msg,
                                     char chr = 0)
  {
    char m[200];
    if (chr) {


      snprintf(m, 200, (char *)msg, MsgConv(l)(chr), l.to_uni(chr));
      msg = m;
    }
    return make_err(invalid_word, MsgConv(l)(word), msg);
  }
