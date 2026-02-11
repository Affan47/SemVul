generate_expr_bin(ast_expr * e) {

    ast_expr* up = e->get_up_op();
    bool need_para = false;
    if (up == NULL)
        need_para = false;
    else if (up->is_biop() || up->is_comp()) {
        need_para = check_need_para(e->get_optype(), up->get_optype(), e->is_right_op());
    } else {
        need_para = true;
    }

    if (need_para) _Body.push("(");

    generate_expr(e->get_left_op());
    _Body.SPC();
    const char* opstr = gm_get_op_string(e->get_optype());
    _Body.push_spc(opstr);
    generate_expr(e->get_right_op());

    if (need_para) _Body.push(")");
}
