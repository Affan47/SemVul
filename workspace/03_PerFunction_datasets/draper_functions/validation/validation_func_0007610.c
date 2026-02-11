CORD_lf_func(size_t i, void * client_data)
{
    register lf_state * state = (lf_state *)client_data;
    register cache_line * volatile * cl_addr =
		&(state -> lf_cache[DIV_LINE_SZ(MOD_CACHE_SZ(i))]);
    register cache_line * cl = (cache_line *)ATOMIC_READ(cl_addr);

    if (cl == 0 || cl -> tag != DIV_LINE_SZ(i)) {

    	refill_data rd;

        rd.state = state;
        rd.file_pos =  i;
        rd.new_cache = GC_NEW_ATOMIC(cache_line);
        if (rd.new_cache == 0) OUT_OF_MEMORY;
        return((char)(GC_word)
        	  GC_call_with_alloc_lock((GC_fn_type) refill_cache, &rd));
    }
    return(cl -> data[MOD_LINE_SZ(i)]);
}
