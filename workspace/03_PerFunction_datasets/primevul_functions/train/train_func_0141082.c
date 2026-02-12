sec_recv(uint8 * rdpver)
{
	uint32 sec_flags;
	uint16 channel;
	STREAM s;
	struct stream packet;

	while ((s = mcs_recv(&channel, rdpver)) != NULL)
	{
		packet = *s;
		if (rdpver != NULL)
		{
			if (*rdpver != 3)
			{
				if (*rdpver & 0x80)
				{
					if (!s_check_rem(s, 8)) {
						rdp_protocol_error("sec_recv(), consume fastpath signature from stream would overrun", &packet);
					}

					in_uint8s(s, 8);
					sec_decrypt(s->p, s->end - s->p);
				}
				return s;
			}
		}
		if (g_encryption || (!g_licence_issued && !g_licence_error_result))
		{
			in_uint32_le(s, sec_flags);

			if (g_encryption)
			{
				if (sec_flags & SEC_ENCRYPT)
				{
					if (!s_check_rem(s, 8)) {
						rdp_protocol_error("sec_recv(), consume encrypt signature from stream would overrun", &packet);
					}

					in_uint8s(s, 8);
					sec_decrypt(s->p, s->end - s->p);
				}

				if (sec_flags & SEC_LICENCE_NEG)
				{
					licence_process(s);
					continue;
				}

				if (sec_flags & 0x0400)
				{
					uint8 swapbyte;

					if (!s_check_rem(s, 8)) {
						rdp_protocol_error("sec_recv(), consume redirect signature from stream would overrun", &packet);
					}

					in_uint8s(s, 8);
					sec_decrypt(s->p, s->end - s->p);


					if (s->p[0] == 0 && s->p[1] == 4)
					{


						swapbyte = s->p[0];
						s->p[0] = s->p[2];
						s->p[2] = swapbyte;

						swapbyte = s->p[1];
						s->p[1] = s->p[3];
						s->p[3] = swapbyte;

						swapbyte = s->p[2];
						s->p[2] = s->p[3];
						s->p[3] = swapbyte;
					}
#ifdef WITH_DEBUG

					hexdump(s->p, s->end - s->p);
#endif
				}
			}
			else
			{
				if ((sec_flags & 0xffff) == SEC_LICENCE_NEG)
				{
					licence_process(s);
					continue;
				}
				s->p -= 4;
			}
		}

		if (channel != MCS_GLOBAL_CHANNEL)
		{
			channel_process(s, channel);
			if (rdpver != NULL)
				*rdpver = 0xff;
			return s;
		}

		return s;
	}

	return NULL;
}
