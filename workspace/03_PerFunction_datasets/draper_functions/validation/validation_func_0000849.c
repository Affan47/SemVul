write_trie_word_data(SquatIndex* index, SquatWordTable* t, int len,
                                int* result_offset) {
  int i;
  int offsets[256];
  int off;
  SquatWordTableEntry* entries = t->entries;
  int r;

  memset(offsets, 0, t->first_valid_entry*sizeof(int));
  if (len > 2) {

    for (i = t->first_valid_entry; i <= t->last_valid_entry; i++) {
      SquatWordTable* new_t = entries[i].table;

      if (new_t != NULL) {
        if (write_trie_word_data(index, new_t, len - 1, offsets + i)
            != SQUAT_OK) {
          return SQUAT_ERR;
        }
        free(entries[i].table);
        entries[i].table = NULL;
      } else {
        offsets[i] = 0;
      }
    }
  } else {

    for (i = t->first_valid_entry; i <= t->last_valid_entry; i++) {
      SquatWordTableLeafDocs* leaf_docs = entries[i].leaf_docs;

      if (leaf_docs != NULL) {
        offsets[i] = index->out.total_output_bytes;

        if (dump_doc_list_present_bits(index, leaf_docs) != SQUAT_OK
            || dump_doc_list_docs(index, leaf_docs) != SQUAT_OK) {
          return SQUAT_ERR;
        }
        free(entries[i].leaf_docs);
        entries[i].leaf_docs = NULL;
      } else {
        offsets[i] = 0;
      }
    }
  }
  memset(offsets + i, 0, (256 - i)*sizeof(int));


  *result_offset = off = index->out.total_output_bytes;


  for (i = t->first_valid_entry; i <= t->last_valid_entry; i++) {
    if (offsets[i] != 0) {
      offsets[i] = off - offsets[i];
    }
  }

  r = dump_word_table_offsets(index, t, offsets);


  t->first_valid_entry = 256;
  t->last_valid_entry = 0;

  return r;
}
