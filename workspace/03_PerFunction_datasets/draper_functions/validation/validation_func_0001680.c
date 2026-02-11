method_entry_of_iseq(rb_control_frame_t *cfp, rb_iseq_t *iseq)
{
    rb_thread_t *th = GET_THREAD();
    rb_control_frame_t *cfp_limit;

    cfp_limit = (rb_control_frame_t *)(th->stack + th->stack_size);
    while (cfp_limit > cfp) {
	if (cfp->iseq == iseq)
	    return cfp->me;
	cfp = RUBY_VM_PREVIOUS_CONTROL_FRAME(cfp);
    }
    return 0;
}
