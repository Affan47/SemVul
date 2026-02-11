Op(char op, ASTexpression* l, ASTexpression* r)
    {
        if (l && r) return new ASToperator(op, l, r);
        return l ? l : r;
    }
