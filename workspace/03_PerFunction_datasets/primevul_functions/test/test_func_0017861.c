static int fcn_print_makestyle(RCore *core, RList *fcns, char mode) {
	RListIter *refiter;
	RListIter *fcniter;
	RAnalFunction *fcn;
	RAnalRef *refi;
	RList *refs = NULL;
	PJ *pj = NULL;

	if (mode == 'j') {
		pj = r_core_pj_new (core);
		pj_a (pj);
	}


	r_list_foreach (fcns, fcniter, fcn) {

		refs = r_core_anal_fcn_get_calls (core, fcn);

		r_list_uniq_inplace (refs, RAnalRef_val);


		if (!r_list_empty (refs)) {
			if (pj) {
				pj_o (pj);
				pj_ks (pj, "name", fcn->name);
				pj_kn (pj, "addr", fcn->addr);
				pj_k (pj, "calls");
				pj_a (pj);
			} else {
				r_cons_printf ("%s", fcn->name);
			}

			if (mode == 'm') {
				r_cons_printf (":\n");
			} else if (mode == 'q') {
				r_cons_printf (" -> ");
			}

			r_list_foreach (refs, refiter, refi) {
				RFlagItem *f = r_flag_get_i (core->flags, refi->addr);
				char *dst = r_str_newf ((f? f->name: "0x%08"PFMT64x), refi->addr);
				if (pj) {
					pj_o (pj);
					pj_ks (pj, "name", dst);
					pj_kn (pj, "addr", refi->addr);
					pj_end (pj);
				} else if (mode == 'q') {
					r_cons_printf ("%s ", dst);
				} else {
					r_cons_printf ("    %s\n", dst);
				}
				free (dst);
			}
			if (pj) {
				pj_end (pj);
				pj_end (pj);
			} else {
				r_cons_newline();
			}
		}

		r_list_free (refs);
	}

	if (mode == 'j') {
		pj_end (pj);
		r_cons_printf ("%s\n", pj_string (pj));
	}
	if (pj) {
		pj_free (pj);
	}
	return 0;
}
