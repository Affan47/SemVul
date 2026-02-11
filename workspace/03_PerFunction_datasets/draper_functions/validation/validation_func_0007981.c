BufNum() const {
    if (!h || !*h)
      return 1;
    return (*h)->BufNum();
  }
