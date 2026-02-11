of_CMPIU(vthread_t thr, vvp_code_t cp)
{
      unsigned addr = cp->bit_idx[0];
      unsigned long imm  = cp->bit_idx[1];
      unsigned wid  = cp->number;

      unsigned long*array = vector_to_array(thr, addr, wid);


      if (array == 0)
	    return of_CMPIU_the_hard_way(thr, cp);

      unsigned words = (wid+CPU_WORD_BITS-1) / CPU_WORD_BITS;
      vvp_bit4_t eq  = BIT4_1;
      vvp_bit4_t lt  = BIT4_0;
      for (unsigned idx = 0 ; idx < words ; idx += 1, imm = 0UL) {
	    if (array[idx] == imm)
		  continue;

	    eq = BIT4_0;
	    lt = (array[idx] < imm) ? BIT4_1 : BIT4_0;
      }

      delete[]array;

      thr_put_bit(thr, 4, eq);
      thr_put_bit(thr, 5, lt);
      thr_put_bit(thr, 6, eq);
      return true;
}
