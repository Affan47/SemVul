apply2(ast_sent* s) {
        if (s->get_nodetype() == AST_FOREACH) {
            if (s->find_info_bool(GPS_FLAG_IS_OUTER_LOOP)) {
                outer_loop = NULL;
            } else if (s->find_info_bool(GPS_FLAG_IS_INNER_LOOP)) {
                inner_loop = NULL;
            }
        }

        return true;
    }
