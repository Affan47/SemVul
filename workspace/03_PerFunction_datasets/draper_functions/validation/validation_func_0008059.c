passes_bars(mptr)
struct permonst *mptr;
{
    return (boolean) (passes_walls(mptr) || amorphous(mptr) ||
		      is_whirly(mptr) || verysmall(mptr) ||
		      (slithy(mptr) && !bigmonst(mptr)));
}
