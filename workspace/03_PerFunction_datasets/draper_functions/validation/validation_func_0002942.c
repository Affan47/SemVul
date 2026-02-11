apply_general_options(struct ast_variable *var)
{
	int error = 0;

	while (var) {

		if (!strcmp(var->name, "mailcmd")) {
			ast_copy_string(global_mailcmd, var->value, sizeof(global_mailcmd));
		} else if (!strcmp(var->name, "maxgreet")) {
			global_maxgreet = atoi(var->value);
		} else if (!strcmp(var->name, "maxsilence")) {
			global_maxsilence = atoi(var->value);
			if (global_maxsilence > 0)
				global_maxsilence *= 1000;
		} else if (!strcmp(var->name, "logfile")) {
			if (!ast_strlen_zero(var->value) ) {
				if(*(var->value) == '/')
					ast_copy_string(global_logfile, var->value, sizeof(global_logfile));
				else
					snprintf(global_logfile, sizeof(global_logfile), "%s/%s", ast_config_AST_LOG_DIR, var->value);
			}
		} else if (!strcmp(var->name, "externnotify")) {

			ast_copy_string(global_externnotify, var->value, sizeof(global_externnotify));
		} else if (!strcmp(var->name, "silencetreshold")) {

			global_silencethreshold = atoi(var->value);
		} else if (!strcmp(var->name, "maxmessage")) {
			int x;
			if (sscanf(var->value, "%30d", &x) == 1) {
				global_vmmaxmessage = x;
			} else {
				error ++;
				ast_log(LOG_WARNING, "Invalid max message time length\n");
			}
		} else if (!strcmp(var->name, "minmessage")) {
			int x;
			if (sscanf(var->value, "%30d", &x) == 1) {
				global_vmminmessage = x;
				if (global_maxsilence <= global_vmminmessage)
					ast_log(LOG_WARNING, "maxsilence should be less than minmessage or you may get empty messages\n");
			} else {
				error ++;
				ast_log(LOG_WARNING, "Invalid min message time length\n");
			}
		} else if (!strcmp(var->name, "format")) {
			ast_copy_string(default_vmformat, var->value, sizeof(default_vmformat));
		} else if (!strcmp(var->name, "review")) {
			ast_set2_flag((&globalflags), ast_true(var->value), MVM_REVIEW);
		} else if (!strcmp(var->name, "operator")) {
			ast_set2_flag((&globalflags), ast_true(var->value), MVM_OPERATOR);
		}
		var = var->next;
	}
	return error;
}
