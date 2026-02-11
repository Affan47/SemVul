SetZoom( double zoom_x, double zoom_y,
                            double origin_x, double origin_y, bool send_event )
{

    if (zoom_x <= 0)
    {
        zoom_x = double(m_areaClientRect.width)/(m_curveBoundingRect.m_width);
        origin_x = m_curveBoundingRect.m_x;
    }
    if (zoom_y <= 0)
    {
        zoom_y = double(m_areaClientRect.height)/(m_curveBoundingRect.m_height);
        origin_y = m_curveBoundingRect.m_y;
    }

    if (m_fix_aspectratio)
        FixAspectRatio( &zoom_x, &zoom_y, &origin_x, &origin_y );

    double view_width  = m_areaClientRect.width/zoom_x;
    double view_height = m_areaClientRect.height/zoom_y;

    if (!IsFinite(zoom_x, wxT("X zoom is NaN"))) return false;
    if (!IsFinite(zoom_y, wxT("Y zoom is NaN"))) return false;
    if (!IsFinite(origin_x, wxT("X origin is not finite"))) return false;
    if (!IsFinite(origin_y, wxT("Y origin is not finite"))) return false;
    if (!IsFinite(view_width, wxT("Plot width is NaN"))) return false;
    if (!IsFinite(view_height, wxT("Plot height is NaN"))) return false;

    bool x_changed = false, y_changed = false;

    if ((m_viewRect.m_x != origin_x) || (m_zoom.m_x != zoom_x))
        x_changed = true;
    if ((m_viewRect.m_y != origin_y) || (m_zoom.m_y != zoom_y))
        y_changed = true;

    if (x_changed || y_changed)
    {
        if (send_event)
        {
            wxPlotEvent event( wxEVT_PLOT_VIEW_CHANGING, GetId(), this);
            event.SetCurve(m_activeCurve, m_active_index);
            if (!DoSendEvent(event)) return false;
        }

        m_zoom.m_x = zoom_x;
        m_zoom.m_y = zoom_y;

        m_viewRect.m_x = origin_x;
        m_viewRect.m_y = origin_y;
        m_viewRect.m_width = view_width;
        m_viewRect.m_height = view_height;
    }


    Redraw(wxPLOT_REDRAW_PLOT | (x_changed?wxPLOT_REDRAW_XAXIS:0) |
                                (y_changed?wxPLOT_REDRAW_YAXIS:0));

    if (!m_batch_count)
        AdjustScrollBars();

    if (send_event && (x_changed || y_changed))
    {
        wxPlotEvent event( wxEVT_PLOT_VIEW_CHANGED, GetId(), this);
        event.SetCurve(m_activeCurve, m_active_index);
        (void)DoSendEvent( event );
    }

    return true;
}
