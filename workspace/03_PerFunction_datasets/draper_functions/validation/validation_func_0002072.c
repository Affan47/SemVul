AM_drawThings(void)
{
    int         i;
    mobj_t*     t;
    int         colors;
    fixed_t     radius;


    for(i = 0; i < numsectors; i++)
    {
        t = sectors[i].thinglist;
        while(t)
        {
            radius = t->radius;

            if(t->flags & (MF_MISSILE|MF_SPECIAL))
            {
                colors = MISSILECOLORS;
            }
            else if(t->flags & MF_COUNTKILL)
            {
                colors = SHOOTABLECOLORS;
            }
            else
            {
                colors = THINGCOLORS;
                radius = (16<<FRACBITS);
            }

            AM_drawLineCharacter (thintriangle_guy, arrlen(thintriangle_guy),
                radius, t->angle, colors, t->x, t->y);

            t = t->snext;
        }
    }
}
