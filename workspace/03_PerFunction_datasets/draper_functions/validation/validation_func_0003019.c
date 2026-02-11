epr_is_little_endian_order(void)
{
    uint le_value = EPR_LE_MAGIC_NUMBER;
    return (((uchar*)(&le_value))[0] == EPR_LE_MAGIC_BYTE_0)
        && (((uchar*)(&le_value))[1] == EPR_LE_MAGIC_BYTE_1)
        && (((uchar*)(&le_value))[2] == EPR_LE_MAGIC_BYTE_2)
        && (((uchar*)(&le_value))[3] == EPR_LE_MAGIC_BYTE_3);
}
