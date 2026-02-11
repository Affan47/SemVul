declaration_alive_merge0(struct stmt *s)
{
	struct decl_live *w;
	struct decl_live *l;
	int done;

	done = 1;

	for (l = s->decl_live_first[1]; l; l = l->next) {
		for (w = s->decl_write_first; ; w = w->next) {
			if (! w) {

				done &= decl_live_add(s, 0, l->decl);
				break;
			}
			if (l->decl == w->decl) {

				break;
			}
		}
	}

	return done;
}
