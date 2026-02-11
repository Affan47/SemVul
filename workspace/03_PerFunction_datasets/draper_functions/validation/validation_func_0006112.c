instcmd(const char *cmd, const char *ext)
{
	int i;
	apc_cmdtab_t *ct = NULL;

	for (i = 0; apc_cmdtab[i].name != NULL; i++) {

		if (strcasecmp(apc_cmdtab[i].name, cmd))
			continue;

		if (ext && *ext) {
			if (!apc_cmdtab[i].ext)
				continue;
			if (strlen(apc_cmdtab[i].ext) > 2) {
				if (rexhlp(apc_cmdtab[i].ext, ext))
					continue;
			} else {
				if (strcasecmp(apc_cmdtab[i].ext, ext))
					continue;
			}
		} else if (apc_cmdtab[i].ext)
			continue;
		ct = &apc_cmdtab[i];
		break;
	}

	if (!ct) {
		upslogx(LOG_WARNING, "instcmd: unknown command [%s %s]", cmd,
				ext ? ext : "\b");
		return STAT_INSTCMD_INVALID;
	}

	if (!(ct->flags & APC_PRESENT)) {
		upslogx(LOG_WARNING, "instcmd: command [%s %s] recognized, but"
		       " not supported by your UPS model", cmd,
				ext ? ext : "\b");
		return STAT_INSTCMD_INVALID;
	}


	if ((ct->flags & APC_NASTY) && !instcmd_chktime(ct, ext))
		return STAT_INSTCMD_HANDLED;


	if (!strcasecmp(cmd, "calibrate.start"))
		return do_cal(1);

	if (!strcasecmp(cmd, "calibrate.stop"))
		return do_cal(0);

	if (!strcasecmp(cmd, "load.on"))
		return do_loadon();

	if (!strcasecmp(cmd, "load.off"))
		return sdcmd_Z(0);

	if (!strcasecmp(cmd, "shutdown.stayoff"))
		return sdcmd_K(0);

	if (!strcasecmp(cmd, "shutdown.return")) {
		if (!ext || !*ext)
			return sdcmd_S(0);


		if (!strncasecmp(ext, "at", 2))
			return sdcmd_AT(ext + 3);

		if (!strncasecmp(ext, "cs", 2))
			return sdcmd_CS(0);
	}


	return do_cmd(ct);
}
