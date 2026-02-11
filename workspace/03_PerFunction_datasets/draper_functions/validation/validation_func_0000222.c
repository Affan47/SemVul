fixnum_shft(fixnum x,fixnum y) {
  return y<0 ? ({register fixnum _q1=(fixnum_rshft(x,-y));register object _q4; _q4=(!(((_q1)+(0x4000000000000000>>1))&-0x4000000000000000)) ? ((object)((_q1)+(0x8000000000000000 +(0x4000000000000000>>1)))) : make_fixnum1(_q1);_q4;}) : fixnum_lshft(x,y);
}
