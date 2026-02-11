pred16x16_plane_compat_c(uint8_t *src, int stride, const int svq3, const int rv40){
  int i, j, k;
  int a;
  uint8_t *cm = ff_cropTbl + MAX_NEG_CROP;
  const uint8_t * const src0 = src+7-stride;
  const uint8_t *src1 = src+8*stride-1;
  const uint8_t *src2 = src1-2*stride;
  int H = src0[1] - src0[-1];
  int V = src1[0] - src2[ 0];
  for(k=2; k<=8; ++k) {
    src1 += stride; src2 -= stride;
    H += k*(src0[k] - src0[-k]);
    V += k*(src1[0] - src2[ 0]);
  }
  if(svq3){
    H = ( 5*(H/4) ) / 16;
    V = ( 5*(V/4) ) / 16;


    i = H; H = V; V = i;
  }else if(rv40){
    H = ( H + (H>>2) ) >> 4;
    V = ( V + (V>>2) ) >> 4;
  }else{
    H = ( 5*H+32 ) >> 6;
    V = ( 5*V+32 ) >> 6;
  }

  a = 16*(src1[0] + src2[16] + 1) - 7*(V+H);
  for(j=16; j>0; --j) {
    int b = a;
    a += V;
    for(i=-16; i<0; i+=4) {
      src[16+i] = cm[ (b    ) >> 5 ];
      src[17+i] = cm[ (b+  H) >> 5 ];
      src[18+i] = cm[ (b+2*H) >> 5 ];
      src[19+i] = cm[ (b+3*H) >> 5 ];
      b += 4*H;
    }
    src += stride;
  }
}
