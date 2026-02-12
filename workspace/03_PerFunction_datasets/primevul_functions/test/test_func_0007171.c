next_segment(svn_stringbuf_t *segment,
             const char *path)
{
  apr_size_t len;
  char c;


  for (len = 0, c = *path; c; c = path[++len])
    if (c == '/')
      {

        segment->data[len] = 0;
        segment->len = len;


        while (path[++len] == '/')
          ;


        return path + len;
      }
    else
      {


        segment->data[len] = c;
      }


  segment->data[len] = 0;
  segment->len = len;


  return NULL;
}
