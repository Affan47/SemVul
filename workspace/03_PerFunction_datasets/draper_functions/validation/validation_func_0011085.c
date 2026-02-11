buildReturn (Node *node) {
    issue (new IFInstruction (node, opSTATEMENT)) ;
    IFNode *val = NULL ;


    if (node->left != NULL) {
        val = expression (node->left) ;
        if (node->right != NULL) {
            IFNode *t = expression (node->right) ;
            val = issue (new IFExpression (node, opCAST, t, val)) ;
        }
    }

    if (scopeLevel > 0 || trylevel > 0 || foreachlevel > 0) {
        issue (new IFInstruction (node, opPOPSCOPE, integer (node, scopeLevel), integer (node, trylevel), integer (node, foreachlevel))) ;
    }
    if (monitorlevel > 0) {
        std::deque<IFNode*>::reverse_iterator r = monitorStack.rbegin() ;
        while (r != monitorStack.rend()) {
             issue (new IFInstruction (node, opMONITOREXIT, *r)) ;
             r++ ;
        }
    }
    if (node->left == NULL) {
        issue (new IFInstruction (node, opRET)) ;
    } else {
        if (node->left->flags & NODE_TYPEFIXED) {
            switch (node->left->type) {
            case T_INTEGER:
                issue (new IFInstruction (node, opRETVAL_I, val)) ;
                return ;
            }
        }
        issue (new IFInstruction (node, opRETVAL, val)) ;
    }
}
