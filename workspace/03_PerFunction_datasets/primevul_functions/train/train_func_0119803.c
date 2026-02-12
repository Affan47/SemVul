cirrus_hook_write_gr(CirrusVGAState * s, unsigned reg_index, int reg_value)
{
#if defined(DEBUG_BITBLT) && 0
    printf("gr%02x: %02x\n", reg_index, reg_value);
#endif
    switch (reg_index) {
    case 0x00:
	s->cirrus_shadow_gr0 = reg_value;
	return CIRRUS_HOOK_NOT_HANDLED;
    case 0x01:
	s->cirrus_shadow_gr1 = reg_value;
	return CIRRUS_HOOK_NOT_HANDLED;
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x06:
    case 0x07:
    case 0x08:
	return CIRRUS_HOOK_NOT_HANDLED;
    case 0x05:
	s->gr[reg_index] = reg_value & 0x7f;
        cirrus_update_memory_access(s);
	break;
    case 0x09:
    case 0x0A:
	s->gr[reg_index] = reg_value;
	cirrus_update_bank_ptr(s, 0);
	cirrus_update_bank_ptr(s, 1);
        break;
    case 0x0B:
	s->gr[reg_index] = reg_value;
	cirrus_update_bank_ptr(s, 0);
	cirrus_update_bank_ptr(s, 1);
        cirrus_update_memory_access(s);
	break;
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x20:
    case 0x22:
    case 0x24:
    case 0x26:
    case 0x28:
    case 0x29:
    case 0x2c:
    case 0x2d:
    case 0x2f:
    case 0x30:
    case 0x32:
    case 0x33:
    case 0x34:
    case 0x35:
    case 0x38:
    case 0x39:
	s->gr[reg_index] = reg_value;
	break;
    case 0x21:
    case 0x23:
    case 0x25:
    case 0x27:
	s->gr[reg_index] = reg_value & 0x1f;
	break;
    case 0x2a:
	s->gr[reg_index] = reg_value & 0x3f;

        if (s->gr[0x31] & CIRRUS_BLT_AUTOSTART) {
            cirrus_bitblt_start(s);
        }
	break;
    case 0x2e:
	s->gr[reg_index] = reg_value & 0x3f;
	break;
    case 0x31:
	cirrus_write_bitblt(s, reg_value);
	break;
    default:
#ifdef DEBUG_CIRRUS
	printf("cirrus: outport gr_index %02x, gr_value %02x\n", reg_index,
	       reg_value);
#endif
	break;
    }

    return CIRRUS_HOOK_HANDLED;
}
