rmaps_lama_convert_lama_key_to_hwloc_key(rmaps_lama_level_type_t lama_key, hwloc_obj_type_t *hwloc_key, int *depth)
{
    *depth = 0;

    switch(lama_key) {
    case LAMA_LEVEL_MACHINE:
        *hwloc_key = HWLOC_OBJ_MACHINE;
        break;

#if 0
    case LAMA_LEVEL_BOARD:
        *hwloc_key = HWLOC_OBJ_MACHINE;
        break;
#endif
    case LAMA_LEVEL_SOCKET:
        *hwloc_key = HWLOC_OBJ_SOCKET;
        break;
    case LAMA_LEVEL_CORE:
        *hwloc_key = HWLOC_OBJ_CORE;
        break;
    case LAMA_LEVEL_PU:
        *hwloc_key = HWLOC_OBJ_PU;
        break;
    case LAMA_LEVEL_CACHE_L1:
        *hwloc_key = HWLOC_OBJ_CACHE;
        *depth = 1;
        break;
    case LAMA_LEVEL_CACHE_L2:
        *hwloc_key = HWLOC_OBJ_CACHE;
        *depth = 2;
        break;
    case LAMA_LEVEL_CACHE_L3:
        *hwloc_key = HWLOC_OBJ_CACHE;
        *depth = 3;
        break;
    case LAMA_LEVEL_NUMA:
        *hwloc_key = HWLOC_OBJ_NODE;
        break;
    default:
        *hwloc_key = HWLOC_OBJ_TYPE_MAX;
        break;
    }

    return ORTE_SUCCESS;
}
