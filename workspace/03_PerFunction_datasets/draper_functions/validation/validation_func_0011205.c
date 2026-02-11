SendPacket(int in_cl, drone_packet *in_pack) {
	int nlen = kis_ntoh32(in_pack->data_len) + sizeof(drone_packet);

	int ret = 0;

	ret = netserver->WriteData(in_cl, in_pack, nlen);

	if (ret == -2) {
		ostringstream osstr;
		osstr << "Kismet drone server client fd " << in_cl << " ring buffer "
			"full, throwing away packet";
		_MSG(osstr.str(), (MSGFLAG_INFO | MSGFLAG_LOCAL));
		return 0;
	}

	return ret;
}
