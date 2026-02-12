void GfxRadialShading::getParameterRange(double *lower, double *upper, double xMin, double yMin, double xMax, double yMax)
{
    double cx, cy, cr, dx, dy, dr;
    double a, x_focus, y_focus;
    double mindr, minx, miny, maxx, maxy;
    double range[2];
    bool valid;


    if (xMin >= xMax || yMin >= yMax || (fabs(r0 - r1) < RADIAL_EPSILON && (std::min<double>(r0, r1) < RADIAL_EPSILON || std::max<double>(fabs(x0 - x1), fabs(y0 - y1)) < 2 * RADIAL_EPSILON))) {
        *lower = *upper = 0;
        return;
    }

    range[0] = range[1] = 0;
    valid = false;

    x_focus = y_focus = 0;

    cx = x0;
    cy = y0;
    cr = r0;
    dx = x1 - cx;
    dy = y1 - cy;
    dr = r1 - cr;


    xMin -= cx;
    yMin -= cy;
    xMax -= cx;
    yMax -= cy;


    xMin -= RADIAL_EPSILON;
    yMin -= RADIAL_EPSILON;
    xMax += RADIAL_EPSILON;
    yMax += RADIAL_EPSILON;


    minx = xMin - RADIAL_EPSILON;
    miny = yMin - RADIAL_EPSILON;
    maxx = xMax + RADIAL_EPSILON;
    maxy = yMax + RADIAL_EPSILON;


    mindr = -(cr + RADIAL_EPSILON);


    if (fabs(dr) >= RADIAL_EPSILON) {
        double t_focus;

        t_focus = -cr / dr;
        x_focus = t_focus * dx;
        y_focus = t_focus * dy;
        if (minx <= x_focus && x_focus <= maxx && miny <= y_focus && y_focus <= maxy) {
            valid = radialExtendRange(range, t_focus, valid);
        }
    }


    radialEdge(xMin - cr, dx + dr, dy, miny, maxy, dr, mindr, valid, range);
    radialEdge(xMax + cr, dx - dr, dy, miny, maxy, dr, mindr, valid, range);
    radialEdge(yMin - cr, dy + dr, dx, minx, maxx, dr, mindr, valid, range);
    radialEdge(yMax + cr, dy - dr, dx, minx, maxx, dr, mindr, valid, range);


    a = dx * dx + dy * dy - dr * dr;
    if (fabs(a) < RADIAL_EPSILON * RADIAL_EPSILON) {
        double b;


        assert(fabs(dr) >= RADIAL_EPSILON);


        if (dr < 0) {
            valid = radialExtendRange(range, 0, valid);
        } else {
            valid = radialExtendRange(range, 1, valid);
        }


        radialCorner1(xMin, yMin, b, dx, dy, cr, dr, mindr, valid, range);
        radialCorner1(xMin, yMax, b, dx, dy, cr, dr, mindr, valid, range);
        radialCorner1(xMax, yMin, b, dx, dy, cr, dr, mindr, valid, range);
        radialCorner1(xMax, yMax, b, dx, dy, cr, dr, mindr, valid, range);
    } else {
        double inva, b, c, d;

        inva = 1 / a;


        radialCorner2(xMin, yMin, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);
        radialCorner2(xMin, yMax, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);
        radialCorner2(xMax, yMin, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);
        radialCorner2(xMax, yMax, a, b, c, d, dx, dy, cr, inva, dr, mindr, valid, range);
    }

    *lower = std::max<double>(0., std::min<double>(1., range[0]));
    *upper = std::max<double>(0., std::min<double>(1., range[1]));
}
