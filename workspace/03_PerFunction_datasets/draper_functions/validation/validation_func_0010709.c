mlx4_ib_cm_paravirt_clean(struct mlx4_ib_dev *dev, int slave)
{
	struct mlx4_ib_sriov *sriov = &dev->sriov;
	struct rb_root *sl_id_map = &sriov->sl_id_map;
	struct list_head lh;
	struct rb_node *nd;
	int need_flush = 1;
	struct id_map_entry *map, *tmp_map;

	INIT_LIST_HEAD(&lh);
	spin_lock(&sriov->id_map_lock);
	list_for_each_entry_safe(map, tmp_map, &dev->sriov.cm_list, list) {
		if (slave < 0 || slave == map->slave_id) {
			if (map->scheduled_delete)
				need_flush &= !!cancel_delayed_work(&map->timeout);
		}
	}

	spin_unlock(&sriov->id_map_lock);

	if (!need_flush)
		flush_scheduled_work();


	spin_lock(&sriov->id_map_lock);
	if (slave < 0) {
		while (rb_first(sl_id_map)) {
			struct id_map_entry *ent =
				rb_entry(rb_first(sl_id_map),
					 struct id_map_entry, node);

			rb_erase(&ent->node, sl_id_map);
			idr_remove(&sriov->pv_id_table, (int) ent->pv_cm_id);
		}
		list_splice_init(&dev->sriov.cm_list, &lh);
	} else {

		nd = rb_first(sl_id_map);
		while (nd) {
			struct id_map_entry *ent =
				rb_entry(nd, struct id_map_entry, node);
			nd = rb_next(nd);
			if (ent->slave_id == slave)
				list_move_tail(&ent->list, &lh);
		}

		list_for_each_entry_safe(map, tmp_map, &lh, list) {
			rb_erase(&map->node, sl_id_map);
			idr_remove(&sriov->pv_id_table, (int) map->pv_cm_id);
		}


		list_for_each_entry_safe(map, tmp_map, &dev->sriov.cm_list, list) {
			if (slave == map->slave_id)
				list_move_tail(&map->list, &lh);
		}
	}

	spin_unlock(&sriov->id_map_lock);


	list_for_each_entry_safe(map, tmp_map, &lh, list) {
		list_del(&map->list);
		kfree(map);
	}
}
