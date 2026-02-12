bool cpu_restore_state(CPUState *cpu, uintptr_t host_pc, bool will_exit)
{
    TCGContext *tcg_ctx = cpu->uc->tcg_ctx;
    TranslationBlock *tb;
    bool r = false;
    uintptr_t check_offset;
    struct uc_struct *uc = cpu->uc;


    check_offset = host_pc - (uintptr_t) uc->tcg_ctx->code_gen_buffer;

    if (check_offset < uc->tcg_ctx->code_gen_buffer_size) {
        tb = tcg_tb_lookup(tcg_ctx, host_pc);
        if (tb) {
            cpu_restore_state_from_tb(cpu, tb, host_pc, will_exit);
            if (tb_cflags(tb) & CF_NOCACHE) {

                tb_phys_invalidate(tcg_ctx, tb, -1);
                tcg_tb_remove(tcg_ctx, tb);
            }
            r = true;
        }
    }

    return r;
}
