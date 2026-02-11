EA_GetEA(unsigned long *Result, struct _Address *Addr)
{
	switch(Addr->Mode) {
	case 0:
	case 1:
	case 3:
	case 4:
		ERR("Can't get the EA of a register..\n");
		return 0;
	case 2:
	case 5:
	case 6:
		TRACE("Retrieving Effective Address from address 0x%08lx\n", Addr->Address);
		*Result = Addr->Address;
		break;

	case 7:
		switch(Addr->Register) {
		case 0:
		case 1:
		case 2:
		case 3:
			TRACE("Retrieving Effective Address from address 0x%08lx\n", Addr->Address);
			*Result = Addr->Address;
			break;
		case 4:
			return 0;
		}
		break;
	}
	TRACE("   Value=0x%08lx\n", *Result);
	return 1;
}
