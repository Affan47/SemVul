void cpu_exec_init_all(struct uc_struct *uc)
{


    finalize_target_page_bits(uc);
    memory_map_init(uc);
    io_mem_init(uc);
}
