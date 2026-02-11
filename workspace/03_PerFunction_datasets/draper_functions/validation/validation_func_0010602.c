cos_array_put(cos_array_t *pca, long index, const cos_value_t *pvalue)
{
    gs_memory_t *mem = COS_OBJECT_MEMORY(pca);
    cos_value_t value;
    int code = cos_copy_element_value(&value, mem, pvalue, true);

    if (code >= 0) {
        code = cos_array_put_no_copy(pca, index, &value);
        if (code < 0)
            cos_uncopy_element_value(&value, mem, true);
    }
    pca->md5_valid = false;
    return code;
}
