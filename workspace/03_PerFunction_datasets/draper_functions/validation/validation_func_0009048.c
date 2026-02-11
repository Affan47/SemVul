arc(float x, float y, float radius, float startAngle, float endAngle,
                              bool counterClockWise, int& exceptionCode)
{
    exceptionCode = 0;

    if (radius <= 0) {
        exceptionCode = DOMException::INDEX_SIZE_ERR;
        return;
    }

    const QRectF rect(x - radius, y - radius, radius * 2, radius * 2);
    float sweepLength = -degrees(endAngle - startAngle);
    startAngle = -degrees(startAngle);

    if (counterClockWise && (sweepLength < 0 || sweepLength > 360))
    {
        sweepLength = 360 + std::fmod(sweepLength, float(360.0));
        if (qFuzzyCompare(sweepLength + 1, 1))
            sweepLength = 360;
    }
    else if (!counterClockWise && (sweepLength > 0 || sweepLength < -360))
    {
        sweepLength = -(360 - std::fmod(sweepLength, float(360.0)));
        if (qFuzzyCompare(sweepLength + 1, 1))
            sweepLength = 360;
    }

    QPainterPath arcPath;
    arcPath.arcMoveTo(rect, startAngle);
    arcPath.arcTo(rect, startAngle, sweepLength);


    if (sweepLength > 360.0 || sweepLength < -360.0)
    {
        if (sweepLength < 0) {
            sweepLength += 360.0;
            startAngle -= 360.0;
        } else {
            sweepLength -= 360.0;
            startAngle += 360.0;
        }

        arcPath.arcTo(rect, startAngle, sweepLength);
    }


    if (isPathEmpty())
        path.addPath(arcPath * activeState().transform);
    else
    {
        if (path.elementAt(path.elementCount() - 1).type != QPainterPath::MoveToElement)
            path.connectPath(arcPath * activeState().transform);
        else {


            arcPath = arcPath * activeState().transform;
            path.lineTo(arcPath.elementAt(0));

            if (arcPath.elementCount() > 1)
                for (int i = 1; i < arcPath.elementCount(); i += 3)
                    path.cubicTo(arcPath.elementAt(i), arcPath.elementAt(i+1),
                                 arcPath.elementAt(i+2));
        }
    }
    emptyPath = false;
}
