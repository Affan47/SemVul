ulq_node_found_cb(const kuid_t *kuid, const lookup_rs_t *rs, void *arg)
{
	struct ulq_item *ui = arg;

	ulq_item_check(ui);
	g_assert(LOOKUP_STORE == ui->type);
	g_assert(ui->kuid == kuid);

	(*ui->u.fn.ok)(ui->kuid, rs, ui->arg);
	ulq_completed(ui);
}
