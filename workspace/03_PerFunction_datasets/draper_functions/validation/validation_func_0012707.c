predict() {
    U32 p1=m1.predict((ch(1) >> 5) + 8*(ch.pos(0, 3) < ch.pos(32, 3)));
    if (MEM>=MINMEM) {
      U32 p2=m2.predict((ch(1) >> 6)+4*(ch(2) >> 6));
      return (p1+p2)/2;
    }
    else
      return p1;
  }
