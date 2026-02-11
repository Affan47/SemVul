rw_rewrite_module(struct rw_transport *module,
	struct rw_info *rwi, void (*func)(struct rw_info *))
{
	if (!module || !module->rw_ptr)
		(*rwi->err_func)(450, "Internal failure.", rwi);
	else if (module->rw_ptr->rewrite_del)
		(*module->rw_ptr->rewrite)(rwi, func);
	else
		(*rwi->err_func)(550, "Invalid address.", rwi);
}
