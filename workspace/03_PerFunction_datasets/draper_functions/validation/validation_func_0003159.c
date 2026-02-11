ITR_isCAST(tkitr_t *itr)
{
	DBG_ASSERT(itr->c + 1 < itr->e);
	if(ITR_is(itr, TT_PARENTHESIS) && !ITR_isDOTNAME(itr, 1)) {
		tkitr_t cbuf, *citr = ITR_new(ITR_tk(itr), &cbuf);
		if(ITR_is(citr, TT_TO)) {
			ITR_next(citr)
		}
		if((ITR_isT(citr, isTYPE) || ITR_is(itr, TT_MUL)) && ITR_size(citr) == 1) {
			ITR_CASTOP(itr);
			return 1;
		}
	}
	else if(ITR_is(itr, TT_TLINK)) {
		ITR_CASTOP(itr);
		return 1;
	}
	return 0;
}
