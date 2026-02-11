makePasteMask(const QString & svgMask, ItemBase * board, double dpi, const LayerList & maskLayerIDs)
{
    QList<ConnectorItem *> throughHoles;
    QList<ConnectorItem *> pads;
    collectThroughHole(throughHoles, pads, maskLayerIDs);
    if (pads.count() == 0) return "";

    QRectF boardRect = board->sceneBoundingRect();
    QList<QRectF> connectorRects;
    foreach (ConnectorItem * connectorItem, throughHoles) {
        QRectF r = connectorItem->sceneBoundingRect();
        QRectF s((r.left() - boardRect.left())  * dpi / GraphicsUtils::SVGDPI,
                 (r.top() - boardRect.top()) * dpi / GraphicsUtils::SVGDPI,
                 r.width() * dpi / GraphicsUtils::SVGDPI,
                 r.height() * dpi / GraphicsUtils::SVGDPI);
        connectorRects << s;
    }

    QDomDocument doc;
    doc.setContent(svgMask);
    QList<QDomElement> leaves;
    QDomElement root = doc.documentElement();
    TextUtils::collectLeaves(root, leaves);
    int ix = 0;
    foreach (QDomElement element, leaves) {
        element.setAttribute("id", ix++);
    }

    QSvgRenderer renderer;
    renderer.load(doc.toByteArray());

    foreach (QDomElement element, leaves) {
        QString id = element.attribute("id");
        QRectF bounds = renderer.boundsOnElement(id);
        QRectF leafRect = renderer.matrixForElement(id).mapRect(bounds);
        QPointF leafCenter = leafRect.center();
        foreach (QRectF r, connectorRects) {
            if (!leafRect.intersects(r)) continue;

            if (!r.contains(leafCenter)) continue;

            QPointF rCenter = r.center();
            if (!leafRect.contains(rCenter)) continue;

            element.setTagName("g");
            break;
        }
    }

    return doc.toString();
}
