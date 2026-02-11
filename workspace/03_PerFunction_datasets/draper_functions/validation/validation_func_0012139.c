mapObjectsAtScreenPosition(const QPointF &screenPosition) const
{
    if (screenPosition.isNull())
        return QList<QGeoMapObject*>();

    Q_D(const QGeoTiledMapData);

    QList<QGeoMapObject*> results;
    QSet<QGeoMapObject*> considered;

    d->oe->updateTransforms();

    QList<QGraphicsItem*> pixelItems;
    pixelItems = d->oe->pixelScene->items(QRectF(screenPosition - QPointF(1,1),
                                             screenPosition + QPointF(1,1)),
                                      Qt::IntersectsItemShape,
                                      Qt::AscendingOrder);

    foreach (QGraphicsItem *item, pixelItems) {
        QGeoMapObject *object = d->oe->pixelItems.value(item);
        Q_ASSERT(object);

        if (object->isVisible() && !considered.contains(object)) {
            bool contains = false;

            if (d->oe->pixelExact.contains(object)) {
                foreach (QGraphicsItem *item, d->oe->pixelExact.values(object)) {
                    if (item->shape().contains(screenPosition)) {
                        contains = true;
                        break;
                    }
                }
            } else {
                QGraphicsItem *item
                        = d->oe->graphicsItemFromMapObject(object);

                if (item) {
                    QList<QTransform> trans = d->oe->pixelTrans.values(object);

                    foreach (QTransform t, trans) {
                        bool ok;
                        QTransform inv = t.inverted(&ok);
                        if (ok) {
                            QPointF testPt = screenPosition * inv;


                            QGeoMapTextObject *tobj = qobject_cast<QGeoMapTextObject*>(object);
                            if (tobj) {
                                if (item->boundingRect().contains(testPt)) {
                                    contains = true;
                                    break;
                                }
                            } else {
                                if (item->shape().contains(testPt)) {
                                    contains = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }

            if (contains)
                results << object;

            considered.insert(object);
        }
    }

    return results;
}
