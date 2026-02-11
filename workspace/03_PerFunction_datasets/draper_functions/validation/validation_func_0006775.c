generate_sent_return(ast_return *r) {
    if (r->get_expr() != NULL) {
        _Body.push(GPS_RET_VALUE);
        _Body.push(" = ");
        generate_expr(r->get_expr());
        _Body.pushln(";");
    }
}
