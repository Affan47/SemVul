static BOOL rdg_send_tunnel_request(rdpRdg* rdg)
{
	wStream* s;
	BOOL status;
	UINT32 packetSize = 16;
	UINT16 fieldsPresent = 0;
	WCHAR* PAACookie = NULL;
	int PAACookieLen = 0;

	if (rdg->extAuth == HTTP_EXTENDED_AUTH_PAA)
	{
		PAACookieLen =
		    ConvertToUnicode(CP_UTF8, 0, rdg->settings->GatewayAccessToken, -1, &PAACookie, 0);

		if (!PAACookie || (PAACookieLen < 0) || (PAACookieLen > UINT16_MAX / 2))
		{
			free(PAACookie);
			return FALSE;
		}

		packetSize += 2 + (UINT32)PAACookieLen * sizeof(WCHAR);
		fieldsPresent = HTTP_TUNNEL_PACKET_FIELD_PAA_COOKIE;
	}

	s = Stream_New(NULL, packetSize);

	if (!s)
	{
		free(PAACookie);
		return FALSE;
	}

	Stream_Write_UINT16(s, PKT_TYPE_TUNNEL_CREATE);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT32(s, packetSize);
	Stream_Write_UINT32(s, HTTP_CAPABILITY_TYPE_QUAR_SOH);
	Stream_Write_UINT16(s, fieldsPresent);
	Stream_Write_UINT16(s, 0);

	if (PAACookie)
	{
		Stream_Write_UINT16(s, (UINT16)PAACookieLen * 2);
		Stream_Write_UTF16_String(s, PAACookie, (size_t)PAACookieLen);
	}

	Stream_SealLength(s);
	status = rdg_write_packet(rdg, s);
	Stream_Free(s, TRUE);
	free(PAACookie);

	if (status)
	{
		rdg->state = RDG_CLIENT_STATE_TUNNEL_CREATE;
	}

	return status;
}
