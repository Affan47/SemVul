path_to_rect(xy)

int *xy;
{
    int cx,cy,length,width;

    cx = (xy[0] + xy[4])/2;
    cy = (xy[1] + xy[5])/2;
    length = xy[4] - xy[0];
    width = xy[5] - xy[1];
    if (width < 0) width = -width;
    if (length < 0) length = -length;
    fprintf(SymDesc,"B %d %d %d %d;\n",length,width,cx,cy);
}
