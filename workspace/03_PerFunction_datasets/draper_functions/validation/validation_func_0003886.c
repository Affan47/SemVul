result_item_create_role_trans(GtkTextTagTable * table)
{
	result_item_t *item = result_item_single_create(table);
	if (item == NULL) {
		return item;
	}
	item->label = "Role Transitions";
	item->bit_pos = POLDIFF_DIFF_ROLE_TRANS;
	item->get_vector = poldiff_get_role_trans_vector;
	item->get_form = poldiff_role_trans_get_form;
	item->get_string = poldiff_role_trans_to_string;
	item->get_forms = result_item_role_trans_get_forms;
	item->get_buffer = result_item_single_get_rule_buffer;
	return item;
}
