rd_messages(u32b version)
{
	int i;
	char buf[128];
	u16b tmp16u;

	s16b num;


	rd_s16b(&num);


	for (i = 0; i < num; i++)
	{

		rd_string(buf, sizeof(buf));


		rd_u16b(&tmp16u);


		message_add(buf, tmp16u);
	}

	return 0;
}
