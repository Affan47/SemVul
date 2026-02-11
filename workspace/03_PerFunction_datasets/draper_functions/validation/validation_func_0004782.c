nls_list_print(nls_node *node, FILE* out)
{
	int first = 1;
	nls_node **item, *tmp;

	fprintf(out, "(");
	nls_list_foreach(node, &item, &tmp) {
		if (!first) {
			fprintf(out, " ");
		}
		if (first) {
			first = 0;
		}
		nls_node_print(*item, out);
	}
	fprintf(out, ")");
}
