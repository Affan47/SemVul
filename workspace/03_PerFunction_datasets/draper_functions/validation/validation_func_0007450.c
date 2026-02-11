get_bounding_box(int x, int y, int &xmin, int &ymin, int &xmax, int &ymax) const {
        e4_assert(points);
        xmin = ymin = INT_MAX;
        xmax = ymax = INT_MIN;
        for (int p=0; p<points; p++) {
            if (xpos[p]<xmin)      { xmin = xpos[p]; }
            else if (xpos[p]>xmax) { xmax = xpos[p]; }
            if (ypos[p]<ymin)      { ymin = ypos[p]; }
            else if (ypos[p]>ymax) { ymax = ypos[p]; }
        }

        xmin += x; xmax +=x;
        ymin += y; ymax +=y;
    }


}
