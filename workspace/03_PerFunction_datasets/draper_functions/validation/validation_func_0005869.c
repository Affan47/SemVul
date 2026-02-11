free_member_list(void)
{
	struct category *cat;
	struct member *mem;
	struct reference *dep;
	struct reference *cnf;
	struct reference *use;

	while ((cat = AST_LIST_REMOVE_HEAD(&categories, list))) {
		while ((mem = AST_LIST_REMOVE_HEAD(&cat->members, list))) {
			while ((dep = AST_LIST_REMOVE_HEAD(&mem->deps, list)))
				free(dep);
			while ((cnf = AST_LIST_REMOVE_HEAD(&mem->conflicts, list)))
				free(cnf);
			while ((use = AST_LIST_REMOVE_HEAD(&mem->uses, list)))
				free(use);
			free(mem);
		}
		free(cat);
	}
}
