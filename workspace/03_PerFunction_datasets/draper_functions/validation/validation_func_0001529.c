data(const QModelIndex &index, int role) const
{
    if (role == FrecencyRole && index.isValid()) {
        return m_filteredRows[index.row()].frecency;
    }

    return QAbstractProxyModel::data(index, role);
}
