static void cfg_init_defaults(cfg_t *cfg)
{
	int i;

	for (i = 0; cfg->opts && cfg->opts[i].name; i++) {
		int j;

		for (j = 0; j < i; ++j) {
			if (is_set(CFGF_NOCASE, cfg->opts[i].flags | cfg->opts[j].flags)) {
				if (strcasecmp(cfg->opts[i].name, cfg->opts[j].name))
					continue;
			} else {
				if (strcmp(cfg->opts[i].name, cfg->opts[j].name))
					continue;
			}


			cfg_error(cfg, _("duplicate option '%s' not allowed"),
				cfg->opts[i].name);
			break;
		}


		if (cfg->opts[i].simple_value.ptr || is_set(CFGF_NODEFAULT, cfg->opts[i].flags))
			continue;

		if (cfg->opts[i].type != CFGT_SEC) {
			cfg->opts[i].flags |= CFGF_DEFINIT;

			if (is_set(CFGF_LIST, cfg->opts[i].flags) || cfg->opts[i].def.parsed) {
				int xstate, ret = 0;
				char *buf;
				FILE *fp;


				buf = cfg->opts[i].def.parsed;
				if (!buf || !buf[0])
					continue;


				if (is_set(CFGF_LIST, cfg->opts[i].flags))

					xstate = 3;
				else if (cfg->opts[i].type == CFGT_FUNC)
					xstate = 0;
				else
					xstate = 2;

				fp = fmemopen(buf, strlen(buf), "r");
				if (!fp) {


					if (strlen(buf) > 0)
						ret = STATE_ERROR;
				} else {
					cfg_scan_fp_begin(fp);

					do {
						ret = cfg_parse_internal(cfg, 1, xstate, &cfg->opts[i]);
						xstate = -1;
					} while (ret == STATE_CONTINUE);

					cfg_scan_fp_end();
					fclose(fp);
				}

				if (ret == STATE_ERROR) {


					fprintf(stderr, "Parse error in default value '%s'"
						" for option '%s'\n", cfg->opts[i].def.parsed, cfg->opts[i].name);
					fprintf(stderr, "Check your initialization macros and the" " libConfuse documentation\n");
					abort();
				}
			} else {
				switch (cfg->opts[i].type) {
				case CFGT_INT:
					cfg_opt_setnint(&cfg->opts[i], cfg->opts[i].def.number, 0);
					break;

				case CFGT_FLOAT:
					cfg_opt_setnfloat(&cfg->opts[i], cfg->opts[i].def.fpnumber, 0);
					break;

				case CFGT_BOOL:
					cfg_opt_setnbool(&cfg->opts[i], cfg->opts[i].def.boolean, 0);
					break;

				case CFGT_STR:
					cfg_opt_setnstr(&cfg->opts[i], cfg->opts[i].def.string, 0);
					break;

				case CFGT_FUNC:
				case CFGT_PTR:
					break;

				default:
					cfg_error(cfg, "internal error in cfg_init_defaults(%s)", cfg->opts[i].name);
					break;
				}
			}


			cfg->opts[i].flags |= CFGF_RESET;
			cfg->opts[i].flags &= ~CFGF_MODIFIED;
		} else if (!is_set(CFGF_MULTI, cfg->opts[i].flags)) {
			cfg_setopt(cfg, &cfg->opts[i], NULL);
			cfg->opts[i].flags |= CFGF_DEFINIT;
		}
	}
}
