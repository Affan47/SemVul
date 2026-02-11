columnCount( const QModelIndex &parent ) const
{
    if( !parent.isValid() ||
        ( parent.internalId() == tupleIndexIndernalId && parent.column() == m_titleColumn ) )
    {
        return m_columns.count();
    }
    return 0;
}
