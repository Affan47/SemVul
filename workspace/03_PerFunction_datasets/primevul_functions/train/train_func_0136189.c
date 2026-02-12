Point& SGeometry::next_pt()
    {
        if(!this->has_next_pt())
        {
            throw SG_Exception_BadPoint();
        }


        for(int order = 0; order < touple_order; order++)
        {
            Point& pt = *(this->pt_buffer);
            double data;
            size_t full_ind = bound_list[cur_geometry_ind] + current_vert_ind;


            int err = nc_get_var1_double(ncid, nodec_varIds[order], &full_ind, &data);


            if(err != NC_NOERR)
            {
                throw SG_Exception_BadPoint();
            }

            pt[order] = data;
        }

        this->current_vert_ind++;
        return *(this->pt_buffer);
    }
