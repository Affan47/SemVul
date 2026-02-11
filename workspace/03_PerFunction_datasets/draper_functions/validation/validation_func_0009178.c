T1_SetBitmapPad( int pad)
{
  if (T1_Up){

    T1_errno=T1ERR_OP_NOT_PERMITTED;
    return(-1);
  }
  else{
    switch (pad){
    case 8:
      T1_pad=8;
      return(0);
    case 16:
      T1_pad=16;
      return(0);
#ifdef T1_AA_TYPE64
    case 32:
      T1_pad=32;
      return(0);
#endif
    default:
      T1_errno=T1ERR_INVALID_PARAMETER;
      return(-1);
    }
  }
}
