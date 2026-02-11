popup_notify_goto_dialog(const char *headline, const char *lines,
                              const struct text_tag_list *tags,
                              struct tile *ptile)
{
  Widget notify_dialog_shell, notify_form, notify_command, notify_goto_command;
  Widget notify_headline, notify_label;
  Dimension width, width2, width_1, width_2;

  if (!ptile) {
    popup_notify_dialog("Message:", headline, lines);
    return;
  }
  notify_dialog_shell = XtCreatePopupShell("Message:",
					   transientShellWidgetClass,
					   toplevel, NULL, 0);

  notify_form = XtVaCreateManagedWidget("notifyform",
					 formWidgetClass,
					 notify_dialog_shell, NULL);

  notify_headline=XtVaCreateManagedWidget("notifyheadline",
			  labelWidgetClass, notify_form,
			  XtNlabel, headline,
			  NULL);


  notify_label=XtVaCreateManagedWidget("notifylabel",
			  labelWidgetClass, notify_form,
			  XtNlabel, lines,
			  NULL);

  notify_command =
    I_L(XtVaCreateManagedWidget("notifycommand",
				commandWidgetClass,
				notify_form,
				NULL));

  notify_goto_command =
    I_L(XtVaCreateManagedWidget("notifygotocommand",
				commandWidgetClass,
				notify_form,
				NULL));

  XtVaGetValues(notify_label, XtNwidth, &width, NULL);
  XtVaGetValues(notify_headline, XtNwidth, &width2, NULL);
  XtVaGetValues(notify_command, XtNwidth, &width_1, NULL);
  XtVaGetValues(notify_goto_command, XtNwidth, &width_2, NULL);
  if (width_1 + width_2 > width) width = width_1 + width_2;
  if(width>width2)
    XtVaSetValues(notify_headline, XtNwidth, width, NULL);

  XtAddCallback(notify_command, XtNcallback, notify_no_goto_command_callback, NULL);
  XtAddCallback(notify_goto_command, XtNcallback, notify_goto_command_callback, NULL);
  notify_goto_add_widget_tile(notify_goto_command, ptile);
  xaw_set_relative_position(toplevel, notify_dialog_shell, 25, 5);
  XtPopup(notify_dialog_shell, XtGrabNone);

}
