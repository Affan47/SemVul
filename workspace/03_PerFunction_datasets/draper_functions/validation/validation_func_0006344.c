setPlaceHidden(const QModelIndex &index, bool hidden)
{
    if (!index.isValid()) return;

    KFilePlacesItem *item = static_cast<KFilePlacesItem*>(index.internalPointer());

    KBookmark bookmark = item->bookmark();

    if (bookmark.isNull()) return;

    bookmark.setMetaDataItem("IsHidden", (hidden ? "true" : "false"));

    d->reloadAndSignal();
    emit dataChanged(index, index);
}
