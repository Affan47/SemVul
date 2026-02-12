status_put_floating(stream * s, double v)
{

    int vf = (int)(v * 100 + ((v < 0) ? -0.5 : 0.5));

    if (vf / 100 * 100 == vf)
        stprintf(s, "%d", vf / 100);
    else if (vf / 10 * 10 == vf)
        stprintf(s, "%.1f", v);
    else
        stprintf(s, "%.2f", v);
}
