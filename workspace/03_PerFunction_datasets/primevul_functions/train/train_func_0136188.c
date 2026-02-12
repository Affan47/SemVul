size_t SGeometry::get_geometry_count()
    {
        if(type == POINT)
        {


            if(this->nodec_varIds.size() < 1) return 0;


            int dims;
            if(nc_inq_varndims(this->ncid, nodec_varIds[0], &dims) != NC_NOERR) return 0;
            if(dims != 1) return 0;


            int index;
            if(nc_inq_vardimid(this->ncid, nodec_varIds[0], &index) != NC_NOERR)
            {
                return 0;
            }


            size_t len;
            if(nc_inq_dimlen(this->ncid, index, &len) != NC_NOERR)
            {
                return 0;
            }
            return len;
        }

        else return this->node_counts.size();
    }
