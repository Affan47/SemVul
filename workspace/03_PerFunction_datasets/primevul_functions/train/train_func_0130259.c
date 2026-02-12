static void dp8393x_write(void *opaque, hwaddr addr, uint64_t data,
                          unsigned int size)
{
    dp8393xState *s = opaque;
    int reg = addr >> s->it_shift;
    uint32_t val = s->big_endian ? data >> 16 : data;

    DPRINTF("write 0x%04x to reg %s\n", (uint16_t)val, reg_names[reg]);

    switch (reg) {

        case SONIC_CR:
            dp8393x_do_command(s, val);
            break;

        case SONIC_CAP2:
        case SONIC_CAP1:
        case SONIC_CAP0:
        case SONIC_SR:
        case SONIC_MDT:
            DPRINTF("writing to reg %d invalid\n", reg);
            break;

        case SONIC_DCR:
            if (s->regs[SONIC_CR] & SONIC_CR_RST) {
                s->regs[reg] = val & 0xbfff;
            } else {
                DPRINTF("writing to DCR invalid\n");
            }
            break;
        case SONIC_DCR2:
            if (s->regs[SONIC_CR] & SONIC_CR_RST) {
                s->regs[reg] = val & 0xf017;
            } else {
                DPRINTF("writing to DCR2 invalid\n");
            }
            break;

        case SONIC_TCR:
            s->regs[reg] = val & 0xf000;
            break;

        case SONIC_RCR:
            s->regs[reg] = val & 0xffe0;
            break;

        case SONIC_IMR:
            s->regs[reg] = val & 0x7fff;
            dp8393x_update_irq(s);
            break;

        case SONIC_ISR:
            val &= s->regs[reg];
            s->regs[reg] &= ~val;
            if (val & SONIC_ISR_RBE) {
                dp8393x_do_read_rra(s);
            }
            dp8393x_update_irq(s);
            break;

        case SONIC_RSA:
        case SONIC_REA:
        case SONIC_RRP:
        case SONIC_RWP:
            if (s->regs[SONIC_DCR] & SONIC_DCR_DW) {
                s->regs[reg] = val & 0xfffc;
            } else {
                s->regs[reg] = val & 0xfffe;
            }
            break;

        case SONIC_CRCT:
        case SONIC_FAET:
        case SONIC_MPT:
            s->regs[reg] = val ^ 0xffff;
            break;

        default:
            s->regs[reg] = val;
    }

    if (reg == SONIC_WT0 || reg == SONIC_WT1) {
        dp8393x_set_next_tick(s);
    }
}
