static void cil_reset_sid(struct cil_sid *sid)
{

	sid->context = NULL;
	sid->ordered = CIL_FALSE;
}
