compute_padding(section *s)
{
    return (s->y0 < 0 || s->y1 < 0 ? -2 :
            s->y1 < fixed_half ? 0 :
            s->y0 > fixed_half ? 1 :
            fixed_half - s->y0 < s->y1 - fixed_half ? 1 : 0);
}
