parse_display(const char* str, int* val)
{
  gt_display_modes_e i;

  if ((str == NULL) || (*str == '\0')) {
    return 0;
  }

  for (i = GT_DISPLAY_MODE_MIN; i <= GT_DISPLAY_MODE_MAX; i++) {
    if (case_ignore_strcmp(str, gt_display_mode_names[i]) == 0) {
      *val = i;
      return 1;
    }
  }
  warning(MYNAME ": Unknown display mode \"%s\" at line %d.\n", str, current_line);
  return 0;
}
