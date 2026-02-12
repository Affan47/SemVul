void tb_flush_jmp_cache(CPUState *cpu, target_ulong addr)
{
#ifdef TARGET_ARM
    struct uc_struct *uc = cpu->uc;
#endif


    tb_jmp_cache_clear_page(cpu, addr - TARGET_PAGE_SIZE);
    tb_jmp_cache_clear_page(cpu, addr);
}
