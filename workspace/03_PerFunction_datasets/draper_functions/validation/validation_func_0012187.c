e1000_phy_setup_autoneg(struct e1000_hw *hw)
{
    int32_t ret_val;
    uint16_t mii_autoneg_adv_reg;
    uint16_t mii_1000t_ctrl_reg;

    DEBUGFUNC("e1000_phy_setup_autoneg");


    ret_val = e1000_read_phy_reg(hw, PHY_AUTONEG_ADV, &mii_autoneg_adv_reg);
    if (ret_val)
        return ret_val;

    if (hw->phy_type != e1000_phy_ife) {

        ret_val = e1000_read_phy_reg(hw, PHY_1000T_CTRL, &mii_1000t_ctrl_reg);
        if (ret_val)
            return ret_val;
    } else
        mii_1000t_ctrl_reg=0;


    mii_autoneg_adv_reg &= ~REG4_SPEED_MASK;
    mii_1000t_ctrl_reg &= ~REG9_SPEED_MASK;

    DEBUGOUT1("autoneg_advertised %x\n", hw->autoneg_advertised);


    if (hw->autoneg_advertised & ADVERTISE_10_HALF) {
        DEBUGOUT("Advertise 10mb Half duplex\n");
        mii_autoneg_adv_reg |= NWAY_AR_10T_HD_CAPS;
    }


    if (hw->autoneg_advertised & ADVERTISE_10_FULL) {
        DEBUGOUT("Advertise 10mb Full duplex\n");
        mii_autoneg_adv_reg |= NWAY_AR_10T_FD_CAPS;
    }


    if (hw->autoneg_advertised & ADVERTISE_100_HALF) {
        DEBUGOUT("Advertise 100mb Half duplex\n");
        mii_autoneg_adv_reg |= NWAY_AR_100TX_HD_CAPS;
    }


    if (hw->autoneg_advertised & ADVERTISE_100_FULL) {
        DEBUGOUT("Advertise 100mb Full duplex\n");
        mii_autoneg_adv_reg |= NWAY_AR_100TX_FD_CAPS;
    }


    if (hw->autoneg_advertised & ADVERTISE_1000_HALF) {
        DEBUGOUT("Advertise 1000mb Half duplex requested, request denied!\n");
    }


    if (hw->autoneg_advertised & ADVERTISE_1000_FULL) {
        DEBUGOUT("Advertise 1000mb Full duplex\n");
        mii_1000t_ctrl_reg |= CR_1000T_FD_CAPS;
        if (hw->phy_type == e1000_phy_ife) {
            DEBUGOUT("e1000_phy_ife is a 10/100 PHY. Gigabit speed is not supported.\n");
        }
    }


    switch (hw->fc) {
    case E1000_FC_NONE:


        mii_autoneg_adv_reg &= ~(NWAY_AR_ASM_DIR | NWAY_AR_PAUSE);
        break;
    case E1000_FC_RX_PAUSE:


        mii_autoneg_adv_reg |= (NWAY_AR_ASM_DIR | NWAY_AR_PAUSE);
        break;
    case E1000_FC_TX_PAUSE:


        mii_autoneg_adv_reg |= NWAY_AR_ASM_DIR;
        mii_autoneg_adv_reg &= ~NWAY_AR_PAUSE;
        break;
    case E1000_FC_FULL:


        mii_autoneg_adv_reg |= (NWAY_AR_ASM_DIR | NWAY_AR_PAUSE);
        break;
    default:
        DEBUGOUT("Flow control param set incorrectly\n");
        return -E1000_ERR_CONFIG;
    }

    ret_val = e1000_write_phy_reg(hw, PHY_AUTONEG_ADV, mii_autoneg_adv_reg);
    if (ret_val)
        return ret_val;

    DEBUGOUT1("Auto-Neg Advertising %x\n", mii_autoneg_adv_reg);

    if (hw->phy_type != e1000_phy_ife) {
        ret_val = e1000_write_phy_reg(hw, PHY_1000T_CTRL, mii_1000t_ctrl_reg);
        if (ret_val)
            return ret_val;
    }

    return E1000_SUCCESS;
}
