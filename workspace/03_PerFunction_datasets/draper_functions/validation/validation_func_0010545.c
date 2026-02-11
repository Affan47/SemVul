ull_to_number(unsigned long long n, ikpcb* pcb) {
  if (((unsigned long long)(unsigned long) n) == n) {
    return u_to_number(n, pcb);
  }
  ikptr bn = ik_safe_alloc(pcb, align(disp_bignum_data+sizeof(long long)));
  bcopy((char*)(&n), (char*)(bn+disp_bignum_data), sizeof(long long));
  return normalize_bignum(sizeof(long long)/sizeof(mp_limb_t), 0, bn);
}
