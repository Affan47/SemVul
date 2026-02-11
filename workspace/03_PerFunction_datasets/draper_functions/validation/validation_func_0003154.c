df_search(hwloc_topology_t topo,
                             hwloc_obj_t start,
                             hwloc_obj_type_t target,
                             unsigned cache_level,
                             unsigned int nobj,
                             opal_hwloc_resource_type_t rtype,
                             unsigned int *idx,
                             unsigned int *num_objs)
{
    unsigned k;
    hwloc_obj_t obj;
    opal_hwloc_obj_data_t *data;

    if (target == start->type) {
        if (HWLOC_OBJ_CACHE == start->type && cache_level != start->attr->cache.depth) {
            goto notfound;
        }
        if (OPAL_HWLOC_LOGICAL == rtype) {


            if (NULL != num_objs) {

                *num_objs += 1;
            } else if (*idx == nobj) {

                return start;
            }
            *idx += 1;
            return NULL;
        }
        if (OPAL_HWLOC_PHYSICAL == rtype) {


            if (NULL != num_objs) {

                if (*num_objs < (unsigned int)start->os_index) {
                    *num_objs = (unsigned int)start->os_index;
                }
            } else if (*idx == nobj) {

                return start;
            }
            *idx += 1;
            return NULL;
        }
        if (OPAL_HWLOC_AVAILABLE == rtype) {

            data = (opal_hwloc_obj_data_t*)start->userdata;
            if (NULL == data) {
                data = OBJ_NEW(opal_hwloc_obj_data_t);
                start->userdata = (void*)data;
            }


            if (UINT_MAX != data->idx && data->idx == nobj) {
                return start;
            }

            if (NULL == data->available) {
                data->available = opal_hwloc_base_get_available_cpus(topo, start);
            }
            if (NULL != data->available && !hwloc_bitmap_iszero(data->available)) {
                if (NULL != num_objs) {
                    *num_objs += 1;
                } else if (*idx == nobj) {

                    data->idx = *idx;
                    return start;
                }
                *idx += 1;
            }
            return NULL;
        }

        return NULL;
    }

 notfound:
    for (k=0; k < start->arity; k++) {
        obj = df_search(topo, start->children[k], target, cache_level, nobj, rtype, idx, num_objs);
        if (NULL != obj) {
            return obj;
        }
    }

    return NULL;
}
