e1000_hash_mc_addr(struct e1000_hw *hw,
                   uint8_t *mc_addr)
{
    uint32_t hash_value = 0;


    switch (hw->mc_filter_type) {


    case 0:
        if (hw->mac_type == e1000_ich8lan) {

            hash_value = ((mc_addr[4] >> 6) | (((uint16_t) mc_addr[5]) << 2));
        } else {

            hash_value = ((mc_addr[4] >> 4) | (((uint16_t) mc_addr[5]) << 4));
        }
        break;
    case 1:
        if (hw->mac_type == e1000_ich8lan) {

            hash_value = ((mc_addr[4] >> 5) | (((uint16_t) mc_addr[5]) << 3));
        } else {

            hash_value = ((mc_addr[4] >> 3) | (((uint16_t) mc_addr[5]) << 5));
        }
        break;
    case 2:
        if (hw->mac_type == e1000_ich8lan) {

            hash_value = ((mc_addr[4] >> 4) | (((uint16_t) mc_addr[5]) << 4));
        } else {

            hash_value = ((mc_addr[4] >> 2) | (((uint16_t) mc_addr[5]) << 6));
        }
        break;
    case 3:
        if (hw->mac_type == e1000_ich8lan) {

            hash_value = ((mc_addr[4] >> 2) | (((uint16_t) mc_addr[5]) << 6));
        } else {

            hash_value = ((mc_addr[4]) | (((uint16_t) mc_addr[5]) << 8));
        }
        break;
    }

    hash_value &= 0xFFF;
    if (hw->mac_type == e1000_ich8lan)
        hash_value &= 0x3FF;

    return hash_value;
}
