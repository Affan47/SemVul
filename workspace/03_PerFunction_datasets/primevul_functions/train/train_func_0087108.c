set_phy_ctrl(E1000State *s, int index, uint16_t val)
{

    s->phy_reg[PHY_CTRL] = val & ~(0x3f |
                                   MII_CR_RESET |
                                   MII_CR_RESTART_AUTO_NEG);


    if (have_autoneg(s) && (val & MII_CR_RESTART_AUTO_NEG)) {
        e1000x_restart_autoneg(s->mac_reg, s->phy_reg, s->autoneg_timer);
    }
}
