e1000_link_up(E1000State *s)
{
    e1000x_update_regs_on_link_up(s->mac_reg, s->phy_reg);


    qemu_flush_queued_packets(qemu_get_queue(s->nic));
}
