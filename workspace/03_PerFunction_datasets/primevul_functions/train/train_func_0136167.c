unsigned char * SGeometry::serializeToWKB(size_t featureInd, int& wkbSize)
    {
        unsigned char * ret = nullptr;
        int nc = 0; size_t sb = 0;


        if(this->getGeometryType() != POINT)
        {
            nc = node_counts[featureInd];
            sb = bound_list[featureInd];
        }


        switch(this->getGeometryType())
        {
            case POINT:
                wkbSize = 1 + 4 + this->touple_order * 8;
                ret = new uint8_t[wkbSize];
                inPlaceSerialize_Point(this, featureInd, ret);
                break;

            case LINE:
                wkbSize = 1 + 4 + 4 + this->touple_order * 8 * nc;
                ret = new uint8_t[wkbSize];
                inPlaceSerialize_LineString(this, nc, sb, ret);
                break;

            case POLYGON:


                wkbSize = 1 + 4 + 4 + 4 + this->touple_order * 8 * nc;
                ret = new uint8_t[wkbSize];
                inPlaceSerialize_PolygonExtOnly(this, nc, sb, ret);
                break;

            case MULTIPOINT:
                {
                    wkbSize = 1 + 4 + 4 + nc * (1 + 4 + this->touple_order * 8);
                    ret = new uint8_t[wkbSize];

                    void * worker = ret;
                    int8_t header = PLATFORM_HEADER;
                    uint32_t t = this->touple_order == 2 ? wkbMultiPoint :
                                 this->touple_order == 3 ? wkbMultiPoint25D : wkbNone;

                    if(t == wkbNone) throw SG_Exception_BadFeature();


                    worker = memcpy_jump(worker, &header, 1);
                    worker = memcpy_jump(worker, &t, 4);
                    worker = memcpy_jump(worker, &nc, 4);


                    for(int pts = 0; pts < nc; pts++)
                    {
                        worker = inPlaceSerialize_Point(this, static_cast<size_t>(sb + pts), worker);
                    }
                }

                break;

            case MULTILINE:
                {
                    int8_t header = PLATFORM_HEADER;
                    uint32_t t = this->touple_order == 2 ? wkbMultiLineString :
                                this->touple_order == 3 ? wkbMultiLineString25D : wkbNone;

                    if(t == wkbNone) throw SG_Exception_BadFeature();
                    int32_t lc = parts_count[featureInd];
                    size_t seek_begin = sb;
                    size_t pc_begin = pnc_bl[featureInd];
                    wkbSize = 1 + 4 + 4;
                    std::vector<int> pnc;


                    for(int itr = 0; itr < lc; itr++)
                    {
                        pnc.push_back(pnode_counts[pc_begin + itr]);
                         wkbSize += this->touple_order * 8 * pnc[itr] + 1 + 4 + 4;
                    }


                    size_t cur_point = seek_begin;
                    size_t pcount = pnc.size();


                    ret = new uint8_t[wkbSize];
                    void * worker = ret;


                    worker = memcpy_jump(worker, &header, 1);
                    worker = memcpy_jump(worker, &t, 4);
                    worker = memcpy_jump(worker, &pcount, 4);

                    for(size_t itr = 0; itr < pcount; itr++)
                    {
                            worker = inPlaceSerialize_LineString(this, pnc[itr], cur_point, worker);
                            cur_point = pnc[itr] + cur_point;
                    }
                }

                break;

            case MULTIPOLYGON:
                {
                    int8_t header = PLATFORM_HEADER;
                    uint32_t t = this->touple_order == 2 ? wkbMultiPolygon:
                                 this->touple_order == 3 ? wkbMultiPolygon25D: wkbNone;

                    if(t == wkbNone) throw SG_Exception_BadFeature();
                    bool noInteriors = this->int_rings.size() == 0 ? true : false;
                    int32_t rc = parts_count[featureInd];
                    size_t seek_begin = sb;
                    size_t pc_begin = pnc_bl[featureInd];
                    wkbSize = 1 + 4 + 4;
                    std::vector<int> pnc;


                    for(int itr = 0; itr < rc; itr++)
                    {
                        pnc.push_back(pnode_counts[pc_begin + itr]);
                    }


                    if(noInteriors)
                    {
                        for(int ss = 0; ss < rc; ss++)
                        {
                             wkbSize += 8 * this->touple_order * pnc[ss] + 1 + 4 + 4 + 4;
                        }
                    }

                    else
                    {


                        wkbSize += (1 + 4 + 4) * poly_count[featureInd];


                        wkbSize += 4 * parts_count[featureInd];


                        wkbSize += 8 * this->touple_order * nc;
                    }


                    ret = new uint8_t[wkbSize];


                    void * worker = (void*)ret;
                    worker = memcpy_jump(worker, &header, 1);
                    worker = memcpy_jump(worker, &t, 4);

                    if(noInteriors)
                    {
                        size_t cur_point = seek_begin;
                        size_t pcount = pnc.size();
                        worker = memcpy_jump(worker, &pcount, 4);

                        for(size_t itr = 0; itr < pcount; itr++)
                        {
                            worker = inPlaceSerialize_PolygonExtOnly(this, pnc[itr], cur_point, worker);
                            cur_point = pnc[itr] + cur_point;
                        }
                    }

                    else
                    {
                        int32_t polys = poly_count[featureInd];
                        worker = memcpy_jump(worker, &polys, 4);

                        size_t base = pnc_bl[featureInd];
                        size_t seek = seek_begin;
                        size_t ir_base = base + 1;
                        int rc_m = 1;


                        for(int32_t itr = 0; itr < polys; itr++)
                        {
                            rc_m = 1;


                            while(ir_base < int_rings.size() && int_rings[ir_base])
                            {
                                rc_m++;
                                ir_base++;
                            }

                            if(rc_m == 1) ir_base++;

                            std::vector<int> poly_parts;


                            for(int itr_2 = 0; itr_2 < rc_m; itr_2++)
                            {
                                poly_parts.push_back(pnode_counts[base + itr_2]);
                            }

                            worker = inPlaceSerialize_Polygon(this, poly_parts, rc_m, seek, worker);


                            for(size_t itr_3 = 0; itr_3 < poly_parts.size(); itr_3++)
                            {
                                seek += poly_parts[itr_3];
                            }
                        }
                    }
                }
                break;

                default:

                    throw SG_Exception_BadFeature();
                    break;
        }

        return ret;
    }
