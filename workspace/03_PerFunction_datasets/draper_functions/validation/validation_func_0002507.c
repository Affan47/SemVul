_k_slotClear()
{
    const int numRows = m_rootNode->m_childNodes.count();
    if (numRows > 0) {
        q->beginRemoveRows( QModelIndex(), 0, numRows - 1 );
        q->endRemoveRows();
    }

    m_nodeHash.clear();

    clear();

}
