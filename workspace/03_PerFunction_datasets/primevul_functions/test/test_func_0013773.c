int con_set_unimap(struct vc_data *vc, ushort ct, struct unipair __user *list)
{
	int err = 0, err1, i;
	struct uni_pagedir *p, *q;
	struct unipair *unilist, *plist;

	if (!ct)
		return 0;

	unilist = vmemdup_user(list, ct * sizeof(struct unipair));
	if (IS_ERR(unilist))
		return PTR_ERR(unilist);

	console_lock();


	p = *vc->vc_uni_pagedir_loc;

	if (!p) {
		err = -EINVAL;

		goto out_unlock;
	}

	if (p->refcount > 1) {
		int j, k;
		u16 **p1, *p2, l;

		err1 = con_do_clear_unimap(vc);
		if (err1) {
			err = err1;
			goto out_unlock;
		}


		q = *vc->vc_uni_pagedir_loc;


		l = 0;
		for (i = 0; i < 32; i++) {
		p1 = p->uni_pgdir[i];
		if (p1)
			for (j = 0; j < 32; j++) {
			p2 = p1[j];
			if (p2) {
				for (k = 0; k < 64; k++, l++)
				if (p2[k] != 0xffff) {


					err1 = con_insert_unipair(q, l, p2[k]);
					if (err1) {
						p->refcount++;
						*vc->vc_uni_pagedir_loc = p;
						con_release_unimap(q);
						kfree(q);
						err = err1;
						goto out_unlock;
					}
				}
			} else {

				l += 64;
			}
		}
		else

			l += 32 * 64;
		}


		p = q;
	} else if (p == dflt) {
		dflt = NULL;
	}


	for (plist = unilist; ct; ct--, plist++) {
		err1 = con_insert_unipair(p, plist->unicode, plist->fontpos);
		if (err1)
			err = err1;
	}


	if (con_unify_unimap(vc, p))
		goto out_unlock;

	for (i = 0; i <= 3; i++)
		set_inverse_transl(vc, p, i);
	set_inverse_trans_unicode(vc, p);

out_unlock:
	console_unlock();
	kvfree(unilist);
	return err;
}
