vs_alloc(len)
int     len;
{
    register struct vstring *vp;

    if (len < 1
	|| (vp = (struct vstring *) malloc(sizeof(struct vstring))) == 0
	|| (vp->str = malloc(len)) == 0)
	return (0);
    vp->last = vp->str + len - 1;
    return (vp);
}
