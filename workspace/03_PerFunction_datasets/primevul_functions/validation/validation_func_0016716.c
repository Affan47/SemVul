static void cil_reset_typeattr(struct cil_typeattribute *attr)
{

	if (attr->expr_list != NULL) {


		struct cil_list_item *expr = attr->expr_list->head;
		while (expr != NULL) {
			struct cil_list_item *next = expr->next;
			cil_list_item_destroy(&expr, CIL_FALSE);
			expr = next;
		}
		free(attr->expr_list);
		attr->expr_list = NULL;
	}
	attr->used = CIL_FALSE;
	attr->keep = CIL_FALSE;
}
