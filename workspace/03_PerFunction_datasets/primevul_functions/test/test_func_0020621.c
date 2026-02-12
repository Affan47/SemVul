status_end(stream * s, pcl_state_t * pcs)
{
    if (sendwp(s)) {

        static const char *error_line = "ERROR=INTERNAL ERROR\r\n";
        int error_size = strlen(error_line) + 1;
        uint limit = gs_object_size(pcs->memory, pcs->status.buffer);
        uint wpos = stell(s);

        while (limit - wpos < error_size ||
               pcs->status.buffer[wpos - 1] != '\n')
            --wpos;
        s->end_status = 0;
        sseek(s, wpos);
        stputs(s, error_line);
    }
    sputc(s, FF);
    pcs->status.write_pos = stell(s);
}
