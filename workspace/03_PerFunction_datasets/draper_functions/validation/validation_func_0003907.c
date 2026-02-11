canFetchMore( const QModelIndex & parent ) const
{
    if (!parent.isValid())
        return false;


    KDirModelNode* node = static_cast<KDirModelNode*>(parent.internalPointer());
    const KFileItem& item = node->item();
    return item.isDir() && !static_cast<KDirModelDirNode *>(node)->isPopulated()
        && static_cast<KDirModelDirNode *>(node)->m_childNodes.isEmpty();
}
