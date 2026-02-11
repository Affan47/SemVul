zreadstring_at(i_ctx_t *i_ctx_p, os_ptr op, uint start)
{
    stream *s;
    uint len, rlen;
    int status;

    check_write_type(*op, t_string);
    check_read_file(i_ctx_p, s, op - 1);
    len = r_size(op);
    status = sgets(s, op->value.bytes + start, len - start, &rlen);
    rlen += start;
    switch (status) {
        case EOFC:
        case 0:
            break;
        default:
            return handle_read_status(i_ctx_p, status, op - 1, &rlen,
                                      zreadstring_continue);
    }


    if (len == 0)
        return_error(e_rangecheck);
    r_set_size(op, rlen);
    op[-1] = *op;
    make_bool(op, (rlen == len ? 1 : 0));
    return 0;
}
