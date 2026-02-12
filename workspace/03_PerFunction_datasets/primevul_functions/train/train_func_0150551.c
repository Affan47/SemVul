void qemu_ram_unset_idstr(ram_addr_t addr)
{
    RAMBlock *block;


    rcu_read_lock();
    block = find_ram_block(addr);
    if (block) {
        memset(block->idstr, 0, sizeof(block->idstr));
    }
    rcu_read_unlock();
}
