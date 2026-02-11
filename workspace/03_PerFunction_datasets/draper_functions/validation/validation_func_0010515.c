_find_qos_name_from_list(
	List qos_list, int qosid)
{
	ListIterator itr = NULL;
	slurmdb_qos_rec_t *qos = NULL;

	if(!qos_list || qosid == NO_VAL)
		return NULL;

	itr = list_iterator_create(qos_list);
	while((qos = list_next(itr))) {
		if(qosid == qos->id)
			break;
	}
	list_iterator_destroy(itr);

	if(qos)
		return qos->name;
	else
		return "Unknown";
}
