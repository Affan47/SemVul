void qemu_ram_unset_idstr(RAMBlock *block)
{


    if (block) {
        memset(block->idstr, 0, sizeof(block->idstr));
    }
}
