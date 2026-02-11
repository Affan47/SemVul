atom_dref_copy_data (AtomDREF * dref, guint8 ** buffer, guint64 * size,
    guint64 * offset)
{
  guint64 original_offset = *offset;
  GList *walker;

  if (!atom_full_copy_data (&dref->header, buffer, size, offset)) {
    return 0;
  }

  prop_copy_uint32 (g_list_length (dref->entries), buffer, size, offset);

  walker = dref->entries;
  while (walker != NULL) {
    Atom *atom = (Atom *) walker->data;

    if (atom->type == FOURCC_url_) {
      atom_url_copy_data ((AtomURL *) atom, buffer, size, offset);
    } else if (atom->type == FOURCC_alis) {
      atom_full_copy_data ((AtomFull *) atom, buffer, size, offset);
    } else {
      g_error ("Unsupported atom used inside dref atom");
    }
    walker = g_list_next (walker);
  }

  atom_write_size (buffer, size, offset, original_offset);
  return *offset - original_offset;
}
