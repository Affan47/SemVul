pdf_scan_read_trailer(PDFSCAN *ps, unsigned long *prev)
{
    int code = 0;
    ref p;
    code = pdf_scan_next_token(ps);
    if ((code == 0) && (ps->token_type != marktype))
	code = -1;
    push_token(ps);
    while (code == 0) {
        code = pdf_scan_next_token(ps);
	if (code != 0)
	    break;
	if (is_optoken(ps, "startxref")) {
	    if (ps->root == 0) {
	        p = dict_get(ps, "Root");
	        if (p.type == objtype)
		    ps->root = p.value.objval;
		else {
		    pdf_scan_msgf(ps,
			"trailer /Root requires indirect reference\n");
		    code = -1;
		}
	    }
	    p = dict_get(ps, "Prev");
	    if (p.type == integertype)
		*prev = p.value.intval;
	    else if (p.type != invalidtype) {
		code = -1;
		pdf_scan_msgf(ps, "trailer /Prev requires integer\n");
	    }
	    break;
	}
	if (process_op(ps) != 0)
	    push_token(ps);
    }
    if (code != 0)
	pdf_scan_msgf(ps, "Error reading trailer\n");
    return code;
}
