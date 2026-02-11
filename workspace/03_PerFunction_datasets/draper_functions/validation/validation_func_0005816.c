ssm2518_hw_params(struct snd_pcm_substream *substream,
	struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_codec *codec = dai->codec;
	struct ssm2518 *ssm2518 = snd_soc_codec_get_drvdata(codec);
	unsigned int rate = params_rate(params);
	unsigned int ctrl1, ctrl1_mask;
	int mcs;
	int ret;

	mcs = ssm2518_lookup_mcs(ssm2518, rate);
	if (mcs < 0)
		return mcs;

	ctrl1_mask = SSM2518_SAI_CTRL1_FS_MASK;

	if (rate >= 8000 && rate <= 12000)
		ctrl1 = SSM2518_SAI_CTRL1_FS_8000_12000;
	else if (rate >= 16000 && rate <= 24000)
		ctrl1 = SSM2518_SAI_CTRL1_FS_16000_24000;
	else if (rate >= 32000 && rate <= 48000)
		ctrl1 = SSM2518_SAI_CTRL1_FS_32000_48000;
	else if (rate >= 64000 && rate <= 96000)
		ctrl1 = SSM2518_SAI_CTRL1_FS_64000_96000;
	else
		return -EINVAL;

	if (ssm2518->right_j) {
		switch (params_width(params)) {
		case 16:
			ctrl1 |= SSM2518_SAI_CTRL1_FMT_RJ_16BIT;
			break;
		case 24:
			ctrl1 |= SSM2518_SAI_CTRL1_FMT_RJ_24BIT;
			break;
		default:
			return -EINVAL;
		}
		ctrl1_mask |= SSM2518_SAI_CTRL1_FMT_MASK;
	}


	ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_CLOCK,
				SSM2518_CLOCK_ASR, SSM2518_CLOCK_ASR);
	if (ret < 0)
		return ret;

	ret = regmap_update_bits(ssm2518->regmap, SSM2518_REG_SAI_CTRL1,
				ctrl1_mask, ctrl1);
	if (ret < 0)
		return ret;

	return regmap_update_bits(ssm2518->regmap, SSM2518_REG_POWER1,
				SSM2518_POWER1_MCS_MASK, mcs << 1);
}
