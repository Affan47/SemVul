command_places_getShapeHistory(flickcurl* fc, int argc, char *argv[])
{
  flickcurl_shapedata **shapes = NULL;
  int woe_id = -1;
  char* place_id = NULL;

  if(strcmp(argv[1], "-"))
    place_id = argv[1];
  if(argc > 2) {
    if(strcmp(argv[2], "-"))
     woe_id = atoi(argv[2]);
  }

  if(!woe_id < 0 && !place_id)
    return 1;

  shapes = flickcurl_places_getShapeHistory(fc, place_id, woe_id);
  if(shapes) {
    int i;
    for(i = 0; shapes[i]; i++) {
      fprintf(stdout, "Shape %d: ", i);
      command_print_shape(shapes[i]);
      fputc('\n', stdout);
    }

    flickcurl_free_shapes(shapes);
  }

  return (shapes == NULL);
}
