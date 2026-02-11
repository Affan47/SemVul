insert_file (const string &path)

{
	char buf[1024];
	ifstream f (path.c_str());

	if (!f) {
		return;
	}

	Glib::RefPtr<Gtk::TextBuffer> tb (etext.get_buffer());

	tb->begin_user_action();
	while (f) {
		f.read (buf, sizeof (buf));

		if (f.gcount()) {
			buf[f.gcount()] = '\0';
			string foo (buf);
			tb->insert (tb->end(), foo);
		}
	}
	tb->end_user_action();
}
