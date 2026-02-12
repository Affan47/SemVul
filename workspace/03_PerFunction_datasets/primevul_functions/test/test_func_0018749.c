static void ram_block_add(struct uc_struct *uc, RAMBlock *new_block)
{
    RAMBlock *block;
    RAMBlock *last_block = NULL;

    new_block->offset = find_ram_offset(uc, new_block->max_length);

    if (!new_block->host) {
        new_block->host = phys_mem_alloc(uc, new_block->max_length,
                &new_block->mr->align);
        if (!new_block->host) {

            uc->invalid_error = UC_ERR_NOMEM;


            return;
        }

    }


    RAMBLOCK_FOREACH(block) {
        last_block = block;
        if (block->max_length < new_block->max_length) {
            break;
        }
    }
    if (block) {
        QLIST_INSERT_BEFORE_RCU(block, new_block, next);
    } else if (last_block) {
        QLIST_INSERT_AFTER_RCU(last_block, new_block, next);
    } else {
        QLIST_INSERT_HEAD_RCU(&uc->ram_list.blocks, new_block, next);
    }
    uc->ram_list.mru_block = NULL;


    cpu_physical_memory_set_dirty_range(new_block->offset,
                                        new_block->used_length,
                                        DIRTY_CLIENTS_ALL);

}
