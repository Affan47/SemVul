Diff16bitUnFilter(armcpu_t* cpu)
{
  u32 source,dest,header;
  u16 data;
  int len;

  source = cpu->R[0];
  dest = cpu->R[1];

  header = MMU_read8(cpu->proc_ID, source);
  source += 4;

  if(((source & 0xe000000) == 0) ||
     ((source + ((header >> 8) & 0x1fffff)) & 0xe000000) == 0)
    return 0;

  len = header >> 8;

  data = MMU_read16(cpu->proc_ID, source);
  source += 2;
  MMU_write16(cpu->proc_ID, dest, data);
  dest += 2;
  len -= 2;

  while(len >= 2) {
    u16 diff = MMU_read16(cpu->proc_ID, source);
    source += 2;
    data += diff;
    MMU_write16(cpu->proc_ID, dest, data);
    dest += 2;
    len -= 2;
  }
  return 1;
}
