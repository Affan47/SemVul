sigblock(int mask){
  int oldmask = _real_sigblock( patchBSDMask(mask) );

  patchBSDUserMask(SIG_BLOCK, mask, &oldmask);

  return oldmask;
}
