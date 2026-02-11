renewEpisode(const QModelIndex &episodeToRenew)
{
    const QString &xml = d->getEpisodeContent(episodeToRenew);


    bool ro = d->_readOnly;
    d->_readOnly = false;
    if (!insertRow(rowCount())) {
        LOG_ERROR("Unable to create a new episode");
        return QModelIndex();
    }

    QModelIndex newEpisode = index(rowCount() - 1, 0);
    QModelIndex xmlIndex = index(newEpisode.row(), EpisodeModel::XmlContent);
    if (setData(xmlIndex, xml)) {
        d->_readOnly = ro;
        return newEpisode;
    }
    d->_readOnly = ro;
    return QModelIndex();
}
