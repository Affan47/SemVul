fix_unclean_leb(struct ubifs_info *c, struct ubifs_scan_leb *sleb,
			   int start)
{
	int lnum = sleb->lnum, endpt = start;


	if (!list_empty(&sleb->nodes)) {
		struct ubifs_scan_node *snod;

		snod = list_entry(sleb->nodes.prev,
				  struct ubifs_scan_node, list);
		endpt = snod->offs + snod->len;
	}

	if (c->ro_mount && !c->remounting_rw) {

		struct ubifs_unclean_leb *ucleb;

		dbg_rcvry("need to fix LEB %d start %d endpt %d",
			  lnum, start, sleb->endpt);
		ucleb = kzalloc(sizeof(struct ubifs_unclean_leb), GFP_NOFS);
		if (!ucleb)
			return -ENOMEM;
		ucleb->lnum = lnum;
		ucleb->endpt = endpt;
		list_add_tail(&ucleb->list, &c->unclean_leb_list);
	} else {

		int err;

		dbg_rcvry("fixing LEB %d start %d endpt %d",
			  lnum, start, sleb->endpt);
		if (endpt == 0) {
			err = ubifs_leb_unmap(c, lnum);
			if (err)
				return err;
		} else {
			int len = ALIGN(endpt, c->min_io_size);

			if (start) {
				err = ubifs_leb_read(c, lnum, sleb->buf, 0,
						     start, 1);
				if (err)
					return err;
			}

			if (len > endpt) {
				int pad_len = len - ALIGN(endpt, 8);

				if (pad_len > 0) {
					void *buf = sleb->buf + len - pad_len;

					ubifs_pad(c, buf, pad_len);
				}
			}
			err = ubifs_leb_change(c, lnum, sleb->buf, len);
			if (err)
				return err;
		}
	}
	return 0;
}
