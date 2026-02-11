nes6502_getcontext (nes6502_context * cpu)
{
  int loop;


  for (loop = 0; loop < NES6502_NUMBANKS; loop++) {
    cpu->mem_page[loop] = nes6502_banks[loop];
#ifdef NES6502_MEM_ACCESS_CTRL
    cpu->acc_mem_page[loop] = acc_nes6502_banks[loop];
#endif
  }

  cpu->read_handler = pmem_read;
  cpu->write_handler = pmem_write;

  cpu->pc_reg = reg_PC;
  cpu->a_reg = reg_A;
  cpu->p_reg = reg_P;
  cpu->x_reg = reg_X;
  cpu->y_reg = reg_Y;
  cpu->s_reg = reg_S;
  cpu->int_pending = int_pending;
  cpu->dma_cycles = dma_cycles;
}
