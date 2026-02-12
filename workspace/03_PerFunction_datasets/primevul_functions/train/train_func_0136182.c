void SGeometry_PropertyScanner::open(int container_id)
    {

        if(nc_inq_var(this->nc, container_id, nullptr, nullptr, nullptr, nullptr, nullptr) != NC_NOERR)
        {
            return;
        }


        char contname[NC_MAX_NAME + 1];
        memset(contname, 0, NC_MAX_NAME + 1);
        if(nc_inq_varname(this->nc, container_id, contname) != NC_NOERR)
        {
            return;
        }


        int varCount = 0;
        if(nc_inq_nvars(this->nc, &varCount) != NC_NOERR)
        {
            return;
        }

        for(int curr = 0; curr < varCount; curr++)
        {
            size_t contname2_len = 0;


            if(nc_inq_attlen(this->nc, curr, CF_SG_GEOMETRY, &contname2_len) != NC_NOERR)
            {

                continue;
            }


            if(contname2_len == 0) continue;


            char buf[NC_MAX_CHAR + 1];
            memset(buf, 0, NC_MAX_CHAR + 1);

            if(nc_get_att_text(this->nc, curr, CF_SG_GEOMETRY, buf)!= NC_NOERR)
            {
                continue;
            }


            if(!strcmp(contname, buf))
            {
                char property_name[NC_MAX_NAME];
                nc_inq_varname(this->nc, curr, property_name);

                std::string n(property_name);
                v_ids.push_back(curr);
                v_headers.push_back(n);
            }
        }
    }
