hovered(QAction *action)
{
    QVariant v = action->data();
    if (v.canConvert<QModelIndex>()) {
        QModelIndex idx = qvariant_cast<QModelIndex>(v);
        QString hoveredString = idx.data(Qt::StatusTipRole).toString();
        if (!hoveredString.isEmpty())
            Q_EMIT hovered(hoveredString);
    }
}
