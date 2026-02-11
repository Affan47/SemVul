gf_codec_use_codec(GF_Codec *codec, GF_ObjectManager *odm)
{
	GF_Codec *tmp;
	if (!codec->decio) return NULL;
	GF_SAFEALLOC(tmp, GF_Codec);
	tmp->type = codec->type;
	tmp->inChannels = gf_list_new();
	tmp->Status = GF_ESM_CODEC_STOP;
	tmp->odm = odm;
	tmp->flags = codec->flags | GF_ESM_CODEC_IS_USE;
	tmp->decio = codec->decio;
	tmp->process = codec->process;
	return tmp;
}
