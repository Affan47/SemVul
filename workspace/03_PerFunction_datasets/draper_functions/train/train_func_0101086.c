calcRouteDist(void)
{
    double (*dist)(const Point& a, const Point& b) =
            (_type == ConnType_PolyLine) ? euclideanDist : manhattanDist;

    _route_dist = 0;
    for (size_t i = 1; i < _route.size(); ++i)
    {
        _route_dist += dist(_route.at(i), _route.at(i - 1));
    }
}
