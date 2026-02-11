firstSibling() const
{
    const QwtMmlNode *n = this;
    while ( !n->isFirstSibling() )
        n = n->previousSibling();
    return const_cast<QwtMmlNode*>( n );
}
