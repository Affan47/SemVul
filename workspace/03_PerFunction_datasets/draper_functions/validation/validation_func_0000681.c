DeviceInfo(JLDeviceInfo &info)
{
	Data command(-1, 8), data(-1, 8), response;
	JLPacket packet(command, data, response);

	packet.DeviceInfo();

	m_socket->Packet(packet);

	if( packet.Command() != SB_COMMAND_JL_ACK ) {
		ThrowJLError("JavaLoader::DeviceInfo", packet.Command());
	}

	m_socket->Receive(response);

	Protocol::CheckSize(response, SB_JLPACKET_HEADER_SIZE + SB_JLDEVICEINFO_SIZE);
	MAKE_JLPACKET(rpack, response);

	info.HardwareId = be_btohl(rpack->u.devinfo.hardware_id);
	info.Pin = be_btohl(rpack->u.devinfo.pin);
	info.OsVersion = be_btohl(rpack->u.devinfo.os_version);
	info.VmVersion = be_btohl(rpack->u.devinfo.vm_version);
	info.RadioId = be_btohl(rpack->u.devinfo.radio_id);
	info.VendorId = be_btohl(rpack->u.devinfo.vendor_id);
	info.ActiveWafs = be_btohl(rpack->u.devinfo.active_wafs);

	packet.OsMetrics();

	m_socket->Packet(packet);

	if( packet.Command() != SB_COMMAND_JL_ACK ) {
		ThrowJLError("JavaLoader::DeviceInfo", packet.Command());
	}

	m_socket->Receive(response);
	Protocol::CheckSize(response, SB_JLPACKET_HEADER_SIZE);

	size_t offset = SB_JLPACKET_HEADER_SIZE;
	size_t size = response.GetSize()-offset;
	unsigned char* buf = info.OsMetrics.GetBuffer(size);
	memcpy(buf, response.GetData()+offset, size);
	info.OsMetrics.ReleaseBuffer(size);

	packet.BootromMetrics();

	m_socket->Packet(packet);

	if( packet.Command() != SB_COMMAND_JL_ACK ) {
		ThrowJLError("JavaLoader::DeviceInfo", packet.Command());
	}

	m_socket->Receive(response);
	Protocol::CheckSize(response, SB_JLPACKET_HEADER_SIZE);

	offset = SB_JLPACKET_HEADER_SIZE;
	size = response.GetSize()-offset;
	buf = info.BootromMetrics.GetBuffer(size);
	memcpy(buf, response.GetData()+offset, size);
	info.BootromMetrics.ReleaseBuffer(size);
}
