order(gint p)
{
    gint power = 1;
    gint ord = 0;

    while (power < p) {
        power += power;
        ord++;
    }

    return ord;
}
