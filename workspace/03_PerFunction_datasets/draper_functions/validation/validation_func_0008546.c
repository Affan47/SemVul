garbage_collect(void)
{
    size_t i;


    gc_mark_register();
    gc_mark_stack();


    for (i = 0; i < root_ranges_used; i++) {
        gc_mark_range(root_ranges[i].start, root_ranges[i].end);
    }


    gc_sweep();
}
