oc_mb_fill_cmapping01(oc_mb_map_plane _mb_map[3],
 const oc_fragment_plane _fplanes[3],int _xfrag0,int _yfrag0){
  ptrdiff_t fragi;
  int       j;
  _yfrag0>>=1;
  fragi=_yfrag0*(ptrdiff_t)_fplanes[1].nhfrags+_xfrag0;
  for(j=0;j<2;j++){
    _mb_map[1][j]=fragi+_fplanes[1].froffset;
    _mb_map[2][j]=fragi+_fplanes[2].froffset;
    fragi++;
  }
}
