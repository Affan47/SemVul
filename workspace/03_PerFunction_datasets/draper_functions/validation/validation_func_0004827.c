GetDirectory(JLDirectory &dir, bool include_subdirs)
{
	Data cmd(-1, 8), data(-1, 8), response;
	JLPacket packet(cmd, data, response);

	packet.GetDirectory();
	GetDir(packet, SB_COMMAND_JL_GET_DATA_ENTRY, dir, include_subdirs);
}
