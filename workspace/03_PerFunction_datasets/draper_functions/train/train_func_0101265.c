InsertText(const std::string& c) {
	my_allowHiddenCursor = false;
	if (my_mark != -1 && my_mark != my_cursorPosition) {
		DeleteSelection();
	}

   PG_Application::BulkModeActivator bulk;
   for ( unsigned int i = 0; i < c.length(); ++i )
	  PG_LineEdit::InsertChar(c[i]);
   bulk.disable();
	my_mark = -1;
	CreateTextVector();
	Update();
}
