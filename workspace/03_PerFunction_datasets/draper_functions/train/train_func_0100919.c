z8000_get_reg(int regnum)
{
	switch( regnum )
	{
		case REG_PC:
		case Z8000_PC: return PC;
		case REG_SP:
        case Z8000_NSP: return NSP;
        case Z8000_FCW: return FCW;
		case Z8000_PSAP: return PSAP;
		case Z8000_REFRESH: return REFRESH;
		case Z8000_IRQ_REQ: return IRQ_REQ;
		case Z8000_IRQ_SRV: return IRQ_SRV;
		case Z8000_IRQ_VEC: return IRQ_VEC;
		case Z8000_R0: return RW( 0);
		case Z8000_R1: return RW( 1);
		case Z8000_R2: return RW( 2);
		case Z8000_R3: return RW( 3);
		case Z8000_R4: return RW( 4);
		case Z8000_R5: return RW( 5);
		case Z8000_R6: return RW( 6);
		case Z8000_R7: return RW( 7);
		case Z8000_R8: return RW( 8);
		case Z8000_R9: return RW( 9);
		case Z8000_R10: return RW(10);
		case Z8000_R11: return RW(11);
		case Z8000_R12: return RW(12);
		case Z8000_R13: return RW(13);
		case Z8000_R14: return RW(14);
		case Z8000_R15: return RW(15);
		case Z8000_NMI_STATE: return Z.nmi_state;
		case Z8000_NVI_STATE: return Z.irq_state[0];
		case Z8000_VI_STATE: return Z.irq_state[1];
		case REG_PREVIOUSPC: return PPC;
		default:
			if( regnum <= REG_SP_CONTENTS )
			{
				unsigned offset = NSP + 2 * (REG_SP_CONTENTS - regnum);
				if( offset < 0xffff )
					return RDMEM_W( offset );
			}
	}
    return 0;
}
