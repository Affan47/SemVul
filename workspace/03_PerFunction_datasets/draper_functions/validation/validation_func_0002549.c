license_write_platform_challenge_response_packet(rdpLicense* license, STREAM* s, uint8* mac_data)
{

	license_write_binary_blob(s, license->encrypted_platform_challenge);


	license_write_binary_blob(s, license->encrypted_hwid);


	stream_write(s, mac_data, 16);
}
