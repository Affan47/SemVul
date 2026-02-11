dxf_hatch_boundary_path_edge_spline_copy_knot_values
(
        DxfHatchBoundaryPathEdgeSpline *dxf_hatch_boundary_path_edge_spline,

        double *knot_values[DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS]

)
{
#if DEBUG
        DXF_DEBUG_BEGIN
#endif
        int i;

        if (dxf_hatch_boundary_path_edge_spline == NULL)
        {
                fprintf (stderr,
                  (_("Error in %s () received a NULL pointer value in dxf_hatch_boundary_path_edge_spline.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        if (dxf_hatch_boundary_path_edge_spline->number_of_knots > DXF_MAX_HATCH_BOUNDARY_PATH_EDGE_SPLINE_KNOTS)
        {
                fprintf (stderr,
                  (_("Error in %s () resulted in a array pointer overflow.\n")),
                  __FUNCTION__);
                return (EXIT_FAILURE);
        }
        for (i = 0; i < dxf_hatch_boundary_path_edge_spline->number_of_knots; i++)
        {
                *knot_values[i] = dxf_hatch_boundary_path_edge_spline->knots[i];
        }
#if DEBUG
        DXF_DEBUG_END
#endif
        return (EXIT_SUCCESS);
}
