asn1p_module_free(asn1p_module_t *mod) {
	if(mod) {
		asn1p_expr_t *expr;

		if(mod->ModuleName)
			free(mod->ModuleName);

		if(mod->module_oid)
			asn1p_oid_free(mod->module_oid);

		while((expr = TQ_REMOVE(&(mod->members), next)))
			asn1p_expr_free(expr);

		free(mod);
	}
}
