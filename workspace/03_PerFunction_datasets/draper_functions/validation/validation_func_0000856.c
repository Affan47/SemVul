wip_read_graph_tags(GNode *node, gpointer header)
{
    WIPTag *tag;
    WIPGraph *graphheader;
    const guchar *p;

    tag = node->data;
    graphheader = (WIPGraph *)header;
    p = tag->data;
    if (!strncmp(tag->name, "SizeX", 5))
        graphheader->sizex = gwy_get_gint32_le(&p);
    else if (!strncmp(tag->name, "SizeY", 5))
        graphheader->sizey = gwy_get_gint32_le(&p);
    else if (!strncmp(tag->name, "SizeGraph", 9))
        graphheader->sizegraph = gwy_get_gint32_le(&p);
    else if (!strncmp(tag->name, "SpaceTransformationID", 21))
        graphheader->spacetransformid = gwy_get_gint32_le(&p);
    else if (!strncmp(tag->name, "XTransformationID", 17))
        graphheader->xtransformid = gwy_get_gint32_le(&p);
    else if (!strncmp(tag->name, "XInterpretationID", 17))
        graphheader->xinterpid = gwy_get_gint32_le(&p);
    else if (!strncmp(tag->name, "ZInterpretationID", 17))
        graphheader->zinterpid = gwy_get_gint32_le(&p);
    else if (!strncmp(tag->name, "Dimension", 9))
        graphheader->dimension = gwy_get_gint32_le(&p);
    else if (!strncmp(tag->name, "DataType", 8))
        graphheader->datatype = (WIPDataType)gwy_get_gint32_le(&p);
    else if (!strncmp(tag->name, "Ranges", 6)) {
        graphheader->xrange = gwy_get_gint32_le(&p);
        graphheader->yrange = gwy_get_gint32_le(&p);
    }
    else if (!strncmp(tag->name, "Data", 4)) {
        graphheader->data = p;
        graphheader->datasize = (gsize)(tag->data_end-tag->data_start);
    }

    return FALSE;
}
