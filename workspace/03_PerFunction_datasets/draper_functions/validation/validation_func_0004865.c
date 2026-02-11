isDirty() const
{
    Q_ASSERT(orientation() == Qt::Horizontal);
    Q_ASSERT(rootIndex() == QModelIndex());


    for(int i = 0; i < model()->columnCount(); i++) {
        QWidget *mapWidget = mappedWidgetAt(i);
        if (mapWidget) {
            const QVariant &current = mapWidget->property(mappedPropertyName(mapWidget));
            const QVariant &orig = _original.value(mapWidget);


            if (orig.isNull() && current.toString().isEmpty())
                continue;
            if (current.type() == QVariant::Pixmap)
                if (orig.isNull() && current.value<QPixmap>().isNull())
                    continue;
            if (current != orig) {


                return true;
            }
        }
    }
    return false;
}
