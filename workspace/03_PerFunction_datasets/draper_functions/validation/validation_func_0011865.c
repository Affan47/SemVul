atom_stsc_copy_data (AtomSTSC * stsc, guint8 ** buffer, guint64 * size,
    guint64 * offset)
{
  guint64 original_offset = *offset;
  guint i;

  if (!atom_full_copy_data (&stsc->header, buffer, size, offset)) {
    return 0;
  }

  prop_copy_uint32 (atom_array_get_len (&stsc->entries), buffer, size, offset);

  prop_copy_ensure_buffer (buffer, size, offset,
      12 * atom_array_get_len (&stsc->entries));

  for (i = 0; i < atom_array_get_len (&stsc->entries); i++) {
    STSCEntry *entry = &atom_array_index (&stsc->entries, i);

    prop_copy_uint32 (entry->first_chunk, buffer, size, offset);
    prop_copy_uint32 (entry->samples_per_chunk, buffer, size, offset);
    prop_copy_uint32 (entry->sample_description_index, buffer, size, offset);
  }

  atom_write_size (buffer, size, offset, original_offset);
  return *offset - original_offset;
}
