pixelsCollide(QImage * image1, QImage * image2, QImage * image3, int x1, int y1, int x2, int y2, uint clr, QList<QPointF> & points) {
    bool result = false;
    const uchar * bits1 = image1->constScanLine(0);
    const uchar * bits2 = image2->constScanLine(0);
    int bytesPerLine = image1->bytesPerLine();
	for (int y = y1; y < y2; y++) {
        int offset = y * bytesPerLine;
		for (int x = x1; x < x2; x++) {


            int byteOffset = (x >> 3) + offset;
            uchar mask = DRC::BitTable[x & 7];

            if (*(bits1 + byteOffset) & mask) continue;
            if (*(bits2 + byteOffset) & mask) continue;

            image3->setPixel(x, y, clr);

			result = true;
            if (points.count() < 1000) {
                points.append(QPointF(x, y));
            }
		}
	}

	return result;
}
