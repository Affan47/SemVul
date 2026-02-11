LSL_GvEw(bxInstruction_c *i)
{

  Bit16u raw_selector;
  Bit32u limit32;
  bx_selector_t selector;
  Bit32u dword1, dword2;
#if BX_SUPPORT_X86_64
  Bit32u dword3 = 0;
#endif

  if (real_mode() || v8086_mode()) {
    BX_ERROR(("LSL: not recognized in real or virtual-8086 mode"));
    exception(BX_UD_EXCEPTION, 0, 0);
  }

  if (i->modC0()) {
    raw_selector = BX_READ_16BIT_REG(i->rm());
  }
  else {
    bx_address eaddr = BX_CPU_CALL_METHODR(i->ResolveModrm, (i));

    raw_selector = read_virtual_word(i->seg(), eaddr);
  }


  if ((raw_selector & 0xfffc) == 0) {
    clear_ZF();
    return;
  }

  parse_selector(raw_selector, &selector);

  if (!fetch_raw_descriptor2(&selector, &dword1, &dword2)) {
    BX_DEBUG(("LSL: failed to fetch descriptor"));
    clear_ZF();
    return;
  }

  Bit32u descriptor_dpl = (dword2 >> 13) & 0x03;

  if ((dword2 & 0x00001000) == 0) {
    Bit32u type = (dword2 >> 8) & 0x0000000f;
    switch (type) {
      case BX_SYS_SEGMENT_AVAIL_286_TSS:
      case BX_SYS_SEGMENT_BUSY_286_TSS:
        if (long_mode()) {
          clear_ZF();
          return;
        }

      case BX_SYS_SEGMENT_LDT:
      case BX_SYS_SEGMENT_AVAIL_386_TSS:
      case BX_SYS_SEGMENT_BUSY_386_TSS:
#if BX_SUPPORT_X86_64
        if (BX_CPU_THIS_PTR cpu_mode == BX_MODE_LONG_64) {
          if (!fetch_raw_descriptor2_64(&selector, &dword1, &dword2, &dword3)) {
            BX_ERROR(("LSL: failed to fetch 64-bit descriptor"));
            clear_ZF();
            return;
          }
        }
#endif
        if (descriptor_dpl < CPL || descriptor_dpl < selector.rpl) {
          clear_ZF();
          return;
        }
        limit32 = (dword1 & 0x0000ffff) | (dword2 & 0x000f0000);
        if (dword2 & 0x00800000)
          limit32 = (limit32 << 12) | 0x00000fff;
        break;
      default:
        clear_ZF();
        return;
    }
  }
  else {
    limit32 = (dword1 & 0x0000ffff) | (dword2 & 0x000f0000);
    if (dword2 & 0x00800000)
      limit32 = (limit32 << 12) | 0x00000fff;
    if ((dword2 & 0x00000c00) != 0x00000c00) {

      if (descriptor_dpl < CPL || descriptor_dpl < selector.rpl) {
        clear_ZF();
        return;
      }
    }
  }


  assert_ZF();

  if (i->os32L()) {
    BX_WRITE_32BIT_REGZ(i->nnn(), limit32);
  }
  else {

    BX_WRITE_16BIT_REG(i->nnn(), (Bit16u) limit32);
  }
}
