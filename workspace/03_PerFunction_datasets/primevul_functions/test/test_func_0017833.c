R_API RList *r_core_anal_fcn_get_calls(RCore *core, RAnalFunction *fcn) {
	RAnalRef *refi;
	RListIter *iter, *iter2;


	RList *refs = r_anal_function_get_refs (fcn);

	if (!r_list_empty (refs)) {

		r_list_foreach_safe (refs, iter, iter2, refi) {
			if (refi->type != R_ANAL_REF_TYPE_CALL) {
				r_list_delete (refs, iter);
			}
		}
	}
	return refs;
}
