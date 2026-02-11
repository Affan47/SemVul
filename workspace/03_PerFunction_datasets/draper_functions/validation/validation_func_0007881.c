toQuadrilaterals(const QList< HighlightAnnotation::Quad > &quads) const
{
    const int count = quads.size();
    AnnotQuadrilaterals::AnnotQuadrilateral **ac =
        (AnnotQuadrilaterals::AnnotQuadrilateral**)
            gmallocn( count, sizeof(AnnotQuadrilaterals::AnnotQuadrilateral*) );

    double MTX[6];
    fillTransformationMTX(MTX);

    int pos = 0;
    foreach (const HighlightAnnotation::Quad &q, quads)
    {
        double x1, y1, x2, y2, x3, y3, x4, y4;
        XPDFReader::invTransform( MTX, q.points[0], x1, y1 );
        XPDFReader::invTransform( MTX, q.points[1], x2, y2 );

        XPDFReader::invTransform( MTX, q.points[3], x3, y3 );
        XPDFReader::invTransform( MTX, q.points[2], x4, y4 );
        ac[pos++] = new AnnotQuadrilaterals::AnnotQuadrilateral(x1, y1, x2, y2, x3, y3, x4, y4);
    }

    return new AnnotQuadrilaterals(ac, count);
}
