void *qemu_get_ram_ptr(ram_addr_t addr)
{
    RAMBlock *block;
    void *ptr;

    rcu_read_lock();
    block = qemu_get_ram_block(addr);

    if (xen_enabled() && block->host == NULL) {


        if (block->offset == 0) {
            ptr = xen_map_cache(addr, 0, 0);
            goto unlock;
        }

        block->host = xen_map_cache(block->offset, block->max_length, 1);
    }
    ptr = ramblock_ptr(block, addr - block->offset);

unlock:
    rcu_read_unlock();
    return ptr;
}
