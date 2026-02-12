static void _delete_submaps_from_bank_tree(RIO *io, RIOBank *bank, RListIter *prio, RIOMap *map) {
	RIOSubMap fake_sm;
	fake_sm.itv = map->itv;
	fake_sm.mapref.id = map->id;
	RRBNode *entry = _find_entry_submap_node (bank, &fake_sm);
	if (!entry) {
		return;
	}
	RIOSubMap *bd = (RIOSubMap *)entry->data;
	while (bd && r_io_submap_overlap (bd, (&fake_sm))) {


		RRBNode *next = r_rbnode_next (entry);
		if (bd->mapref.id == fake_sm.mapref.id) {
			r_queue_enqueue (bank->todo, R_NEWCOPY (RIOSubMap, bd));
			r_crbtree_delete (bank->submaps, bd, _find_sm_by_from_vaddr_cb, NULL);
		}
		entry = next;
		bd = entry ? (RIOSubMap *)entry->data : NULL;
	}
	RListIter *iter = prio;
	while (!r_queue_is_empty (bank->todo)) {


		RIOSubMap *sm = r_queue_dequeue (bank->todo);
		RListIter *ator = r_list_iter_get_prev (iter);
		while (ator) {
			map = r_io_map_get_by_ref (io, (RIOMapRef *)ator->data);
			ator = r_list_iter_get_prev (ator);
			if (!map) {

				continue;
			}


			if (r_io_submap_to (sm) < r_io_map_from (map) || r_io_submap_from (sm) > r_io_map_to (map)) {

				continue;
			}
			RIOMapRef *mapref = _mapref_from_map (map);
			bd = r_io_submap_new (io, mapref);
			free (mapref);
			if (!bd) {
				continue;
			}
			if (r_io_submap_from (sm) >= r_io_map_from (map)) {

				r_io_submap_set_from (bd, r_io_submap_from (sm));
				r_crbtree_insert (bank->submaps, bd, _find_sm_by_from_vaddr_cb, NULL);
				if (r_io_submap_to (sm) <= r_io_map_to (map)) {

					r_io_submap_set_to (bd, r_io_submap_to (sm));
					break;
				}

				r_io_submap_set_from (sm, r_io_submap_to (bd) + 1);
				continue;
			}
			if (r_io_submap_to (sm) <= r_io_map_to (map)) {


				r_io_submap_set_to (bd, r_io_submap_to (sm));

				r_io_submap_set_to (sm, r_io_submap_from (bd) - 1);
				r_crbtree_insert (bank->submaps, bd, _find_sm_by_from_vaddr_cb, NULL);
				continue;
			}

			RIOSubMap *bdsm = R_NEWCOPY (RIOSubMap, sm);
			r_io_submap_set_to (sm, r_io_submap_from (bd) - 1);
			r_io_submap_set_from (bdsm, r_io_submap_to (bd) + 1);
			r_crbtree_insert (bank->submaps, bd, _find_sm_by_from_vaddr_cb, NULL);
			r_queue_enqueue (bank->todo, bdsm);
		}
		free (sm);
	}
}
