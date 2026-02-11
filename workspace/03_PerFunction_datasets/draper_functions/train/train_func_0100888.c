populateSplitBlock(Block *b, Variable* v, Variable const* u) {
    b->addVariable(v);
    for (Cit c=v->in.begin();c!=v->in.end();++c) {
        if (canFollowLeft(*c,u))
            populateSplitBlock(b, (*c)->left, v);
    }
    for (Cit c=v->out.begin();c!=v->out.end();++c) {
        if (canFollowRight(*c,u))
            populateSplitBlock(b, (*c)->right, v);
    }
}
