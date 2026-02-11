hmap_removeON(CTX ctx, kmapptr_t* m, ksfp_t *ksfp)
{
	knh_hmap_t *hmap = (knh_hmap_t*)m;
	kObject *key = ksfp[0].o;
	khashcode_t hcode = O_cTBL(key)->cdef->hashCode(ctx, ksfp[0].p);
	knh_hentry_t *e = hmap_getentry(hmap, hcode);
	while(e != NULL) {
		if(e->hcode == hcode && knh_Object_compareTo(key, e->key) == 0) {
			KNH_FINALv(ctx, e->key);
			hmap_remove(hmap, e);
			hmap_unuse(hmap, e);
			return;
		}
		e = e->next;
	}
}
