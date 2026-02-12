e1000_autoneg_done(E1000State *s)
{
    e1000x_update_regs_on_autoneg_done(s->mac_reg, s->phy_reg);


    qemu_flush_queued_packets(qemu_get_queue(s->nic));
}
