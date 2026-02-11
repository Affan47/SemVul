jump_protected(bxInstruction_c *i, Bit16u cs_raw, bx_address disp)
{
  bx_descriptor_t  descriptor;
  bx_selector_t    selector;
  Bit32u dword1, dword2;


  if ((cs_raw & 0xfffc) == 0) {
    BX_ERROR(("jump_protected: cs == 0"));
    exception(BX_GP_EXCEPTION, 0, 0);
  }

  parse_selector(cs_raw, &selector);


  fetch_raw_descriptor(&selector, &dword1, &dword2, BX_GP_EXCEPTION);


  parse_descriptor(dword1, dword2, &descriptor);

  if (descriptor.segment) {
    check_cs(&descriptor, cs_raw, BX_SELECTOR_RPL(cs_raw), CPL);
    branch_far64(&selector, &descriptor, disp, CPL);
    return;
  }
  else {

    if (descriptor.dpl < CPL) {
      BX_ERROR(("jump_protected: call gate.dpl < CPL"));
      exception(BX_GP_EXCEPTION, cs_raw & 0xfffc, 0);
    }


    if (descriptor.dpl < selector.rpl) {
      BX_ERROR(("jump_protected: call gate.dpl < selector.rpl"));
      exception(BX_GP_EXCEPTION, cs_raw & 0xfffc, 0);
    }

#if BX_SUPPORT_X86_64
    if (long_mode()) {
      if (descriptor.type != BX_386_CALL_GATE) {
        BX_ERROR(("jump_protected: gate type %u unsupported in long mode", (unsigned) descriptor.type));
        exception(BX_GP_EXCEPTION, cs_raw & 0xfffc, 0);
      }
      jmp_call_gate64(&selector);
      return;
    }
#endif

    switch (descriptor.type) {
      case BX_SYS_SEGMENT_AVAIL_286_TSS:
      case BX_SYS_SEGMENT_AVAIL_386_TSS:

        if (descriptor.type==BX_SYS_SEGMENT_AVAIL_286_TSS)
          BX_DEBUG(("jump_protected: jump to 286 TSS"));
        else
          BX_DEBUG(("jump_protected: jump to 386 TSS"));


        task_switch(i, &selector, &descriptor, BX_TASK_FROM_JUMP, dword1, dword2);


        if (EIP > BX_CPU_THIS_PTR sregs[BX_SEG_REG_CS].cache.u.segment.limit_scaled) {
          BX_ERROR(("jump_protected: EIP not within CS limits"));
          exception(BX_GP_EXCEPTION, 0, 0);
        }
        return;

      case BX_TASK_GATE:
        task_gate(i, &selector, &descriptor, BX_TASK_FROM_JUMP);
        return;

      case BX_286_CALL_GATE:
      case BX_386_CALL_GATE:
        jmp_call_gate(&selector, &descriptor);
        return;

      default:
        BX_ERROR(("jump_protected: gate type %u unsupported", (unsigned) descriptor.type));
        exception(BX_GP_EXCEPTION, cs_raw & 0xfffc, 0);
    }
  }
}
