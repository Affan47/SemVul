Boundary_find_bounding_region(Boundary *boundary){
    register Region *region = Region_create_blank();
    register gint i, qmin, qmax;
    register Boundary_Row *boundary_row;
    register Boundary_Interval *interval;
    g_assert(boundary->row_list->len);

    boundary_row = boundary->row_list->pdata[0];
    region->target_start = boundary_row->target_pos;

    interval = boundary_row->interval_list->pdata[0];
    qmin = interval->query_pos;

    interval = boundary_row->interval_list->pdata
              [boundary_row->interval_list->len-1];
    qmax = interval->query_pos + interval->length;

    boundary_row = boundary->row_list->pdata[boundary->row_list->len-1];
    region->target_length = boundary_row->target_pos;
    for(i = 1; i < boundary->row_list->len; i++){
        boundary_row = boundary->row_list->pdata[i];
        g_assert(boundary_row->interval_list->len);

        interval = boundary_row->interval_list->pdata[0];
        if(qmin > interval->query_pos)
            qmin = interval->query_pos;

        interval = boundary_row->interval_list->pdata
                  [boundary_row->interval_list->len-1];
        if(qmax < (interval->query_pos + interval->length))
            qmax = interval->query_pos + interval->length;
        }
    region->query_start = qmin;
    region->query_length = qmax - qmin;
    return region;
    }
