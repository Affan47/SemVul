gretl_model_get_y_list (const MODEL *pmod)
{
    int *list = NULL;

    if (pmod->ci == BIPROBIT) {
	list = gretl_list_new(2);
	if (list != NULL) {
	    list[1] = pmod->list[1];
	    list[2] = pmod->list[2];
	}
    } else {
	list = gretl_list_new(1);
	if (list != NULL) {
	    list[1] = pmod->list[1];
	}
    }

    return list;
}
