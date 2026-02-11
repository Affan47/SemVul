verify_ports(void)
{
	int cpunum;


	for (cpunum = 0; cpunum < cpu_gettotalcpu(); cpunum++)
	{
		const struct IO_ReadPort *mra = Machine->drv->cpu[cpunum].port_read;
		const struct IO_WritePort *mwa = Machine->drv->cpu[cpunum].port_write;
		UINT32 width;


		switch (cpunum_databus_width(cpunum))
		{
			case 8:		width = MEMPORT_WIDTH_8;	break;
			case 16:	width = MEMPORT_WIDTH_16;	break;
			case 32:	width = MEMPORT_WIDTH_32;	break;
			default:	return fatalerror("cpu #%d has invalid memory width!\n", cpunum);
		}


		if (mra)
		{

			if (mra->start == MEMPORT_MARKER && mra->end != 0)
			{
				if ((mra->end & MEMPORT_TYPE_MASK) != MEMPORT_TYPE_IO)
					return fatalerror("cpu #%d has memory handlers in place of I/O read handlers!\n", cpunum);
				if ((mra->end & MEMPORT_DIRECTION_MASK) != MEMPORT_DIRECTION_READ)
					return fatalerror("cpu #%d has port write handlers in place of port read handlers!\n", cpunum);
				if ((mra->end & MEMPORT_WIDTH_MASK) != width)
					return fatalerror("cpu #%d uses wrong data width port handlers! (width = %d, memory = %08x)\n", cpunum,cpunum_databus_width(cpunum),mra->end);
			}
		}


		if (mwa)
		{

			if (mwa->start == MEMPORT_MARKER && mwa->end != 0)
			{
				if ((mwa->end & MEMPORT_TYPE_MASK) != MEMPORT_TYPE_IO)
					return fatalerror("cpu #%d has memory handlers in place of I/O write handlers!\n", cpunum);
				if ((mwa->end & MEMPORT_DIRECTION_MASK) != MEMPORT_DIRECTION_WRITE)
					return fatalerror("cpu #%d has port read handlers in place of port write handlers!\n", cpunum);
				if ((mwa->end & MEMPORT_WIDTH_MASK) != width)
					return fatalerror("cpu #%d uses wrong data width port handlers! (width = %d, memory = %08x)\n", cpunum,cpunum_databus_width(cpunum),mwa->end);
			}
		}
	}
	return 1;
}
