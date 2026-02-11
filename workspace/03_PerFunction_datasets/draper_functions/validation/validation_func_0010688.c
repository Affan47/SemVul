vm_set_main_stack(rb_thread_t *th, VALUE iseqval)
{
    VALUE toplevel_binding = rb_const_get(rb_cObject, rb_intern("TOPLEVEL_BINDING"));
    rb_binding_t *bind;
    rb_iseq_t *iseq;
    rb_env_t *env;

    GetBindingPtr(toplevel_binding, bind);
    GetEnvPtr(bind->env, env);
    th->base_block = &env->block;
    vm_set_eval_stack(th, iseqval, 0);
    th->base_block = 0;


    GetISeqPtr(iseqval, iseq);
    if (bind && iseq->local_size > 0) {
	bind->env = rb_vm_make_env_object(th, th->cfp);
    }

    CHECK_STACK_OVERFLOW(th->cfp, iseq->stack_max);
}
