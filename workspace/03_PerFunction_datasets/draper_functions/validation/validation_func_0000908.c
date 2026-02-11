assoc_mgr_update(List update_list)
{
	int rc = SLURM_SUCCESS;
	ListIterator itr = NULL;
	slurmdb_update_object_t *object = NULL;

	xassert(update_list);
	itr = list_iterator_create(update_list);
	while ((object = list_next(itr))) {
		if (!object->objects || !list_count(object->objects))
			continue;

		switch(object->type) {
		case SLURMDB_MODIFY_USER:
		case SLURMDB_ADD_USER:
		case SLURMDB_REMOVE_USER:
		case SLURMDB_ADD_COORD:
		case SLURMDB_REMOVE_COORD:
			rc = assoc_mgr_update_users(object);
			break;
		case SLURMDB_ADD_ASSOC:
		case SLURMDB_MODIFY_ASSOC:
		case SLURMDB_REMOVE_ASSOC:
		case SLURMDB_REMOVE_ASSOC_USAGE:
			rc = assoc_mgr_update_assocs(object);
			break;
		case SLURMDB_ADD_QOS:
		case SLURMDB_MODIFY_QOS:
		case SLURMDB_REMOVE_QOS:
			rc = assoc_mgr_update_qos(object);
			break;
		case SLURMDB_ADD_WCKEY:
		case SLURMDB_MODIFY_WCKEY:
		case SLURMDB_REMOVE_WCKEY:
			rc = assoc_mgr_update_wckeys(object);
			break;
		case SLURMDB_ADD_CLUSTER:
		case SLURMDB_REMOVE_CLUSTER:


			break;
		case SLURMDB_UPDATE_NOTSET:
		default:
			error("unknown type set in "
			      "update_object: %d",
			      object->type);
			break;
		}
	}
	list_iterator_destroy(itr);
	return rc;
}
