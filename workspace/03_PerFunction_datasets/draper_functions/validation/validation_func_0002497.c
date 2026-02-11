knh_Param_add(CTX ctx, kParam *pa, kparam_t p)
{
	size_t size = pa->psize + pa->rsize;
	if(size == 0) {
		pa->p0 = p;
		pa->p2 = p;
	}
	else if(size == 1) {
		pa->p1 = p;
		pa->p2 = p;
	}
	else if(size == 2) {
		pa->p2 = p;
	}
	else if(size == 3) {
		kparam_t *params = (kparam_t*)KNH_MALLOC(ctx, K_FASTMALLOC_SIZE);
		params[0] = pa->p0;
		params[1] = pa->p1;
		params[2] = pa->p2;
		params[3] = p;
		pa->capacity = K_FASTMALLOC_SIZE / sizeof(kparam_t);
		pa->params = params;
	}
	else {
		if(pa->capacity == size) {
			pa->params = (kparam_t*)KNH_REALLOC(ctx, NULL, pa->params, pa->capacity, pa->capacity*2, sizeof(kparam_t));
			pa->capacity *= 2;
		}
		pa->params[size] = p;
	}
	pa->psize += 1;
}
