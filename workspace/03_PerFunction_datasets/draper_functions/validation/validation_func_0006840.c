histemple_at(struct monst *priest, xchar x, xchar y)
{
    return ((EPRI(priest)->shroom == *in_rooms(x, y, TEMPLE)) &&
            on_level(&(EPRI(priest)->shrlevel), &u.uz));
}
