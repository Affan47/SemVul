free_all_array_dim(Array_lmad_dim *dim_head)
{
    Array_lmad_dim *dim, *tmp_dim;

    dim = dim_head;
    while(dim != NULL) {
	if(dim->stride != NULL) {
	    semtree_destruct(dim->stride);
	    dim->stride = NULL;
	}
	if(dim->span != NULL) {
	    semtree_destruct(dim->span);
	    dim->span = NULL;
	}

	tmp_dim = dim;
	dim = dim->next_dim;
	free(tmp_dim);
	tmp_dim = NULL;
    }
}
