addToBuffer(const video::S3DVertex& v, SMeshBuffer* Buffer) const
{
	const s32 tnidx = Buffer->Vertices.linear_reverse_search(v);
	const bool alreadyIn = (tnidx != -1);
	u16 nidx = (u16)tnidx;
	if (!alreadyIn)
	{
		nidx = (u16)Buffer->Vertices.size();
		Buffer->Indices.push_back(nidx);
		Buffer->Vertices.push_back(v);
	}
	else
		Buffer->Indices.push_back(nidx);
}
