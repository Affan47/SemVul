eb_finalize_hookset(EB_Hookset *hookset)
{
    int i;

    LOG(("in: eb_finalize_hookset()"));

    for (i = 0; i < EB_NUMBER_OF_HOOKS; i++) {
	hookset->hooks[i].code = i;
	hookset->hooks[i].function = NULL;
    }
    eb_finalize_lock(&hookset->lock);

    LOG(("out: eb_finalize_hookset()"));
}
