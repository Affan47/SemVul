faceShotActivated(const QModelIndex &index)
{
    if (!index.isValid())
        return;


    QIcon icon = m_imageModel->data(index, Qt::DecorationRole).value<QIcon>();
    _pixmap = icon.pixmap(QSize(150,150));
    accept();
    return;
}
