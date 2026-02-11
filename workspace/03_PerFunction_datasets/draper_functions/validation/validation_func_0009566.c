removeChild( int idx )
{
    if ( idx < 0 )
        return false;
    if ( idx < m_children.size() ) {
        ConstraintNode* n = m_children.takeAt( idx );
        n->deleteLater();
        return true;
    }
    return false;
}
