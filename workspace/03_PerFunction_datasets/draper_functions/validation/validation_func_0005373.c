e2_action_pack_runtime (E2_Action *action, gpointer data,
	gpointer data_free)
{

	E2_ActionRuntime *rt = ALLOCATE (E2_ActionRuntime);
	CHECKALLOCATEDFATAL (rt);
	rt->action = action;
	rt->data = data;
	rt->data_free = (data == NULL) ? NULL : data_free;
	return rt;
}
