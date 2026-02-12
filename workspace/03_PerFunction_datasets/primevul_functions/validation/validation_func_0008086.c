void rfbScaledCorrection(rfbScreenInfoPtr from, rfbScreenInfoPtr to, int *x, int *y, int *w, int *h, const char *function)
{
    double x1,y1,w1,h1, x2, y2, w2, h2;
    double scaleW = ((double) to->width) / ((double) from->width);
    double scaleH = ((double) to->height) / ((double) from->height);


    if (from==to) return;

    x1 = ((double) *x) * scaleW;
    y1 = ((double) *y) * scaleH;
    w1 = ((double) *w) * scaleW;
    h1 = ((double) *h) * scaleH;


    x2 = FLOOR(x1);
    y2 = FLOOR(y1);


    w2 = CEIL(w1 + ( x1 - x2 ));
    h2 = CEIL(h1 + ( y1 - y2 ));


    *x = (int)x2;
    *y = (int)y2;
    *w = (int)w2;
    *h = (int)h2;


    if (*w==0) (*w)++;
    if (*h==0) (*h)++;

    if (*x+*w > to->width)  *w=to->width - *x;
    if (*y+*h > to->height) *h=to->height - *y;
}
