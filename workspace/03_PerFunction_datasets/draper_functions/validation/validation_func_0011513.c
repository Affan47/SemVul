knh_ClassTBL_setConstPool(CTX ctx, const knh_ClassTBL_t *ct)
{
	if(ct->constPoolMapNULL == NULL) {
		KNH_INITv(((knh_ClassTBL_t*)ct)->constPoolMapNULL, new_PtrMap(ctx, 0));
	}
}
