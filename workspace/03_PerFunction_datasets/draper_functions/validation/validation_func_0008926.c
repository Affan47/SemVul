prepLoadImage() {
	QString imagesStr = tr("Images");
	imagesStr += " (";
    if (!m_svgOnly) {
	    QList<QByteArray> supportedImageFormats = QImageReader::supportedImageFormats();
	    foreach (QByteArray ba, supportedImageFormats) {
		    imagesStr += "*." + QString(ba) + " ";
	    }
    }
	if (!imagesStr.contains("svg")) {
		imagesStr += "*.svg";
	}
	imagesStr += ")";
	QString fileName = FolderUtils::getOpenFileName(
		NULL,
		tr("Select an image file to load"),
		"",
		imagesStr
	);

	if (fileName.isEmpty()) return;

    if (!checkImage(fileName)) return;

	prepLoadImageAux(fileName, true);
}
