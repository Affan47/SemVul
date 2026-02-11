uct_chat(struct engine *e, struct board *b, char *cmd)
{
	struct uct *u = e->data;
	static char reply[1024];

	cmd += strspn(cmd, " \n\t");
	if (!strncasecmp(cmd, "winrate", 7)) {
		if (!u->t)
			return "no game context (yet?)";
		enum stone color = u->t->root_color;
		struct tree_node *n = u->t->root;
		snprintf(reply, 1024, "In %d playouts at %d threads, %s %s can win with %.2f%% probability",
			 n->u.playouts, u->threads, stone2str(color), coord2sstr(node_coord(n), b),
			 tree_node_get_value(u->t, -1, n->u.value) * 100);
		if (u->t->use_extra_komi && abs(u->t->extra_komi) >= 0.5) {
			sprintf(reply + strlen(reply), ", while self-imposing extra komi %.1f",
				u->t->extra_komi);
		}
		strcat(reply, ".");
		return reply;
	}
	return NULL;
}
