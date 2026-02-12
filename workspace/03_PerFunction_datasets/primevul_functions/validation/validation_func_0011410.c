static void load_creator_from_old_format(
    FILE       *fp,
    xref_t     *xref,
    const char *buf,
    size_t      buf_size)
{
    int            i, n_eles, length, is_escaped, obj_id;
    char          *c, *ascii, *start, *s, *saved_buf_search, *obj;
    size_t         obj_size;
    pdf_creator_t *info;

    info = new_creator(&n_eles);


    if (buf_size < 1) return;
    const char *buf_end = buf + buf_size - 1;


    const char *end = buf_end;

    for (i=0; i<n_eles; ++i)
    {
        if (!(c = strstr(buf, info[i].key)))
          continue;


        c += strlen(info[i].key);
        while (isspace(*c))
          ++c;
        if (c >= buf_end) {
          FAIL("Failed to locate space, likely a corrupt PDF.");
        }


        if (*c == '/')
          continue;


        obj = saved_buf_search = NULL;
        obj_size = 0;
        end = buf_end;
        if (isdigit(*c))
        {
            obj_id = atoi(c);
            saved_buf_search = c;
            s = saved_buf_search;

            obj = get_object(fp, obj_id, xref, &obj_size, NULL);
            end = obj + obj_size;
            c = obj;


            while (c && (*c != '(') && (c < end))
              ++c;
            if (c >= end)  {
              FAIL("Failed to locate a '(' character. "
                  "This might be a corrupt PDF.\n");
            }


            while (s && (*s == '/') && (s < buf_end))
              ++s;
            if (s >= buf_end)  {
              FAIL("Failed to locate a '/' character. "
                  "This might be a corrupt PDF.\n");
            }
            saved_buf_search = s;
        }


        start = c;
        length = is_escaped = 0;
        while (c && ((*c != '\r') && (*c != '\n') && (*c != '<')))
        {

            if (!is_escaped && (*c == ')'))
              break;
            else if (*c == '\\')
              is_escaped = 1;
            else
              is_escaped = 0;
            ++c;
            ++length;
            if (c > end) {
              FAIL("Failed to locate the end of a value. "
                   "This might be a corrupt PDF.\n");
            }
        }

        if (length == 0)
          continue;


        if (length)
          length += 1;
        length = (length > KV_MAX_VALUE_LENGTH) ? KV_MAX_VALUE_LENGTH : length;
        strncpy(info[i].value, start, length);
        info[i].value[KV_MAX_VALUE_LENGTH - 1] = '\0';


        if (saved_buf_search)
        {

            free(obj);
            c = saved_buf_search;
        }
    }


    for (i = 0; i < n_eles; ++i) {
      const size_t val_str_len = strnlen(info[i].value, KV_MAX_VALUE_LENGTH);
      if ((ascii = decode_text_string(info[i].value, val_str_len))) {
        strncpy(info[i].value, ascii, val_str_len);
        free(ascii);
      }
    }

    xref->creator = info;
    xref->n_creator_entries = n_eles;
}
