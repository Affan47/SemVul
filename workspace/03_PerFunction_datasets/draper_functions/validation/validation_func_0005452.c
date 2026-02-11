setUrl(const KUrl &url)
{
    KUrl oldUrl = d->currentUrl;
    KFilePlacesModel *placesModel = qobject_cast<KFilePlacesModel*>(model());

    if (placesModel==0) return;

    QModelIndex index = placesModel->closestItem(url);
    QModelIndex current = selectionModel()->currentIndex();

    if (index.isValid()) {
        if (current!=index && placesModel->isHidden(current) && !d->showAll) {
            KFilePlacesViewDelegate *delegate = static_cast<KFilePlacesViewDelegate*>(itemDelegate());
            delegate->addDisappearingItem(current);

            if (d->itemDisappearTimeline.state()!=QTimeLine::Running) {
                delegate->setDisappearingItemProgress(0.0);
                d->itemDisappearTimeline.start();
            }
        }

        if (current!=index && placesModel->isHidden(index) && !d->showAll) {
            KFilePlacesViewDelegate *delegate = static_cast<KFilePlacesViewDelegate*>(itemDelegate());
            delegate->addAppearingItem(index);

            if (d->itemAppearTimeline.state()!=QTimeLine::Running) {
                delegate->setAppearingItemProgress(0.0);
                d->itemAppearTimeline.start();
            }

            setRowHidden(index.row(), false);
        }

        d->currentUrl = url;
        selectionModel()->setCurrentIndex(index, QItemSelectionModel::ClearAndSelect);
    } else {
        d->currentUrl = KUrl();
        selectionModel()->clear();
    }

    if (!current.isValid()) {
        d->updateHiddenRows();
    }
}
