void tb_exec_lock(TCGContext *tcg_ctx)
{

    tb_exec_change(tcg_ctx, true);
}
