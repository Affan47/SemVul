knh_setClassName(CTX ctx, kclass_t cid, kString *lname, kString *snameNULL)
{
	DBG_ASSERT_cid(cid);
	knh_ClassTBL_t *ct = varClassTBL(cid);
	DBG_ASSERT(ct->lname == NULL);
	KNH_INITv(ct->lname, lname);
	if(snameNULL != NULL) {
		KNH_INITv(ct->sname, snameNULL);
	}
	else if(ct->bcid == cid) {
		KNH_INITv(ct->sname, new_T(ct->cdef->name));
	}
	if(ct->sname == NULL) {
		KNH_INITv(ct->sname, ct->lname);
	}
	OLD_LOCK(ctx, LOCK_SYSTBL, NULL);
	{
		kbytes_t t = S_tobytes(lname);
		if(t.buf[t.len-1] != '>') {
			knh_DictSet_set(ctx, ctx->share->classNameDictSet, lname, (kuintptr_t)ct);
		}
		if(!class_isPrivate(cid) && S_startsWith(lname, STEXT("konoha."))) {
			knh_DictSet_append(ctx, ctx->share->classNameDictSet, ct->sname, (kuintptr_t)ct);
		}
	}
	OLD_UNLOCK(ctx, LOCK_SYSTBL, NULL);
	if(ct->fdefnull == NULL) {
		ct->fdefnull = Fdefnull_newValue;
	}
}
