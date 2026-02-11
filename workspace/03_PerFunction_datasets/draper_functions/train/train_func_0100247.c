equals (const event* e)
{

    map_event *t = (map_event *) e;

    if (submap != -1 && t->submap != submap) return false;
    if (x != -1 && t->x != x) return false;
    if (y != -1 && t->y != y) return false;
    if (dir != -1 && t->dir != dir) return false;
    if (map != -1 && t->map != map) return false;
    if (c && t->c != c) return false;

    return true;
}
