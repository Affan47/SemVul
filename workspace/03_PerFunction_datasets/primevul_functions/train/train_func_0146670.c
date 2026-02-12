x_order(const active_line *lp1, const active_line *lp2)
{
    bool s1;

    INCR(order);
    if (!lp1 || !lp2 || lp1->x_current < lp2->x_current)
        return -1;
    else if (lp1->x_current > lp2->x_current)
        return 1;


    if ((s1 = lp1->start.x < lp1->end.x) != (lp2->start.x < lp2->end.x))
        return (s1 ? 1 : -1);


    INCR(slow_order);
    {
        fixed dx1 = lp1->end.x - lp1->start.x,
            dy1 = lp1->end.y - lp1->start.y;
        fixed dx2 = lp2->end.x - lp2->start.x,
            dy2 = lp2->end.y - lp2->start.y;
        double diff = (double)dx1 * dy2 - (double)dx2 * dy1;

        return (diff < 0 ? -1 : diff > 0 ? 1 : 0);
    }
}
