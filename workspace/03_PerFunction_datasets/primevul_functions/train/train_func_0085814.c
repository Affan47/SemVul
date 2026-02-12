static int find_boundary(multipart_buffer *self, char *boundary) {
  char *line;


  while( (line = get_line(self)) )
  {

    if (!strcmp(line, boundary)) {
      return 1;
    }
  }


  return 0;
}
