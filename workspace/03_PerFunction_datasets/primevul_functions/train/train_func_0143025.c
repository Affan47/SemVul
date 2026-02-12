void Inspect::operator()(Number_Ptr n)
  {

    std::string res;


    n->reduce();


    std::stringstream ss;
    ss.precision(12);
    ss << n->value();


    if (ss.str().find_first_of("e") != std::string::npos) {
      ss.clear(); ss.str(std::string());
      ss.precision(std::max(12, opt.precision));
      ss << std::fixed << n->value();
    }

    std::string tmp = ss.str();
    size_t pos_point = tmp.find_first_of(".,");
    size_t pos_fract = tmp.find_last_not_of("0");
    bool is_int = pos_point == pos_fract ||
                  pos_point == std::string::npos;


    ss.clear(); ss.str(std::string());


    if (is_int)
    {
      ss.precision(0);
      ss << std::fixed << n->value();
      res = std::string(ss.str());
    }

    else
    {

      if (pos_fract < opt.precision + pos_point)
      { ss.precision((int)(pos_fract - pos_point)); }
      else { ss.precision(opt.precision); }

      ss << std::fixed << n->value();
      res = std::string(ss.str());

      size_t pos = res.find_last_not_of("0");

      if (pos == std::string::npos) {
        res = "0.0";
      } else {
        bool at_dec_point = res[pos] == '.' ||
                            res[pos] == ',';

        if (at_dec_point) ++ pos;
        res.resize (pos + 1);
      }
    }


    if (res == "0.0") res = "0";
    else if (res == "") res = "0";
    else if (res == "-0") res = "0";
    else if (res == "-0.0") res = "0";
    else if (opt.output_style == COMPRESSED)
    {

      size_t off = res[0] == '-' ? 1 : 0;

      if (n->zero() && res[off] == '0' && res[off+1] == '.') res.erase(off, 1);
    }


    res += n->unit();


    append_token(res, n);
  }
