jsErrorDialogContextMenu() {
  KMenu *m = new KMenu(0L);
  m->addAction(i18n("&Hide Errors"), this, SLOT(removeJSErrorExtension()));
  m->addAction(i18n("&Disable Error Reporting"), this, SLOT(disableJSErrorExtension()));
  m->popup(QCursor::pos());
}
