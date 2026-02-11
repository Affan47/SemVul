Farray_addO(CTX ctx, kArray *a, ksfp_t *v)
{
	size_t capacity = a->dim->capacity;
	if(!(a->size + 1 < capacity)) {
		knh_Array_grow(ctx, a, k_grow(a->size), a->size + 1);
	}
	KNH_INITv_withWB(a, a->list[a->size], v[0].o);
	a->size += 1;
}
