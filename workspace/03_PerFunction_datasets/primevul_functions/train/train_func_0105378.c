ref_stack_release(ref_stack_t *pstack)
{
    gs_ref_memory_t *mem = pstack->memory;

    ref_stack_clear(pstack);

    gs_free_object((gs_memory_t *)mem, pstack->params,
                   "ref_stack_release(stack.params)");

    gs_free_ref_array(mem, &pstack->current, "ref_stack_release");
}
