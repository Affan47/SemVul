BufferPos(unsigned int num = 0) const {
    if(num == 0) return 0;
    if(addr_) {
      if(num == 1) return prefix_.length();
    } else {
      ++num;
    };
    if(num == 2) return (prefix_.length() + length_);
    return (prefix_.length() + length_ + postfix_.length());
  }
