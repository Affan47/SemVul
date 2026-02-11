domenu(BW *bw, unsigned char *s, void *object, int *notify)
{
	struct rc_menu *menu = find_menu(s);
	vsrm(s);
	if (!menu) {
		msgnw(bw->parent, joe_gettext(_("No such menu")));
		if (notify)
			*notify = 1;
		return -1;
	} else {
		bw->b->o.readonly = bw->o.readonly = bw->b->rdonly;
		return display_menu(bw, menu, notify);
	}
}
