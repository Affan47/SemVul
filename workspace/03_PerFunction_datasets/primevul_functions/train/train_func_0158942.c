msgGetMsgVar(msg_t *pThis, cstr_t *pstrPropName, var_t **ppVar)
{
	DEFiRet;
	var_t *pVar;
	size_t propLen;
	uchar *pszProp = NULL;
	cstr_t *pstrProp;
	propid_t propid;
	unsigned short bMustBeFreed = 0;

	ISOBJ_TYPE_assert(pThis, msg);
	ASSERT(pstrPropName != NULL);
	ASSERT(ppVar != NULL);


	CHKiRet(var.Construct(&pVar));
	CHKiRet(var.ConstructFinalize(pVar));


	propNameToID(pstrPropName, &propid);
	pszProp = (uchar*) MsgGetProp(pThis, NULL, propid, &propLen, &bMustBeFreed);


	CHKiRet(rsCStrConstructFromszStr(&pstrProp, pszProp));
	CHKiRet(var.SetString(pVar, pstrProp));


	*ppVar = pVar;

finalize_it:
	if(bMustBeFreed)
		free(pszProp);

	RETiRet;
}
