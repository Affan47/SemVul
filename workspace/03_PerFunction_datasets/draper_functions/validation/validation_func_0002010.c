oc_pack_bytes_left(oc_pack_buf *_b){
  if(_b->eof)return -1;
  return _b->stop-_b->ptr+(_b->bits>>3);
}
