static uint32_t do_phy_read(lan9118_state *s, int reg)
{
    uint32_t val;

    switch (reg) {
    case 0:
        return s->phy_control;
    case 1:
        return s->phy_status;
    case 2:
        return 0x0007;
    case 3:
        return 0xc0d1;
    case 4:
        return s->phy_advertise;
    case 5:
        return 0x0f71;
    case 6:
        return 1;

    case 29:
        val = s->phy_int;
        s->phy_int = 0;
        phy_update_irq(s);
        return val;
    case 30:
        return s->phy_int_mask;
    default:
        BADF("PHY read reg %d\n", reg);
        return 0;
    }
}
