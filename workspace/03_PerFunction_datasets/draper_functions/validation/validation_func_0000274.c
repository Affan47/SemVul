paintBackground(QPainter *p)
    {

        if (image->hasElement("background-center")) {
            QRectF elementRect = barRect();
            if (elementRect.isEmpty()) {
                return;
            }

            QSize imageSize = image->size();
            image->resize();

            image->setElementPrefix("background");
            image->resizeFrame(elementRect.size());
            image->paintFrame(p, elementRect.topLeft());
            image->resize(imageSize);

            paintBar(p, "bar-inactive");
        } else {
            paint(p, "background");
        }
    }
