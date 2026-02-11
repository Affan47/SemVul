xgbe_update_vlan_hash_table(struct xgbe_prv_data *pdata)
{
	u32 crc;
	u16 vid;
	__le16 vid_le;
	u16 vlan_hash_table = 0;


	for_each_set_bit(vid, pdata->active_vlans, VLAN_N_VID) {

		vid_le = cpu_to_le16(vid);
		crc = bitrev32(~xgbe_vid_crc32_le(vid_le)) >> 28;

		vlan_hash_table |= (1 << crc);
	}


	XGMAC_IOWRITE_BITS(pdata, MAC_VLANHTR, VLHT, vlan_hash_table);

	return 0;
}
