add_text_delta_move(gx_device_pdf *pdev, const gs_matrix *pmat)
{
    pdf_text_state_t *const pts = pdev->text->text_state;

    if (matrix_is_compatible(pmat, &pts->in.matrix)) {
        double dx = pmat->tx - pts->in.matrix.tx,
            dy = pmat->ty - pts->in.matrix.ty;
        gs_point dist;
        double dw, dnotw, tdw;
        int code;

        code = set_text_distance(&dist, dx, dy, pmat);
        if (code < 0)
            return code;
        if (pts->wmode)
            dw = dist.y, dnotw = dist.x;
        else
            dw = dist.x, dnotw = dist.y;
        tdw = dw * -1000.0 / pts->in.size;


        if (pts->can_use_TJ && dnotw == 0 && pts->buffer.count_chars > 0 &&


            (tdw >= -MAX_USER_COORD && (tdw * pts->in.size) < MAX_USER_COORD)
            ) {

            int code = append_text_move(pts, tdw);

            if (code >= 0)
                goto finish;
        }
    }
    return -1;
 finish:
    pts->in.matrix = *pmat;
    return 0;
}
