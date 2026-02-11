gastman_redirect(void *data)
{
	struct ast_chan *chan = data;
	char dest[256];
	struct message *m;
	char channame[256];
	char xchan[256] = "";
	char tmp[80];
	char *context;

	if (chan) {
		strncpy(channame, chan->name, sizeof(channame) - 1);
		snprintf(tmp, sizeof(tmp), "Enter new extension for %s", channame);
		if (gui_get_user_input("Redirect", tmp, dest, sizeof(dest)))
			return;
		if (strlen(chan->link)) {
			snprintf(tmp, sizeof(tmp), "Do you want to transfer the person they're talking to (%s), too?", chan->link);
			if (gui_yesno("Confirm additional transfer", tmp, 1))
				snprintf(xchan, sizeof(xchan), "ExtraChannel: %s\r\n", chan->link);
		}
		if ((context = strchr(dest, '@'))) {
			*context = '\0';
			context++;
			manager_action("Redirect", "Channel: %s\r\n%sContext: %s\r\nExten: %s\r\nPriority: 1\r\n", chan->name,xchan, context,dest);
		} else {
			manager_action("Redirect", "Channel: %s\r\n%sExten: %s\r\nPriority: 1\r\n", chan->name, xchan, dest);
		}
		m = wait_for_response(10000);
		if (!m) {
			gui_show_message("Redirect Failed", "Timeout waiting for response");
		} else if (strcasecmp(get_header(m, "Response"), "Success"))  {
			gui_show_message("Redirect Failed", get_header(m, "Message"));
		}
	}

}
