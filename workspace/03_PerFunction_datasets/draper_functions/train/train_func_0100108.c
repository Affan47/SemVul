html_generate_anchor_name (device_type dev_type, char *manufacturer_name)
{
  char *name = malloc (strlen (manufacturer_name) + 1 + 2);
  char *pointer = name;
  char type_char;

  if (!name)
    {
      DBG_ERR ("html_generate_anchor_name: couldn't malloc\n");
      return 0;
    }

  switch (dev_type)
    {
    case type_scanner:
      type_char = 'S';
      break;
    case type_stillcam:
      type_char = 'C';
      break;
    case type_vidcam:
      type_char = 'V';
      break;
    case type_meta:
      type_char = 'M';
      break;
    case type_api:
      type_char = 'A';
      break;
    default:
      type_char = 'Z';
      break;
    }

  snprintf (name, strlen (manufacturer_name) + 1 + 2, "%c-%s",
	    type_char, manufacturer_name);

  while (*pointer)
    {
      if (!isalnum (*pointer))
	*pointer = '-';
      else
	*pointer = toupper (*pointer);
      pointer++;
    }
  return name;
}
