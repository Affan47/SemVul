mimeData( const QModelIndexList & indexes ) const
{
    KUrl::List urls, mostLocalUrls;
    bool canUseMostLocalUrls = true;
    foreach (const QModelIndex &index, indexes) {
        const KFileItem& item = d->nodeForIndex(index)->item();
        urls << item.url();
        bool isLocal;
        mostLocalUrls << item.mostLocalUrl(isLocal);
        if (!isLocal)
            canUseMostLocalUrls = false;
    }
    QMimeData *data = new QMimeData();
    const bool different = canUseMostLocalUrls && (mostLocalUrls != urls);
    urls = simplifiedUrlList(urls);
    if (different) {
        mostLocalUrls = simplifiedUrlList(mostLocalUrls);
        urls.populateMimeData(mostLocalUrls, data);
    } else {
        urls.populateMimeData(data);
    }


    QString application_x_qiconlist;
    const int items = urls.count();
    for (int i = 0; i < items; i++) {
	const int offset = i*16;
	QString tmp("%1$@@$%2$@@$32$@@$32$@@$%3$@@$%4$@@$32$@@$16$@@$no data$@@$");
	application_x_qiconlist += tmp.arg(offset).arg(offset).arg(offset).arg(offset+40);
    }
    data->setData("application/x-qiconlist", application_x_qiconlist.toLatin1());

    return data;
}
