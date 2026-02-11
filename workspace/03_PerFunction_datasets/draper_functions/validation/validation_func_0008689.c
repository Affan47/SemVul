of_MOV_(vthread_t thr, vvp_code_t cp)
{


      thr_check_addr(thr, cp->bit_idx[0]+cp->number-1);
      thr_check_addr(thr, cp->bit_idx[1]+cp->number-1);

      vvp_vector4_t tmp (thr->bits4, cp->bit_idx[1], cp->number);

      thr->bits4.set_vec(cp->bit_idx[0], tmp);

      return true;
}
