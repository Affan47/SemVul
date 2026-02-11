Swig_typemap_debug() {
  int ts;
  Printf(stdout, "---[ typemaps ]--------------------------------------------------------------\n");

  ts = tm_scope;
  while (ts >= 0) {
    Printf(stdout, "::: scope %d\n\n", ts);
    Printf(stdout, "%s\n", typemaps[ts]);
    ts--;
  }
  Printf(stdout, "-----------------------------------------------------------------------------\n");
}
