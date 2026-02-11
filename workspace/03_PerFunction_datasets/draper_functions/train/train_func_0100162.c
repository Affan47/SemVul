find_name_in_header(type8s * name, type8 upper)
{
	type16s header_pos = 0;
	type8s pic_name[8];
	type8 i;

	for (i = 0; i < 8; i++)
		pic_name[i] = 0;
	strncpy(pic_name,name,6);
	if (upper)
	{
		for (i = 0; i < 8; i++)
			pic_name[i] = (type8s)toupper(pic_name[i]);
	}

	while (header_pos < gfx2_hsize)
	{
		type8s* hname = (type8s*)(gfx2_hdr + header_pos);
		if (strncmp(hname,pic_name,6) == 0)
			return header_pos;
		header_pos += 16;
	}
	return -1;
}
