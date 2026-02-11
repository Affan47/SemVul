jaguardsp_ctrl_w(int cpunum, offs_t offset, data32_t data, data32_t mem_mask)
{
	UINT32 			oldval, newval;

#if LOG_DSP_IO
	if (offset != D_FLAGS)
		logerror("%08X/%d:DSP write register @ F1A1%02X = %08X\n", activecpu_get_previouspc(), cpu_getactivecpu(), offset * 4, data);
#endif


	cpuintrf_push_context(cpunum);


	oldval = jaguar.ctrl[offset];
	newval = oldval;
	COMBINE_DATA(&newval);


	switch (offset)
	{
		case D_FLAGS:


			jaguar.ctrl[offset] = newval & (ZFLAG | CFLAG | NFLAG | EINT04FLAGS | EINT5FLAG | RPAGEFLAG);
			if (newval & IFLAG)
				jaguar.ctrl[offset] |= oldval & IFLAG;


			jaguar.ctrl[D_CTRL] &= ~((newval & CINT04FLAGS) >> 3);
			jaguar.ctrl[D_CTRL] &= ~((newval & CINT5FLAG) >> 1);


			update_register_banks();


			check_irqs();
			break;

		case D_MTXC:
		case D_MTXA:
			jaguar.ctrl[offset] = newval;
			break;

		case D_END:
			jaguar.ctrl[offset] = newval;
			if ((newval & 7) != 7)
				logerror("DSP to set to little-endian!\n");
			break;

		case D_PC:
			jaguar.PC = newval & 0xffffff;
			if (executing_cpu == cpunum)
				change_pc24bedw(jaguar.PC);
			break;

		case D_CTRL:
			jaguar.ctrl[offset] = newval;
			if ((oldval ^ newval) & 0x01)
			{
				cpu_set_halt_line(cpunum, (newval & 1) ? CLEAR_LINE : ASSERT_LINE);
				cpu_yield();
			}
			if (newval & 0x02)
			{
				if (jaguar.cpu_interrupt)
					(*jaguar.cpu_interrupt)();
				jaguar.ctrl[offset] &= ~0x02;
			}
			if (newval & 0x04)
			{
				jaguar.ctrl[D_CTRL] |= 1 << 6;
				jaguar.ctrl[offset] &= ~0x04;
				check_irqs();
			}
			if (newval & 0x18)
			{
				logerror("DSP single stepping was enabled!\n");
			}
			break;

		case D_MOD:
		case D_DIVCTRL:
			jaguar.ctrl[offset] = newval;
			break;
	}


	cpuintrf_pop_context();
}
