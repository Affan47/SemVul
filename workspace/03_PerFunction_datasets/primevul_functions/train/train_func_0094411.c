static int nfs3_get_attributes_offset(uint32_t *data)
{
	if (ntohl(data[1]) != 0) {


		return 22;
	} else {


		return 1;
	}
}
