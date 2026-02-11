__pyx_tp_traverse_6Cython_4Plex_8Scanners_Scanner(PyObject *o, visitproc v, void *a) {
  int e;
  struct __pyx_obj_6Cython_4Plex_8Scanners_Scanner *p = (struct __pyx_obj_6Cython_4Plex_8Scanners_Scanner *)o;
  if (p->lexicon) {
    e = (*v)(p->lexicon, a); if (e) return e;
  }
  if (p->stream) {
    e = (*v)(p->stream, a); if (e) return e;
  }
  if (p->name) {
    e = (*v)(p->name, a); if (e) return e;
  }
  if (p->text) {
    e = (*v)(p->text, a); if (e) return e;
  }
  if (p->initial_state) {
    e = (*v)(p->initial_state, a); if (e) return e;
  }
  if (p->state_name) {
    e = (*v)(p->state_name, a); if (e) return e;
  }
  if (p->queue) {
    e = (*v)(p->queue, a); if (e) return e;
  }
  if (p->cur_char) {
    e = (*v)(p->cur_char, a); if (e) return e;
  }
  if (p->level) {
    e = (*v)(p->level, a); if (e) return e;
  }
  return 0;
}
