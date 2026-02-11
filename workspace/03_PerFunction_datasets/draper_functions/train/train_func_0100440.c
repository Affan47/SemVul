knh_PtrMap_get(CTX ctx, kPtrMap *pm, void *keyptr)
{
	knh_hmap_t *hmap = (knh_hmap_t*)pm->mapptr;
	khashcode_t hcode = (khashcode_t)keyptr;
	knh_hentry_t *e = hmap_getentry(hmap, hcode);
	if(e != NULL) {
		hmap_top(hmap, e);
		return e->pvalue;
	}
	return NULL;
}
