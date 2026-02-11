nls_var_bound_vars(nls_node **tree, nls_node *var)
{
	if (!nls_strcmp((*tree)->nn_var.nv_name, var->nn_var.nv_name)) {
		nls_node **next_ref = var->nn_var.nv_next_ref;

		(*tree)->nn_var.nv_next_ref = next_ref;
		var->nn_var.nv_next_ref = tree;
	}
}
