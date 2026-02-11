format_vpiVectorVal(vvp_fun_signal_vec*sig, int base, unsigned wid,
                                s_vpi_value*vp)
{
      long end = base + (signed)wid;
      unsigned int obit = 0;
      unsigned hwid = (wid - 1)/32 + 1;

      s_vpi_vecval *op = (p_vpi_vecval)
                         need_result_buf(hwid * sizeof(s_vpi_vecval), RBUF_VAL);
      vp->value.vector = op;

      op->aval = op->bval = 0;
      for (long idx = base ;  idx < end ;  idx += 1) {
	    if (base >= 0 && base < (signed)sig->size()) {
		switch (sig->value(idx)) {
		case BIT4_0:
		  op->aval &= ~(1 << obit);
		  op->bval &= ~(1 << obit);
		  break;
		case BIT4_1:
		  op->aval |= (1 << obit);
		  op->bval &= ~(1 << obit);
		  break;
		case BIT4_X:
		  op->aval |= (1 << obit);
		  op->bval |= (1 << obit);
		  break;
		case BIT4_Z:
		  op->aval &= ~(1 << obit);
		  op->bval |= (1 << obit);
		  break;
		}
	    } else {
		  op->aval |= (1 << obit);
		  op->bval |= (1 << obit);
	    }

	    obit++;
	    if (!(obit % 32)) {
		  op += 1;
		  if ((op - vp->value.vector) < (ptrdiff_t)hwid)
			op->aval = op->bval = 0;
		  obit = 0;
	    }
      }
}
