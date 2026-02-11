set_drive_type(teledisk_prop_t *prop, int drive_type)
{
  switch (drive_type)
    {
    case 1:
      prop->drive_type = "360k";
      break;
    case 2:
      prop->drive_type = "1.2M";
      break;
    case 3:
      prop->drive_type = "720k";
      break;
    case 4:
      prop->drive_type = "1.44k";
      break;
    default:
      return 0;
    }

  return 1;
}
