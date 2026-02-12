static u32 bond_ip_hash(u32 hash, struct flow_keys *flow)
{
	hash ^= (__force u32)flow_get_u32_dst(flow) ^
		(__force u32)flow_get_u32_src(flow);
	hash ^= (hash >> 16);
	hash ^= (hash >> 8);

	return hash >> 1;
}
