static int e1000_pre_save(void *opaque)
{
    E1000State *s = opaque;
    NetClientState *nc = qemu_get_queue(s->nic);


    if (nc->link_down && have_autoneg(s)) {
        s->phy_reg[PHY_STATUS] |= MII_SR_AUTONEG_COMPLETE;
    }


    if (chkflag(TSO) || !s->use_tso_for_migration) {


        s->mig_props = s->tx.props;
    } else {


        s->mig_props = s->tx.tso_props;
    }
    return 0;
}
