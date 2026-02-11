core_tpg_remove_lun(
	struct se_portal_group *tpg,
	struct se_lun *lun)
{


	struct se_device *dev = rcu_dereference_raw(lun->lun_se_dev);

	lun->lun_shutdown = true;

	core_clear_lun_from_tpg(lun, tpg);


	transport_clear_lun_ref(lun);

	mutex_lock(&tpg->tpg_lun_mutex);
	if (lun->lun_se_dev) {
		target_detach_tg_pt_gp(lun);

		spin_lock(&dev->se_port_lock);
		list_del(&lun->lun_dev_link);
		dev->export_count--;
		rcu_assign_pointer(lun->lun_se_dev, NULL);
		spin_unlock(&dev->se_port_lock);
	}
	if (!(dev->se_hba->hba_flags & HBA_FLAGS_INTERNAL_USE))
		hlist_del_rcu(&lun->link);

	lun->lun_shutdown = false;
	mutex_unlock(&tpg->tpg_lun_mutex);

	percpu_ref_exit(&lun->lun_ref);
}
