setEditChoice (GooString* new_content)
{
  delete editedChoice;
  editedChoice = NULL;

  unselectAll();

  if (new_content) {
    editedChoice = new_content->copy();


    if (!editedChoice->hasUnicodeMarker()) {
      editedChoice->insert(0, 0xff);
      editedChoice->insert(0, 0xfe);
    }
  }
  updateSelection();
}
