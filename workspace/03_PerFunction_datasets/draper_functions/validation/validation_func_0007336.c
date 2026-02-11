shift_up(ScmObj *elts, int root, int nelts,
                            int (*cmp)(ScmObj, ScmObj, ScmObj), ScmObj data)
{
    int l = root+1, maxchild;
    while (l*2 <= nelts) {
        if (l*2 == nelts) {
            maxchild = nelts-1;
        } else if (cmp(elts[l*2-1], elts[l*2], data) < 0) {
            maxchild = l*2;
        } else {
            maxchild = l*2-1;
        }
        if (cmp(elts[l-1], elts[maxchild], data) < 0) {
            ScmObj tmp = elts[maxchild];
            elts[maxchild] = elts[l-1];
            elts[l-1] = tmp;
            l = maxchild+1;
        } else {
            break;
        }
    }
}
