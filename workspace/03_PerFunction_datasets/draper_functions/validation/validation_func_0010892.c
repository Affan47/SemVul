irc_init_account_prefs(eb_local_account *ela)
{
	irc_local_account *ila = ela->protocol_local_account_data;
	input_list *il = g_new0(input_list, 1);

	ela->prefs = il;

	il->widget.entry.value = ela->handle;
	il->name = "SCREEN_NAME";
	il->label = _("_Nick:");
	il->type = EB_INPUT_ENTRY;

	il->next = g_new0(input_list, 1);
	il = il->next;
	il->widget.entry.value = ila->password;
	il->name = "PASSWORD";
	il->label = _("_Password:");
	il->type = EB_INPUT_PASSWORD;

	il->next = g_new0(input_list, 1);
	il = il->next;
	il->widget.checkbox.value = &ela->connect_at_startup;
	il->name = "CONNECT";
	il->label = _("_Connect at startup");
	il->type = EB_INPUT_CHECKBOX;

	il->next = g_new0(input_list, 1);
	il = il->next;
	il->widget.entry.value = ila->ia->connect_address;
	il->name = "irc_host";
	il->label = _("IRC _Host:");
	il->type = EB_INPUT_ENTRY;

	il->next = g_new0(input_list, 1);
	il = il->next;
	il->widget.entry.value = ila->ia->port;
	il->name = "irc_port";
	il->label = _("IRC P_ort:");
	il->type = EB_INPUT_ENTRY;
}
