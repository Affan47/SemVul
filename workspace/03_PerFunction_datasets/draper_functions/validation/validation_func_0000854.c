xxx(unsigned char code)
  { long hn,hw,hk,hk1;
    hk = (int) code-238;
    hw = (int) e_inbyte();
    for (hn=2; hn <= hk; hn++)
    { hk1 = (int) e_inbyte();
      hw = hw * 256 + (long) hk1;
    }
    skip(hw);
  }
