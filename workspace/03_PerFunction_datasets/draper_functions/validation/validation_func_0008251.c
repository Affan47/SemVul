add_feature (hb_tag_t tag, unsigned int value,
				       hb_ot_map_feature_flags_t flags)
{
  feature_info_t *info = feature_infos.push();
  if (unlikely (!info)) return;
  info->tag = tag;
  info->seq = feature_infos.len;
  info->max_value = value;
  info->flags = flags;
  info->default_value = (flags & F_GLOBAL) ? value : 0;
  info->stage[0] = current_stage[0];
  info->stage[1] = current_stage[1];
}
