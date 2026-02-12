static char *next_line(multipart_buffer *self) {

  char* line = self->buf_begin;
  char* ptr = (char*)memchr(self->buf_begin, '\n', self->bytes_in_buffer);

  if (ptr) {


    if ((ptr - line) > 0 && *(ptr-1) == '\r') {
      *(ptr-1) = 0;
    } else {
      *ptr = 0;
    }


    self->buf_begin = ptr + 1;
    self->bytes_in_buffer -= (self->buf_begin - line);

  } else {


    if (self->bytes_in_buffer < self->bufsize) {
      return nullptr;
    }

    line[self->bufsize] = 0;
    self->buf_begin = ptr;
    self->bytes_in_buffer = 0;
  }

  return line;
}
