opal_hwloc_pack(opal_buffer_t *buffer, const void *src,
                    int32_t num_vals,
                    opal_data_type_t type)
{

    hwloc_topology_t t, *tarray  = (hwloc_topology_t*)src;
    int rc, i;
    char *xmlbuffer=NULL;
    int len;
    struct hwloc_topology_support *support;

    for (i=0; i < num_vals; i++) {
        t = tarray[i];


        if (0 != hwloc_topology_export_xmlbuffer(t, &xmlbuffer, &len)) {
            return OPAL_ERROR;
        }


        if (OPAL_SUCCESS != (rc = opal_dss.pack(buffer, &xmlbuffer, 1, OPAL_STRING))) {
            free(xmlbuffer);
            return rc;
        }


        if (NULL != xmlbuffer) {
            free(xmlbuffer);
        }


        support = (struct hwloc_topology_support*)hwloc_topology_get_support(t);

        if (OPAL_SUCCESS != (rc = opal_dss.pack(buffer, support->discovery,
                                                sizeof(struct hwloc_topology_discovery_support),
                                                OPAL_BYTE))) {
            return rc;
        }

        if (OPAL_SUCCESS != (rc = opal_dss.pack(buffer, support->cpubind,
                                                sizeof(struct hwloc_topology_cpubind_support),
                                                OPAL_BYTE))) {
            return rc;
        }

        if (OPAL_SUCCESS != (rc = opal_dss.pack(buffer, support->membind,
                                                sizeof(struct hwloc_topology_membind_support),
                                                OPAL_BYTE))) {
            return rc;
        }
    }

    return OPAL_SUCCESS;
}
