nvhdmi_8ch_7x_pcm_prepare(struct hda_pcm_stream *hinfo,
				     struct hda_codec *codec,
				     unsigned int stream_tag,
				     unsigned int format,
				     struct snd_pcm_substream *substream)
{
	int chs;
	unsigned int dataDCC2, channel_id;
	int i;
	struct hdmi_spec *spec = codec->spec;
	struct hda_spdif_out *spdif;
	struct hdmi_spec_per_cvt *per_cvt;

	mutex_lock(&codec->spdif_mutex);
	per_cvt = get_cvt(spec, 0);
	spdif = snd_hda_spdif_out_of_nid(codec, per_cvt->cvt_nid);

	chs = substream->runtime->channels;

	dataDCC2 = 0x2;


	if (codec->spdif_status_reset && (spdif->ctls & AC_DIG1_ENABLE))
		snd_hda_codec_write(codec,
				nvhdmi_master_con_nid_7x,
				0,
				AC_VERB_SET_DIGI_CONVERT_1,
				spdif->ctls & ~AC_DIG1_ENABLE & 0xff);


	snd_hda_codec_write(codec, nvhdmi_master_con_nid_7x, 0,
			AC_VERB_SET_CHANNEL_STREAMID, (stream_tag << 4) | 0x0);


	snd_hda_codec_write(codec, nvhdmi_master_con_nid_7x, 0,
			AC_VERB_SET_STREAM_FORMAT, format);


	if (codec->spdif_status_reset && (spdif->ctls & AC_DIG1_ENABLE)) {
		snd_hda_codec_write(codec,
				nvhdmi_master_con_nid_7x,
				0,
				AC_VERB_SET_DIGI_CONVERT_1,
				spdif->ctls & 0xff);
		snd_hda_codec_write(codec,
				nvhdmi_master_con_nid_7x,
				0,
				AC_VERB_SET_DIGI_CONVERT_2, dataDCC2);
	}

	for (i = 0; i < 4; i++) {
		if (chs == 2)
			channel_id = 0;
		else
			channel_id = i * 2;


		if (codec->spdif_status_reset &&
		(spdif->ctls & AC_DIG1_ENABLE))
			snd_hda_codec_write(codec,
				nvhdmi_con_nids_7x[i],
				0,
				AC_VERB_SET_DIGI_CONVERT_1,
				spdif->ctls & ~AC_DIG1_ENABLE & 0xff);

		snd_hda_codec_write(codec,
				nvhdmi_con_nids_7x[i],
				0,
				AC_VERB_SET_CHANNEL_STREAMID,
				(stream_tag << 4) | channel_id);

		snd_hda_codec_write(codec,
				nvhdmi_con_nids_7x[i],
				0,
				AC_VERB_SET_STREAM_FORMAT,
				format);


		if (codec->spdif_status_reset &&
		(spdif->ctls & AC_DIG1_ENABLE)) {
			snd_hda_codec_write(codec,
					nvhdmi_con_nids_7x[i],
					0,
					AC_VERB_SET_DIGI_CONVERT_1,
					spdif->ctls & 0xff);
			snd_hda_codec_write(codec,
					nvhdmi_con_nids_7x[i],
					0,
					AC_VERB_SET_DIGI_CONVERT_2, dataDCC2);
		}
	}

	nvhdmi_8ch_7x_set_info_frame_parameters(codec, chs);

	mutex_unlock(&codec->spdif_mutex);
	return 0;
}
