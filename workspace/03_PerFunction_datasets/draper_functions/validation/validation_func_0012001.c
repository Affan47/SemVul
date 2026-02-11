updateShortcuts()
{
    QMutableListIterator<QWeakPointer<KActionCollection> > it(d->actionCollections);
    while (it.hasNext()) {
        it.next();
        KActionCollection *collection = it.value().data();
        if (!collection) {

            it.remove();
            continue;
        }

        collection->readSettings();
        if (d->shortcutsDlg) {
            d->shortcutsDlg.data()->addCollection(collection);
        }
    }
}
