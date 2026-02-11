command_photos_notes_add(flickcurl* fc, int argc, char *argv[])
{
  const char *photo_id = argv[1];
  int note_x = atoi(argv[2]);
  int note_y = atoi(argv[3]);
  int note_w = atoi(argv[4]);
  int note_h = atoi(argv[5]);
  char* note_text = argv[6];
  char *id;

  id = flickcurl_photos_notes_add(fc, photo_id,
                                note_x, note_y, note_w, note_h, note_text);
  if(id) {
    if(verbose)
      fprintf(stdout,
              "%s: Added note '%s' (x:%d y:%d w:%d h:%d) to photo ID %s giving note ID %s\n",
              program, note_text, note_x, note_y, note_w, note_h, photo_id, id);
    free(id);
  }

  return (id == NULL);
}
