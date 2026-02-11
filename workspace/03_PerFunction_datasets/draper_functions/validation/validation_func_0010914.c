obj_nvstore_set_index(TSS_HNVSTORE hNvstore, UINT32 index)
{
	struct tsp_object *obj;
	struct tr_nvstore_obj *nvstore;
	TSS_RESULT result=TSS_SUCCESS;

	if ((obj = obj_list_get_obj(&nvstore_list, hNvstore)) == NULL)
		return TSPERR(TSS_E_INVALID_HANDLE);

	nvstore = (struct tr_nvstore_obj *)obj->data;

	nvstore->nvIndex = index;

	obj_list_put(&nvstore_list);

	return result;
}
