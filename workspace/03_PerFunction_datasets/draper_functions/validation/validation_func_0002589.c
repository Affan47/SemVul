cos_dict_delete(cos_dict_t *pcd, const byte *key_data, uint key_size)
{
    cos_dict_element_t *pcde = pcd->elements, *prev = 0;

    for (; pcde; pcde = pcde->next) {
        if (!bytes_compare(key_data, key_size, pcde->key.data, pcde->key.size)) {
            cos_dict_element_free(pcd, pcde, "cos_dict_delete");
            if (prev != 0)
                prev->next = pcde->next;
            else
                pcd->elements = pcde->next;
            return 0;
        }
        prev = pcde;
    }
    return -1;
}
