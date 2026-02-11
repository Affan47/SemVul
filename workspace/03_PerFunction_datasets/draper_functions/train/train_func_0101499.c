concatenate_unary_strings(struct bt_list_head *head)
{
	struct ctf_node *node;
	GString *str;
	int i = 0;

	str = g_string_new("");
	bt_list_for_each_entry(node, head, siblings) {
		char *src_string;

		if (node->type != NODE_UNARY_EXPRESSION
				|| node->u.unary_expression.type != UNARY_STRING
				|| !((node->u.unary_expression.link != UNARY_LINK_UNKNOWN)
					^ (i == 0)))
			return NULL;
		switch (node->u.unary_expression.link) {
		case UNARY_DOTLINK:
			g_string_append(str, ".");
			break;
		case UNARY_ARROWLINK:
			g_string_append(str, "->");
			break;
		case UNARY_DOTDOTDOT:
			g_string_append(str, "...");
			break;
		default:
			break;
		}
		src_string = node->u.unary_expression.u.string;
		g_string_append(str, src_string);
		i++;
	}
	return g_string_free(str, FALSE);
}
