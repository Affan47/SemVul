gretl_list_cmp (const int *list1, const int *list2)
{
    int i;

    if (list1 == NULL && list2 != NULL) {
	return 1;
    } else if (list1 != NULL && list2 == NULL) {
	return 1;
    } else if (list1 == NULL && list2 == NULL) {
	return 0;
    }

    for (i=0; i<=list1[0]; i++) {
	if (list2[i] != list1[i]) {
	    return 1;
	}
    }

    return 0;
}
