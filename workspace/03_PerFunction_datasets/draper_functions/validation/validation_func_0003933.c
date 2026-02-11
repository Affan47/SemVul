ajGraphOpenFlags(AjPGraph thys, PLFLT xmin, PLFLT xmax,
                      PLFLT ymin, PLFLT ymax, ajint flags)
{
    AjPTime ajtime;

    ajGraphicsSetDevice(thys);


    if(thys)
        (*graphType[thys->displaytype].GOpen)(thys,
                                              graphType[thys->displaytype].Ext);

    if( ajStrGetLen(thys->title) <=1)
    {
        ajtime = ajTimeNewToday();
        ajStrAppendC(&thys->title,
                     ajFmtString("%S (%D)",ajUtilGetProgram(),ajtime));
        ajTimeDel(&ajtime);
    }

    GraphSetName(thys, thys->outputfile,
                 graphType[thys->displaytype].Ext);
    thys->xstart = xmin;
    thys->xend = xmax;
    thys->ystart = ymin;
    thys->yend = ymax;

    GraphColourBack();
    GraphInit(thys);
    GraphColourFore();
    ajGraphicsPlenv(xmin, xmax , ymin, ymax , flags);

    return;
}
