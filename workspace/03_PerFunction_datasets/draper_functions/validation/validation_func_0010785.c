dxf_lwpolyline_init
(
        DxfLWPolyline *dxf_lwpolyline

)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif

        if (dxf_lwpolyline == NULL)
        {
                fprintf (stderr,
                  (_("Warning in %s () a NULL pointer was passed.\n")),
                  __FUNCTION__);
                dxf_lwpolyline = dxf_lwpolyline_new ();
        }
        if (dxf_lwpolyline == NULL)
        {
              fprintf (stderr,
                (_("Error in %s () could not allocate memory for a DxfLWPolyline struct.\n")),
                __FUNCTION__);
              return (NULL);
        }
        dxf_lwpolyline->id_code = 0;
        dxf_lwpolyline->linetype = strdup (DXF_DEFAULT_LINETYPE);
        dxf_lwpolyline->layer = strdup (DXF_DEFAULT_LAYER);
        dxf_lwpolyline->elevation = 0.0;
        dxf_lwpolyline->thickness = 0.0;
        dxf_lwpolyline->linetype_scale = DXF_DEFAULT_LINETYPE_SCALE;
        dxf_lwpolyline->visibility = DXF_DEFAULT_VISIBILITY;
        dxf_lwpolyline->constant_width = 0.0;
        dxf_lwpolyline->color = DXF_COLOR_BYLAYER;
        dxf_lwpolyline->paperspace = DXF_MODELSPACE;
        dxf_lwpolyline->flag = 0;
        dxf_lwpolyline->number_vertices = 0;
        dxf_lwpolyline->extr_x0 = 0.0;
        dxf_lwpolyline->extr_y0 = 0.0;
        dxf_lwpolyline->extr_z0 = 0.0;
        dxf_lwpolyline->dictionary_owner_soft = strdup ("");
        dxf_lwpolyline->dictionary_owner_hard = strdup ("");
        dxf_lwpolyline->vertices = (DxfVertex *) dxf_vertex_new ();
        dxf_lwpolyline->next = NULL;
#if DEBUG
        DXF_DEBUG_END
#endif
        return (dxf_lwpolyline);
}
