createLine(const FloatPoint& start, const FloatPoint& end)
{
    Path path;
    if (start.x() == end.x() && start.y() == end.y())
        return path;

    path.moveTo(start);
    path.addLineTo(end);

    return path;
}
