oc_pack_look1(oc_pack_buf *_b){
  oc_pb_window window;
  int          available;
  window=_b->window;
  available=_b->bits;
  if(available<1)_b->window=window=oc_pack_refill(_b,1);
  return window>>OC_PB_WINDOW_SIZE-1;
}
