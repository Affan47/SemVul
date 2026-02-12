static void hook_count_cb(struct uc_struct *uc, uint64_t address, uint32_t size,
                          void *user_data)
{

    uc->emu_counter++;


    if (uc->emu_counter > uc->emu_count) {

        uc_emu_stop(uc);
    }
}
