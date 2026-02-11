policy_view_display_avrule_results(policy_view_t * pv, apol_vector_t * results, int is_syn_rules)
{
	apol_policy_t *policy = toplevel_get_policy(pv->top);
	qpol_policy_t *qp = apol_policy_get_qpol(policy);
	GtkTextIter start, end;
	char *string, buf[64];
	size_t i;

	gtk_text_buffer_get_start_iter(pv->rules_text, &start);
	gtk_text_buffer_get_end_iter(pv->rules_text, &end);
	gtk_text_buffer_delete(pv->rules_text, &start, &end);

	snprintf(buf, 64, "%zd rule(s) match the search criteria.\n\n", apol_vector_get_size(results));
	gtk_text_buffer_insert_with_tags_by_name(pv->rules_text, &end, buf, -1, "summary", NULL);
	for (i = 0; i < apol_vector_get_size(results); i++) {
		if (!is_syn_rules) {
			qpol_avrule_t *rule = apol_vector_get_element(results, i);
			string = apol_avrule_render(policy, rule);
		} else {
			qpol_syn_avrule_t *rule = apol_vector_get_element(results, i);
			string = apol_syn_avrule_render(policy, rule);
			unsigned long lineno;
			if (qpol_policy_has_capability(qp, QPOL_CAP_LINE_NUMBERS)) {
				qpol_syn_avrule_get_lineno(qp, rule, &lineno);
				sprintf(buf, "%ld", lineno);
				gtk_text_buffer_insert_with_tags_by_name(pv->rules_text, &end, "[", -1, "rule", NULL);
				gtk_text_buffer_insert_with_tags_by_name(pv->rules_text, &end, buf, -1, "line-number", NULL);
				gtk_text_buffer_insert_with_tags_by_name(pv->rules_text, &end, "] ", -1, "rule", NULL);
			}
		}
		if (string == NULL) {
			toplevel_ERR(pv->top, "Error displaying rule: %s", strerror(errno));
			return;
		}
		gtk_text_buffer_insert_with_tags_by_name(pv->rules_text, &end, string, -1, "rule", NULL);
		free(string);
		gtk_text_buffer_insert(pv->rules_text, &end, "\n", -1);
	}
}
