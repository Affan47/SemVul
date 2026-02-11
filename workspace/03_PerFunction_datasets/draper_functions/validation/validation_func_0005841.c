generate_expr_val(ast_expr *e) {
    char* temp = temp_str;
    switch (e->get_opclass()) {
        case GMEXPR_IVAL:
            if (e->get_ival() < 0)
                sprintf(temp, "(%ld)", e->get_ival());
            else
                sprintf(temp, "%ld", e->get_ival());
            _Body.push(temp);
            return;
        case GMEXPR_FVAL:
            if (e->get_type_summary() == GMTYPE_FLOAT) {
                sprintf(temp, "((float)(%lf))", e->get_fval());
                _Body.push(temp);
            } else {
                if (e->get_fval() < 0) {
                    sprintf(temp, "(%lf)", e->get_fval());
                } else {
                    sprintf(temp, "%lf", e->get_fval());
                }
                _Body.push(temp);
            }
            return;
        case GMEXPR_BVAL:
            sprintf(temp, "%s", e->get_bval() ? "true" : "false");
            _Body.push(temp);
            return;

        default:
            assert(false);
            return;
    }
}
