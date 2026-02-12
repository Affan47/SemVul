nv_ctrlg(cmdarg_T *cap)
{
    if (VIsual_active)
    {
	VIsual_select = !VIsual_select;
	showmode();
    }
    else if (!checkclearop(cap->oap))

	fileinfo((int)cap->count0, FALSE, TRUE);
}
