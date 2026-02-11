check_for_reference (xmms_coll_dag_t *dag, xmmsv_coll_t *coll, xmmsv_coll_t *parent, void *udata)
{
	coll_refcheck_t *check = (coll_refcheck_t*)udata;
	if (xmmsv_coll_get_type (coll) == XMMS_COLLECTION_TYPE_REFERENCE && !check->found) {
		gchar *target_name, *target_namespace;

		xmmsv_coll_attribute_get (coll, "reference", &target_name);
		xmmsv_coll_attribute_get (coll, "namespace", &target_namespace);
		if (strcmp (check->target_name, target_name) == 0 &&
		    strcmp (check->target_namespace, target_namespace) == 0) {
			check->found = TRUE;
		} else {
			xmmsv_coll_t *op;
			xmmsv_t *tmp;

			if (xmmsv_list_get (xmmsv_coll_operands_get (coll), 0, &tmp)) {
				xmmsv_get_coll (tmp, &op);
				xmms_collection_apply_to_collection_recurs (dag, op, coll,
				                                            check_for_reference,
				                                            udata);
			}
		}
	}
}
