input_vol_put(struct snd_kcontrol *ctl,
			 struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;
	struct dg *data = chip->model_data;
	unsigned int idx = ctl->private_value;
	int changed = 0;
	int ret = 0;

	if (value->value.integer.value[0] < 2 * -12 ||
	    value->value.integer.value[0] > 2 * 12 ||
	    value->value.integer.value[1] < 2 * -12 ||
	    value->value.integer.value[1] > 2 * 12)
		return -EINVAL;
	mutex_lock(&chip->mutex);
	changed = data->input_vol[idx][0] != value->value.integer.value[0] ||
		  data->input_vol[idx][1] != value->value.integer.value[1];
	if (changed) {
		data->input_vol[idx][0] = value->value.integer.value[0];
		data->input_vol[idx][1] = value->value.integer.value[1];
		if (idx == data->input_sel) {
			ret = input_volume_apply(chip,
				data->input_vol[idx][0],
				data->input_vol[idx][1]);
		}
		changed = ret >= 0 ? 1 : ret;
	}
	mutex_unlock(&chip->mutex);
	return changed;
}
