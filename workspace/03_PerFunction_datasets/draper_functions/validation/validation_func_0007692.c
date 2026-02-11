calculate_ip_mask(uint8_t prefix){
  int i;
  uint32_t mask = 0;
  if(prefix >= 32)
    return UINT_MAX;
  for( i = 0; i < prefix - 1; i++){
    mask = mask | 1;
    mask = mask << 1;
  }
  mask = mask | 1;
  mask = mask << (32 - prefix);
  return mask;
}
