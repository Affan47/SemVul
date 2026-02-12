static Value make(const T &value) {
#ifdef __clang__
    Value result = MakeValue<Formatter>(value);


    (void)result.custom.format;
    return result;
#else
    return MakeValue<Formatter>(value);
#endif
  }
