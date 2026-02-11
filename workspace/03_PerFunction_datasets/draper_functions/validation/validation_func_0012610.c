rfc3484_sort_results(struct resolv_lookup *lookup)
{
	int i;

	for (i = 0; i < lookup->nr_results; i++) {
		struct sort_result *res = &lookup->results[i];
		find_srcaddr(res);
		res->precedence = match_gai_table(&res->dst.sa,
							gai_precedences);
		res->dst_label = match_gai_table(&res->dst.sa, gai_labels);
		res->src_label = match_gai_table(&res->src.sa, gai_labels);
		res->dst_scope = addr_scope(&res->dst.sa);
		res->src_scope = addr_scope(&res->src.sa);
	}

	qsort(lookup->results, lookup->nr_results,
			sizeof(struct sort_result), rfc3484_compare);
}
