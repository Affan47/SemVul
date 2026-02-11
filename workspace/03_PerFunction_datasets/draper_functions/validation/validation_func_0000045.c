get_map_clock_name_value(struct bt_list_head *head)
{
	struct ctf_node *node;
	const char *name = NULL;
	int i = 0;

	bt_list_for_each_entry(node, head, siblings) {
		char *src_string;

		if (node->type != NODE_UNARY_EXPRESSION
			|| node->u.unary_expression.type != UNARY_STRING
			|| !((node->u.unary_expression.link != UNARY_LINK_UNKNOWN)
				^ (i == 0)))
			return 0;

		switch (node->u.unary_expression.link) {
		case UNARY_DOTLINK:
			break;
		case UNARY_ARROWLINK:
		case UNARY_DOTDOTDOT:
			return 0;
		default:
			break;
		}
		src_string = node->u.unary_expression.u.string;
		switch (i) {
		case 0:	if (strcmp("clock", src_string) != 0) {
				return 0;
			}
			break;
		case 1:	name = src_string;
			break;
		case 2:	if (strcmp("value", src_string) != 0) {
				return 0;
			}
			break;
		default:
			return 0;
		}
		i++;
	}
	return g_quark_from_string(name);
}
