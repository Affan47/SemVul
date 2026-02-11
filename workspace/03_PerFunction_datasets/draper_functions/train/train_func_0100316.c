accept_editor(FieldEditor* e) {
  const String* fstring = e->text();
  boolean urlflag = OpenFileChooser::urltest(fstring->string());
  if (!_from_command && !urlflag) {
    String* path = Directory::canonical(*fstring);
    e->field(*path);
    if (chdir(*path)) {

      delete path;
    } else {
      selected_ = path;
      fchooser_->dismiss(true);
      e->select(path->rindex('/') + 1, path->length());
    }
  } else {
    selected_ = e->text();
    fchooser_->dismiss(true);
    e->select(0, selected_->length());
  }
}
