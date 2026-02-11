do_list(struct cli *cli, struct backend *b, void *priv)
{
	int *hdr;

	AN(priv);
	hdr = priv;
	if (!*hdr) {
		VCLI_Out(cli, "%-30s %-6s %-10s %s",
		    "Backend name", "Refs", "Admin", "Probe");
		*hdr = 1;
	}
	CHECK_OBJ_NOTNULL(b, BACKEND_MAGIC);

	VCLI_Out(cli, "\n%-30s %-6d", b->display_name, b->refcount);

	if (b->admin_health == ah_probe)
		VCLI_Out(cli, " %-10s", "probe");
	else if (b->admin_health == ah_sick)
		VCLI_Out(cli, " %-10s", "sick");
	else if (b->admin_health == ah_healthy)
		VCLI_Out(cli, " %-10s", "healthy");
	else
		VCLI_Out(cli, " %-10s", "invalid");

	if (b->probe == NULL)
		VCLI_Out(cli, " %s", "Healthy (no probe)");
	else {
		if (b->healthy)
			VCLI_Out(cli, " %s", "Healthy ");
		else
			VCLI_Out(cli, " %s", "Sick ");
		VBP_Summary(cli, b->probe);
	}

	return (0);
}
