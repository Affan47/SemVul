copy(bool b) {
    expr_list* T = new expr_list;
    std::list<ast_expr*>::iterator I;
    for (I = args.begin(); I != args.end(); I++) {
        ast_expr* e = *I;
        ast_expr* e2 = e->copy(b);
        T->LIST.push_back(e2);
    }

    ast_expr_builtin* e = ast_expr_builtin::new_builtin_expr(driver->copy(b), get_builtin_def(), T);

    e->set_type_summary(this->get_type_summary());
    return e;
}
