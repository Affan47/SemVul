view_log(const int standard_size) {

  if (logfile_name.empty()) return;

  logfile.flush();
  try {
    new LogViewDialog(standard_size, logfile_name, parent_p);


  }
  catch (LogViewFileError&) {
    new InfoDialog(gettext("Cannot open log file for viewing"),
		   gettext("efax-gtk: view logfile"),
		   GTK_MESSAGE_ERROR,
		   parent_p,
		   true);


  }
}
