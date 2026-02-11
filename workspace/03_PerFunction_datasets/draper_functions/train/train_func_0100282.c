GC_push_roots(GC_bool all, ptr_t cold_gc_frame GC_ATTR_UNUSED)
{
    int i;
    unsigned kind;


#      if !defined(REGISTER_LIBRARIES_EARLY)
         GC_cond_register_dynamic_libraries();
#      endif


       for (i = 0; i < n_root_sets; i++) {
         GC_push_conditional_with_exclusions(
                             GC_static_roots[i].r_start,
                             GC_static_roots[i].r_end, all);
       }


       for (kind = 0; kind < GC_n_kinds; kind++) {
         void *base = GC_base(GC_obj_kinds[kind].ok_freelist);
         if (0 != base) {
           GC_set_mark_bit(base);
         }
       }


       if (GC_no_dls || roots_were_cleared) {
           GC_push_gc_structures();
       }


#      if defined(THREAD_LOCAL_ALLOC)
         if (GC_world_stopped) GC_mark_thread_local_free_lists();
#      endif


#    ifndef STACK_NOT_SCANNED
       GC_push_regs_and_stack(cold_gc_frame);
#    endif

    if (GC_push_other_roots != 0) (*GC_push_other_roots)();


}
