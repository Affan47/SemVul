R_API bool r_io_bank_update_map_boundaries(RIO *io, const ut32 bankid, const ut32 mapid, ut64 ofrom, ut64 oto) {
	RIOBank *bank = r_io_bank_get (io, bankid);
	r_return_val_if_fail (io && bank, false);
	RListIter *iter;
	RIOMapRef *mapref;
	r_list_foreach_prev (bank->maprefs, iter, mapref) {
		if (mapref->id == mapid) {
			goto found;
		}
	}

	return false;
found:
	;RIOMap *map = r_io_map_get_by_ref (io, mapref);
	if (!map) {


		return false;
	}
	if (r_io_map_from (map) == ofrom && r_io_map_to (map) == oto) {

		return true;
	}


	RIOSubMap *sm = r_io_submap_new (io, mapref);
	if (!sm) {
		return false;
	}

	bank->last_used = NULL;


	RIOMap fake_map;
	memcpy (&fake_map, map, sizeof (RIOMap));
	fake_map.itv.addr = ofrom;
	fake_map.itv.size = oto - ofrom + 1;
	_delete_submaps_from_bank_tree (io, bank, iter, &fake_map);

	RRBNode *entry = _find_entry_submap_node (bank, sm);
	if (!entry) {

		r_crbtree_insert (bank->submaps, sm, _find_sm_by_from_vaddr_cb, NULL);


		return true;
	}

	RIOSubMap *bd = (RIOSubMap *)entry->data;

	if (_mapref_priority_cmp (bank, &sm->mapref, &bd->mapref) == 1) {

		if (r_io_submap_to (bd) == r_io_submap_to (sm)) {
			if (r_io_submap_from (bd) >= r_io_submap_from (sm)) {


				memcpy (bd, sm, sizeof (RIOSubMap));
				free (sm);
			} else {
				r_io_submap_set_to (bd, r_io_submap_from (sm) - 1);
				r_crbtree_insert (bank->submaps, sm, _find_sm_by_from_vaddr_cb, NULL);
			}
			return true;
		}
		if (r_io_submap_from (bd) < r_io_submap_from (sm) &&
			r_io_submap_to (sm) < r_io_submap_to (bd)) {
			RIOSubMap *bdsm = R_NEWCOPY (RIOSubMap, bd);

			r_io_submap_set_from (bdsm, r_io_submap_to (sm) + 1);
			r_io_submap_set_to (bd, r_io_submap_from (sm) - 1);

			r_crbtree_insert (bank->submaps, sm, _find_sm_by_from_vaddr_cb, NULL);
			r_crbtree_insert (bank->submaps, bdsm, _find_sm_by_from_vaddr_cb, NULL);
			return true;
		}
		if (r_io_submap_from (bd) < r_io_submap_from (sm)) {
			r_io_submap_set_to (bd, r_io_submap_from (sm) - 1);
			entry = r_rbnode_next (entry);
		}
	} else {


		if (r_io_submap_from (bd) <= r_io_submap_from (sm)) {
			if (r_io_submap_to (sm) <= r_io_submap_to (bd)) {

				free (sm);
				return true;
			}


		} else {
			if (r_io_submap_to (sm) <= r_io_submap_to (bd)) {
				r_io_submap_set_to (sm, r_io_submap_from (bd) - 1);
				if (!r_crbtree_insert (bank->submaps, sm, _find_sm_by_from_vaddr_cb, NULL)) {
					free (sm);
					return false;
				}
				return true;
			}
			RIOSubMap *bdsm = R_NEWCOPY (RIOSubMap, sm);
			if (!bdsm) {
				free (sm);
				return false;
			}
			r_io_submap_set_to (bdsm, r_io_submap_from (bd) - 1);

			if (!r_crbtree_insert (bank->submaps, bdsm, _find_sm_by_from_vaddr_cb, NULL)) {
				free (bdsm);
				free (sm);
				return false;
			}

			entry = r_rbnode_next (entry);
		}
		r_io_submap_set_from (sm, r_io_submap_to (bd) + 1);
	}


	while (entry && r_io_submap_to (((RIOSubMap *)entry->data)) <= r_io_submap_to (sm)) {

		bd = (RIOSubMap *)entry->data;
		entry = r_rbnode_next (entry);

		if (_mapref_priority_cmp (bank, &sm->mapref, &bd->mapref) == 1) {

			r_crbtree_delete (bank->submaps, bd, _find_sm_by_from_vaddr_cb, NULL);
		} else {


			if (r_io_submap_from (bd) > r_io_submap_from (sm)) {
				RIOSubMap *bdsm = R_NEWCOPY (RIOSubMap, sm);
				r_io_submap_set_to (bdsm, r_io_submap_from (bd) - 1);
				r_crbtree_insert (bank->submaps, bdsm, _find_sm_by_from_vaddr_cb, NULL);
			}
			if (r_io_submap_to (bd) == r_io_submap_to (sm)) {


				free (sm);
				return true;
			}
			r_io_submap_set_from (sm, r_io_submap_to (bd) + 1);
		}
	}
	if (!entry) {
		return r_crbtree_insert (bank->submaps, sm, _find_sm_by_from_vaddr_cb, NULL);
	}
	bd = (RIOSubMap *)entry->data;
	if (_mapref_priority_cmp (bank, &sm->mapref, &bd->mapref) == 1) {
		if (r_io_submap_from (bd) <= r_io_submap_to (sm)) {
			r_io_submap_set_from (bd, r_io_submap_to (sm) + 1);
		}
		r_crbtree_insert (bank->submaps, sm, _find_sm_by_from_vaddr_cb, NULL);
	} else {
		if (r_io_submap_from (sm) < r_io_submap_from (bd)) {
			if (r_io_submap_from (bd) <= r_io_submap_to (sm)) {
				r_io_submap_set_to (sm, r_io_submap_from (bd) - 1);
			}
			r_crbtree_insert (bank->submaps, sm, _find_sm_by_from_vaddr_cb, NULL);
		} else {

			free (sm);
		}
	}
	return true;
}
