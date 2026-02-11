editPlace(const QModelIndex &index, const QString &text, const KUrl &url,
                                 const QString &iconName, const QString &appName)
{
    if (!index.isValid()) return;

    KFilePlacesItem *item = static_cast<KFilePlacesItem*>(index.internalPointer());

    if (item->isDevice()) return;

    KBookmark bookmark = item->bookmark();

    if (bookmark.isNull()) return;

    bookmark.setFullText(text);
    bookmark.setUrl(url);
    bookmark.setIcon(iconName);
    bookmark.setMetaDataItem("OnlyInApp", appName);

    d->reloadAndSignal();
    emit dataChanged(index, index);
}
