static int e1000_post_load(void *opaque, int version_id)
{
    E1000State *s = opaque;


    s->nic->nc.link_down = (s->mac_reg[STATUS] & E1000_STATUS_LU) == 0;

    return 0;
}
