genPreview(PixmapButton * button)
{
    QUrl currentUrl = button->property("url").toUrl();
    QString fwFilePath = currentUrl.toString();


    QImage previewImage = FotowallFile::embeddedPreview(fwFilePath);


    if (previewImage.isNull()) {
        Canvas * canvas = new Canvas(physicalDpiX(), physicalDpiY(), this);
        if (FotowallFile::read(fwFilePath, canvas, false)) {

            canvas->resizeAutoFit();
            canvas->setEmbeddedPainting(true);
            previewImage = canvas->renderedImage(QSize(48, 48), Qt::KeepAspectRatio, true);
        }
        delete canvas;
    }


    if (!previewImage.isNull()) {
        int angle = button->property("angle").toInt();
        button->setPixmap(prettyPixmap(previewImage, angle));
    }
}
