begin_context(ast_node* n) {


        if ((n->get_nodetype() == AST_SENTBLOCK) && (n->get_parent() != NULL)) {
            ast_node * t = n->get_parent();
            if (t->get_nodetype() != AST_BFS) return;
            ast_bfs* bfs = (ast_bfs*) t;
            if (n == bfs->get_fbody()) {
                gm_rwinfo_map& B_fw = gm_get_bound_set_info(bfs)->bound_set;


                is_okay = check_add_and_report_conflicts(B_scope, B_fw) && is_okay;

            } else if (n == bfs->get_bbody()) {
                gm_rwinfo_map& B_bw = gm_get_bound_set_info(bfs)->bound_set;
                is_okay = check_add_and_report_conflicts(B_scope, B_bw) && is_okay;
            } else {
                assert(false);
            }
        } else if (n->get_nodetype() == AST_FOREACH) {
            ast_foreach* fe = (ast_foreach*) n;
            gm_rwinfo_map& B = gm_get_bound_set_info(fe)->bound_set;
            is_okay = check_add_and_report_conflicts(B_scope, B) && is_okay;
        }
    }
