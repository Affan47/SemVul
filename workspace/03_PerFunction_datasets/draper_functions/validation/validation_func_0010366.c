TKA_ChangeCurrentTube(struct Togl *togl, GLint argc, CONST84 char **argv) {

  GLint  result;

  if(argc >= 3) {
    ChangeCurrentTube(atoi(argv[2]));
  }
  Togl_PostRedisplay(togl);
  result = TCL_OK;

  return result;

}
