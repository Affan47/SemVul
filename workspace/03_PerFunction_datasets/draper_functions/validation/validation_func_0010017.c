operator==(const Node &other) const {
    if(this==&other) {
        return TRUE;
    }
    if(!Node::operator==(other)) {
        return FALSE;
    }
    const SplitBranchNode &o=(const SplitBranchNode &)other;
    return unit==o.unit && lessThan==o.lessThan && greaterOrEqual==o.greaterOrEqual;
}
