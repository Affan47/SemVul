pdf_append_chars(gx_device_pdf * pdev, const byte * str, uint size,
                 double wx, double wy, bool nobreak)
{
    pdf_text_state_t *pts = pdev->text->text_state;
    const byte *p = str;
    uint left = size;

    if (pts->buffer.count_chars == 0 && pts->buffer.count_moves == 0) {
        pts->out_pos.x = pts->start.x = pts->in.matrix.tx;
        pts->out_pos.y = pts->start.y = pts->in.matrix.ty;
    }
    while (left)
        if (pts->buffer.count_chars == MAX_TEXT_BUFFER_CHARS ||
            (nobreak && pts->buffer.count_chars + left > MAX_TEXT_BUFFER_CHARS)) {
            int code = sync_text_state(pdev);

            if (code < 0)
                return code;


            pts->continue_line = true;
        } else {
            int code = pdf_open_page(pdev, PDF_IN_STRING);
            uint copy;

            if (code < 0)
                return code;
            copy = min(MAX_TEXT_BUFFER_CHARS - pts->buffer.count_chars, left);
            memcpy(pts->buffer.chars + pts->buffer.count_chars, p, copy);
            pts->buffer.count_chars += copy;
            p += copy;
            left -= copy;
        }
    pts->in.matrix.tx += wx;
    pts->in.matrix.ty += wy;
    pts->out_pos.x += wx;
    pts->out_pos.y += wy;
    return 0;
}
