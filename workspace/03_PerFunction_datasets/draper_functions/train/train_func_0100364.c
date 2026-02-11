shutdown(void) {
  int i;
  if (styledata != NULL) {
    delete styledata;
    styledata = (JML_CHAR*)NULL;
  }
  for(i=0;i<num_possible_styles;i++) {
    free((void *)possible_styles[i]);
  }
  free((void *)possible_styles);
}
