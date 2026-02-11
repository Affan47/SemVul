rec_comp_prep(jit_State *J)
{

  if (J->cur.nsnap == 1 && J->cur.snap[0].ref == J->cur.nins)
    emitir_raw(IRT(IR_NOP, IRT_NIL), 0, 0);
  lj_snap_add(J);
}
