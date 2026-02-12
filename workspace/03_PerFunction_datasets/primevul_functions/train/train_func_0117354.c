void skipLabel()
  {
    uint8_t len;
    while((len=get8BitInt())) {
      if(len >= 0xc0) {
        get8BitInt();
        return;
      }
      skipBytes(len);
    }
  }
