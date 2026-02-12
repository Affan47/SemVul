SGeometry::SGeometry(int ncId, int geoVarId)
        : gc_varId(geoVarId), touple_order(0), current_vert_ind(0), cur_geometry_ind(0), cur_part_ind(0)
    {

        char container_name[NC_MAX_NAME + 1];
        memset(container_name, 0, NC_MAX_NAME + 1);


        if(nc_inq_varname(ncId, geoVarId, container_name) != NC_NOERR)
        {
            throw SG_Exception_Existential("new geometry container", "the variable of the given ID");
        }


        container_name_s = std::string(container_name);


        this->type = nccfdriver::getGeometryType(ncId, geoVarId);

        if(this->type == NONE)
        {
            throw SG_Exception_Existential(static_cast<const char*>(container_name), CF_SG_GEOMETRY_TYPE);
        }


        this->gm_varId = INVALID_VAR_ID;
        if(attrf(ncId, geoVarId, CF_GRD_MAPPING, gm_name_s) != "")
        {
            const char * gm_name = gm_name_s.c_str();
            int gmVID;
            if(nc_inq_varid(ncId, gm_name, &gmVID) == NC_NOERR)
            {
                this->gm_varId = gmVID;
            }
        }


        std::string nc_name_s;
        std::string pnc_name_s;
        std::string ir_name_s;
        int pnc_vid = INVALID_VAR_ID;
        int nc_vid = INVALID_VAR_ID;
        int ir_vid = INVALID_VAR_ID;
        int buf;
        size_t bound = 0;
        size_t total_node_count = 0;
        if(attrf(ncId, geoVarId, CF_SG_NODE_COUNT, nc_name_s) != "")
        {
            const char * nc_name = nc_name_s.c_str();
            nc_inq_varid(ncId, nc_name, &nc_vid);
            while(nc_get_var1_int(ncId, nc_vid, &bound, &buf) == NC_NOERR)
            {
                this->node_counts.push_back(buf);
                total_node_count += buf;
                bound++;
            }

        }

        if(attrf(ncId, geoVarId, CF_SG_PART_NODE_COUNT, pnc_name_s) != "")
        {
            const char * pnc_name = pnc_name_s.c_str();
            bound = 0;
            nc_inq_varid(ncId, pnc_name, &pnc_vid);
            while(nc_get_var1_int(ncId, pnc_vid, &bound, &buf) == NC_NOERR)
            {
                this->pnode_counts.push_back(buf);
                bound++;
            }
        }

        if(attrf(ncId, geoVarId, CF_SG_INTERIOR_RING, ir_name_s) != "")
        {
            const char * ir_name = ir_name_s.c_str();
            bound = 0;
            nc_inq_varid(ncId, ir_name, &ir_vid);
            while(nc_get_var1_int(ncId, ir_vid, &bound, &buf) == NC_NOERR)
            {
                bool store = buf == 0 ? false : true;
                this->int_rings.push_back(store);
                bound++;
            }
        }


        if(pnode_counts.size() > 0 && node_counts.size() == 0)
        {
            throw SG_Exception_Dep(static_cast<const char *>(container_name), CF_SG_PART_NODE_COUNT, CF_SG_NODE_COUNT);
        }


        if(int_rings.size() > 0 && pnode_counts.size() == 0)
        {
            throw SG_Exception_Dep(static_cast<const char *>(container_name), CF_SG_INTERIOR_RING, CF_SG_PART_NODE_COUNT);
        }


        if(int_rings.size() > 0)
        {
            if(int_rings.size() != pnode_counts.size())
            {
                throw SG_Exception_Dim_MM(static_cast<const char *>(container_name), CF_SG_INTERIOR_RING, CF_SG_PART_NODE_COUNT);
            }
        }


        if(this->type == POLYGON || this->type == LINE)
        {
            if(node_counts.size() < 1)
            {
                throw SG_Exception_Existential(static_cast<const char*>(container_name), CF_SG_NODE_COUNT);
            }
        }


        size_t rc = 0;
        bound_list.push_back(0);

        if(node_counts.size() > 0)
        {
            for(size_t i = 0; i < node_counts.size() - 1; i++)
            {
                rc = rc + node_counts[i];
                bound_list.push_back(rc);
            }
        }


        std::string cart_s;

        if(attrf(ncId, geoVarId, CF_SG_NODE_COORDINATES, cart_s) == "")
        {
            throw SG_Exception_Existential(container_name, CF_SG_NODE_COORDINATES);
        }


        if(this->node_counts.size() > 0)
        {
            int ind = 0;
            int parts = 0;
            int prog = 0;
            int c = 0;

            for(size_t pcnt = 0; pcnt < pnode_counts.size() ; pcnt++)
            {
                if(prog == 0) pnc_bl.push_back(pcnt);

                if(int_rings.size() > 0 && !int_rings[pcnt])
                    c++;

                prog = prog + pnode_counts[pcnt];
                parts++;

                if(prog == node_counts[ind])
                {
                    ind++;
                    this->parts_count.push_back(parts);
                    if(int_rings.size() > 0)
                        this->poly_count.push_back(c);
                    c = 0;
                    prog = 0; parts = 0;
                }
                else if(prog > node_counts[ind])
                {
                    throw SG_Exception_BadSum(container_name, CF_SG_PART_NODE_COUNT, CF_SG_NODE_COUNT);
                }
            }
        }


        int X = INVALID_VAR_ID;
        int Y = INVALID_VAR_ID;
        int Z = INVALID_VAR_ID;

        char cart[NC_MAX_NAME + 1];
        memset(cart, 0, NC_MAX_NAME + 1);
        strncpy(cart, cart_s.c_str(), NC_MAX_NAME);

        char * dim = strtok(cart,  " ");
        int axis_id = 0;

        while(dim != nullptr)
        {
            if(nc_inq_varid(ncId, dim, &axis_id) == NC_NOERR)
            {


                std::string a_sig;
                attrf(ncId, axis_id, CF_AXIS, a_sig);


                if(a_sig == "X")
                {
                    X = axis_id;
                }
                else if(a_sig == "Y")
                {
                    Y = axis_id;
                }
                else if(a_sig == "Z")
                {
                    Z = axis_id;
                }
                else
                {
                    throw SG_Exception_Dep(container_name, "A node_coordinates variable", CF_AXIS);
                }

                this->touple_order++;
            }
            else
            {
                throw SG_Exception_Existential(container_name, dim);
            }

            dim = strtok(nullptr, " ");
        }


        if(X != INVALID_VAR_ID)
            this->nodec_varIds.push_back(X);
        else
        {
            throw SG_Exception_Existential(container_name, "node_coordinates: X-axis");
        }
        if(Y != INVALID_VAR_ID)
            this->nodec_varIds.push_back(Y);
        else
        {
            throw SG_Exception_Existential(container_name, "node_coordinates: Y-axis");
        }
        if(Z != INVALID_VAR_ID)
            this->nodec_varIds.push_back(Z);


        int all_dim = INVALID_VAR_ID; bool dim_set = false;
        int dimC = 0;

        for(size_t nvitr = 0; nvitr < nodec_varIds.size(); nvitr++)
        {
            dimC = 0;
            nc_inq_varndims(ncId, nodec_varIds[nvitr], &dimC);

            if(dimC != 1)
            {
                throw SG_Exception_Not1D();
            }


            int inter_dim[1];
            if(nc_inq_vardimid(ncId, nodec_varIds[nvitr], inter_dim) != NC_NOERR)
            {
                throw SG_Exception_Existential(container_name, "one or more node_coordinate dimensions");
            }

            if(!dim_set)
            {
                all_dim = inter_dim[0];
            }

            else
            {
                if (inter_dim[0] != all_dim)
                    throw SG_Exception_Dim_MM(container_name, "X, Y", "in general all node coordinate axes");
            }
        }


        if(node_counts.size() > 0)
        {
            size_t diml = 0;
            nc_inq_dimlen(ncId, all_dim, &diml);

            if(diml != total_node_count)
                throw SG_Exception_BadSum(container_name, "node_count", "node coordinate dimension length");
        }


        if(this->touple_order < 2)
        {
            throw SG_Exception_Existential(container_name, "insufficent node coordinates must have at least two axis");
        }


        size_t instance_dim_len = 0;

        if(node_counts.size() >= 1)
        {
            int nc_dims = 0;
            nc_inq_varndims(ncId, nc_vid, &nc_dims);

            if(nc_dims != 1) throw SG_Exception_Not1D();

            int nc_dim_id[1];

            if(nc_inq_vardimid(ncId, nc_vid, nc_dim_id) != NC_NOERR)
            {
                throw SG_Exception_Existential(container_name, "node_count dimension");
            }

            this->inst_dimId = nc_dim_id[0];
        }

        else
        {
            this->inst_dimId = all_dim;
        }

        nc_inq_dimlen(ncId, this->inst_dimId, &instance_dim_len);

        if(instance_dim_len == 0)
            throw SG_Exception_EmptyDim();


        this->inst_dimLen = instance_dim_len;
        this->pt_buffer = std::unique_ptr<Point>(new Point(this->touple_order));
        this->gc_varId = geoVarId;
        this->current_vert_ind = 0;
        this->ncid = ncId;
    }
