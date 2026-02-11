delete_all_dups(struct gfs2_inode *ip)
{
	struct osi_node *n, *next;
	struct duptree *dt;
	osi_list_t *tmp, *x;
	struct inode_with_dups *id;
	int found;

	for (n = osi_first(&dup_blocks); n; n = next) {
		next = osi_next(n);
		dt = (struct duptree *)n;

		found = 0;
		id = NULL;

		osi_list_foreach_safe(tmp, &dt->ref_invinode_list, x) {
			id = osi_list_entry(tmp, struct inode_with_dups, list);
			if (id->block_no == ip->i_di.di_num.no_addr) {
				dup_listent_delete(dt, id);
				found = 1;
			}
		}
		osi_list_foreach_safe(tmp, &dt->ref_inode_list, x) {
			id = osi_list_entry(tmp, struct inode_with_dups, list);
			if (id->block_no == ip->i_di.di_num.no_addr) {
				dup_listent_delete(dt, id);
				found = 1;
			}
		}
		if (!found)
			continue;

		if (dt->refs == 0) {
			log_debug(_("This was the last reference: 0x%llx is "
				    "no longer a duplicate.\n"),
				  (unsigned long long)dt->block);
			dup_delete(dt);
		} else {
			log_debug(_("%d references remain to 0x%llx\n"),
				  dt->refs, (unsigned long long)dt->block);
			if (dt->refs > 1)
				continue;

			id = NULL;
			osi_list_foreach(tmp, &dt->ref_invinode_list)
				id = osi_list_entry(tmp,
						    struct inode_with_dups,
						    list);
			osi_list_foreach(tmp, &dt->ref_inode_list)
				id = osi_list_entry(tmp,
						    struct inode_with_dups,
						    list);
			if (id)
				log_debug("Last reference is from inode "
					  "0x%llx\n",
					  (unsigned long long)id->block_no);
		}
	}
}
