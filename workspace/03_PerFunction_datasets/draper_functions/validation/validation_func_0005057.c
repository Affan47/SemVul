os_get_buffer (unsigned char *buf, size_t len, size_t init)
{
    input = malloc(sizeof(glui32)*(len+1));
    max = len;

    if (init)
        os_parse_chars(buf, init + 1, input, len);

    glk_request_line_event_uni(mainwin, input, len - 1, init);
}
