conf_load(void)
{
	int stat;

	while (1) {
		cprint_init();
		cprint("--inputbox");
		cprint(load_config_text);
		cprint("11");
		cprint("55");
		cprint("%s", filename);
		stat = exec_conf();
		switch(stat) {
		case 0:
			if (!input_buf[0])
				return;
			if (!conf_read(input_buf))
				return;
			show_textbox(NULL, _("File does not exist!"), 5, 38);
			break;
		case 1:
			show_helptext(_("Load Alternate Configuration"), load_config_help);
			break;
		case 255:
			return;
		}
	}
}
