emit(raw_ostream &o, unsigned int &i) {
      if (IsNumber)
        o << Number;
      else
        o << String;
    }
