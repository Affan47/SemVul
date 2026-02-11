makeItemVisible(QGraphicsItem *itemToBeVisible)
    {
        if (!widget) {
            return;
        }

        QRectF rect(widget.data()->mapFromScene(itemToBeVisible->scenePos()), itemToBeVisible->boundingRect().size());
        rectToBeVisible = rect;

        makeRectVisible();
    }
