DoCommand (Item *cmd)
{
  int k, dn;
  char *sp;
  Item *item;


  if (cmd->button.key == IB_QUIT)
  {
    if (!XWithdrawWindow(dpy, CF.frame, screen))
    {

    }
  }

  for (k = 0; k < cmd->button.n; k++) {
    char *parsed_command;

    parsed_command = ParseCommand(0, cmd->button.commands[k], '\0', &dn, &sp);
    myfprintf((stderr, "Final command[%d]: [%s]\n", k, parsed_command));


    if ( parsed_command[0] == '!') {
      system(parsed_command+1);
    } else {
      SendText(Channel,parsed_command, ref);
    }
  }


  if (CF.last_error) {
    memset(CF.last_error->text.value, ' ', CF.last_error->text.n);


    XClearArea(dpy,CF.frame,
	       CF.last_error->header.pos_x,
	       CF.last_error->header.pos_y,

	       2000,
	       CF.last_error->header.size_y, False);
  }
  if (cmd->button.key == IB_QUIT) {
    if (CF.grab_server)
      XUngrabServer(dpy);

    SendQuitNotification(Channel);


  }
  else if (cmd->button.key == IB_RESTART) {
    Restart();
    for (item = root_item_ptr; item != 0;
	 item = item->header.next) {
      if (item->type == I_INPUT) {
	XClearWindow(dpy, item->header.win);
	RedrawItem(item, 0, NULL);
      }
      if (item->type == I_CHOICE)
	RedrawItem(item, 0, NULL);
    }
  }
}
