static void cil_reset_userattr(struct cil_userattribute *attr)
{
	struct cil_list_item *expr = NULL;
	struct cil_list_item *next = NULL;


	if (attr->expr_list != NULL) {


		expr = attr->expr_list->head;
		while (expr != NULL) {
			next = expr->next;
			cil_list_item_destroy(&expr, CIL_FALSE);
			expr = next;
		}
		free(attr->expr_list);
		attr->expr_list = NULL;
	}
}
