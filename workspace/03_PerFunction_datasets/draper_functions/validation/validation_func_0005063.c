stonith_get_status(Stonith* s)
{
	StonithPlugin*	sp = (StonithPlugin*)s;
	if (sp && sp->s_ops && sp->isconfigured) {
		return sp->s_ops->get_status(sp);
	}
	return S_INVAL;
}
