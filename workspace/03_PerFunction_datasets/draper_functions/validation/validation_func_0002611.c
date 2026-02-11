new_item(const char *name, const char *description)
{
  ITEM *item;

  T((T_CALLED("new_item(\"%s\", \"%s\")"),
     name ? name : "",
     description ? description : ""));

  if (!name || (*name == '\0') || !Is_Printable_String(name))
    {
      item = (ITEM *) 0;
      SET_ERROR(E_BAD_ARGUMENT);
    }
  else
    {
      item = (ITEM *) calloc(1, sizeof(ITEM));
      if (item)
	{
	  *item = _nc_Default_Item;

	  item->name.length = strlen(name);
	  item->name.str = name;

	  if (description && (*description != '\0') &&
	      Is_Printable_String(description))
	    {
	      item->description.length = strlen(description);
	      item->description.str = description;
	    }
	  else
	    {
	      item->description.length = 0;
	      item->description.str = (char *)0;
	    }
	}
      else
	SET_ERROR(E_SYSTEM_ERROR);
    }
  returnItem(item);
}
