void cpu_exec_init_all(void)
{
    qemu_mutex_init(&ram_list.mutex);


    finalize_target_page_bits();
    io_mem_init();
    memory_map_init();
    qemu_mutex_init(&map_client_list_lock);
}
