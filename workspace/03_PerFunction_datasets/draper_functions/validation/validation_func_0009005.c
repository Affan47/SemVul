lkb_idr_free(int id, void *p, void *data)
{
	struct dlm_lkb *lkb = p;

	if (lkb->lkb_lvbptr && lkb->lkb_flags & DLM_IFL_MSTCPY)
		dlm_free_lvb(lkb->lkb_lvbptr);

	dlm_free_lkb(lkb);
	return 0;
}
