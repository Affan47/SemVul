gog_chart_add_axis (GogChart *chart, GogAxisType type)
{
	unsigned i = G_N_ELEMENTS (roles);
	while (i-- > 0)
		if (roles[i].user.i == (int)type) {
			gog_object_add_by_role (GOG_OBJECT (chart), roles + i, NULL);
			return;
		}
	g_warning ("unknown axis type %d", type);
}
