orte_dt_quick_print(char **output, char *type_name, char *prefix, void *src, opal_data_type_t real_type)
{
    int8_t *i8;
    int16_t *i16;
    int32_t *i32;
    int64_t *i64;
    uint8_t *ui8;
    uint16_t *ui16;
    uint32_t *ui32;
    uint64_t *ui64;


    *output = NULL;


    if (NULL == src) {
        asprintf(output, "%sData type: %s\tData size: 8-bit\tValue: NULL pointer",
                 (NULL == prefix) ? "" : prefix, type_name);
        return;
    }

    switch(real_type) {
        case OPAL_INT8:
            i8 = (int8_t*)src;
            asprintf(output, "%sData type: %s\tData size: 8-bit\tValue: %d",
                     (NULL == prefix) ? "" : prefix, type_name, (int) *i8);
            break;

        case OPAL_UINT8:
            ui8 = (uint8_t*)src;
            asprintf(output, "%sData type: %s\tData size: 8-bit\tValue: %u",
                     (NULL == prefix) ? "" : prefix, type_name, (unsigned int)*ui8);
            break;

        case OPAL_INT16:
            i16 = (int16_t*)src;
            asprintf(output, "%sData type: %s\tData size: 16-bit\tValue: %d",
                     (NULL == prefix) ? "" : prefix, type_name, (int) *i16);
            break;

        case OPAL_UINT16:
            ui16 = (uint16_t*)src;
            asprintf(output, "%sData type: %s\tData size: 16-bit\tValue: %u",
                     (NULL == prefix) ? "" : prefix, type_name, (unsigned int) *ui16);
            break;

        case OPAL_INT32:
            i32 = (int32_t*)src;
            asprintf(output, "%sData type: %s\tData size: 32-bit\tValue: %ld",
                     (NULL == prefix) ? "" : prefix, type_name, (long) *i32);
            break;

        case OPAL_UINT32:
            ui32 = (uint32_t*)src;
            asprintf(output, "%sData type: %s\tData size: 32-bit\tValue: %lu",
                     (NULL == prefix) ? "" : prefix, type_name, (unsigned long) *ui32);
            break;

        case OPAL_INT64:
            i64 = (int64_t*)src;
            asprintf(output, "%sData type: %s\tData size: 64-bit\tValue: %ld",
                     (NULL == prefix) ? "" : prefix, type_name, (long) *i64);
            break;

        case OPAL_UINT64:
            ui64 = (uint64_t*)src;
            asprintf(output, "%sData type: %s\tData size: 64-bit\tValue: %lu",
                     (NULL == prefix) ? "" : prefix, type_name, (unsigned long) *ui64);
            break;

        default:
            return;
    }

    return;
}
