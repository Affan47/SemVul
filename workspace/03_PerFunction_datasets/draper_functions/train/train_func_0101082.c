unit_flag_rule_name(enum unit_flag_id id)
{
  fc_assert_ret_val(ARRAY_SIZE(flag_names) == F_USER_FLAG_1, NULL);
  fc_assert_ret_val(id >= 0 && id < F_LAST, NULL);

  if (id < F_USER_FLAG_1) {
    return flag_names[id];
  }

  return user_flag_names[id - F_USER_FLAG_1];
}
