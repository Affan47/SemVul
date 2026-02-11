push_argv(argv_stack *stck, char **argv, int ix)
{
    if (stck->top_ix == stck->size) {
	if (stck->base != &stck->def_buf[0]) {
	    stck->size += ARGV_STACK_SIZE_INCR;
	    stck->base = erealloc(stck->base,
				  sizeof(argv_stack_element)*stck->size);
	}
	else {
	    argv_stack_element *base;
	    base = emalloc(sizeof(argv_stack_element)
			   *(stck->size + ARGV_STACK_SIZE_INCR));
	    memcpy((void *) base,
		   (void *) stck->base,
		   sizeof(argv_stack_element)*stck->size);
	    stck->base = base;
	    stck->size += ARGV_STACK_SIZE_INCR;
	}
    }
    stck->base[stck->top_ix].argv = argv;
    stck->base[stck->top_ix++].ix = ix;
}
