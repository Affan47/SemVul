mlxsw_sp_fdb_notify_work(struct work_struct *work)
{
	struct mlxsw_sp *mlxsw_sp;
	char *sfn_pl;
	u8 num_rec;
	int i;
	int err;

	sfn_pl = kmalloc(MLXSW_REG_SFN_LEN, GFP_KERNEL);
	if (!sfn_pl)
		return;

	mlxsw_sp = container_of(work, struct mlxsw_sp, fdb_notify.dw.work);

	rtnl_lock();
	do {
		mlxsw_reg_sfn_pack(sfn_pl);
		err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(sfn), sfn_pl);
		if (err) {
			dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Failed to get FDB notifications\n");
			break;
		}
		num_rec = mlxsw_reg_sfn_num_rec_get(sfn_pl);
		for (i = 0; i < num_rec; i++)
			mlxsw_sp_fdb_notify_rec_process(mlxsw_sp, sfn_pl, i);

	} while (num_rec);
	rtnl_unlock();

	kfree(sfn_pl);
	mlxsw_sp_fdb_notify_work_schedule(mlxsw_sp);
}
