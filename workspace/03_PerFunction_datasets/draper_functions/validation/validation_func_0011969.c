selectVideo(QString fullpath)
{

    for (int i=0; i<mediaTree->model()->rowCount(); i++) {
        QString path = mediaTree->model()->data(mediaTree->model()->index(i,0)).toString();
        if (path == fullpath) {
            mediaTree->setCurrentIndex(mediaTree->model()->index(i,0));
            break;
        }
    }
}
