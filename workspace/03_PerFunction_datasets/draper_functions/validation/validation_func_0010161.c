thumb_set_return_address (rtx source, rtx scratch)
{
  arm_stack_offsets *offsets;
  HOST_WIDE_INT delta;
  HOST_WIDE_INT limit;
  int reg;
  rtx addr;
  unsigned long mask;

  emit_use (source);

  offsets = arm_get_frame_offsets ();
  mask = offsets->saved_regs_mask;
  if (mask & (1 << LR_REGNUM))
    {
      limit = 1024;

      if (frame_pointer_needed)
	{
	  delta = offsets->soft_frame - offsets->saved_args;
	  reg = THUMB_HARD_FRAME_POINTER_REGNUM;
	  if (TARGET_THUMB1)
	    limit = 128;
	}
      else
	{
	  delta = offsets->outgoing_args - offsets->saved_args;
	  reg = SP_REGNUM;
	}

      if (TARGET_THUMB1 && TARGET_BACKTRACE)
	delta -= 16;

      delta -= 4;


      addr = gen_rtx_REG (SImode, reg);
      if (delta > limit)
	{
	  emit_insn (gen_movsi (scratch, GEN_INT (delta)));
	  emit_insn (gen_addsi3 (scratch, scratch, stack_pointer_rtx));
	  addr = scratch;
	}
      else
	addr = plus_constant (addr, delta);

      emit_move_insn (gen_frame_mem (Pmode, addr), source);
    }
  else
    emit_move_insn (gen_rtx_REG (Pmode, LR_REGNUM), source);
}
