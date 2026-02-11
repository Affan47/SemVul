gbmemory_init(void)
{


  memset(key,0,256);
  memset(oam_space,0,0xa0);
  memcpy(&himem[0x60],IOMem,0xff);

  DIVID=0x00;
  TIME_MOD=0x00;
  TIME_CONTROL=0x00;
  TIME_COUNTER=0x00;

  NR10=0x80;
  NR11=0xbf;
  NR12=0xf3;
  NR14=0xbf;
  NR21=0x3f;
  NR21=0x00;
  NR24=0xbf;
  NR30=0x7f;
  NR31=0xff;
  NR32=0x9f;
  NR33=0xbf;
  NR41=0xff;
  NR42=0x00;
  NR43=0x00;
  NR44=0xbf;
  NR50=0x77;
  NR51=0xf3;

  NR52=0xf1;

  CMP_LINE=0x00;
  INT_ENABLE=0x00;

  dma_info.type=NO_DMA;

  if (rom_type&MBC1) select_rom_page=mbc1_select_page;
  else if (rom_type&MBC2) select_rom_page=mbc2_select_page;
  else if (rom_type&MBC3) select_rom_page=mbc3_select_page;
  else if (rom_type&MBC5) select_rom_page=mbc5_select_page;
  else select_rom_page=select_default;

  gbmemory_reset();
}
