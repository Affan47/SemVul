world_remove_serial(struct world *world, uint32_t serial) {
    uint32_t host_serial = ntohl(serial);

    if (host_serial < 0x40000000)
        world_remove_mobile_serial(world, serial);
    else if (host_serial < 0x80000000)
        world_remove_item_serial(world, serial);
}
