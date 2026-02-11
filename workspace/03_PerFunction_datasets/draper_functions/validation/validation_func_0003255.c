Item_ScrollVisible (menuitem_s *item)
{
	menuframework_s *menu = item->generic.parent;

	if (menu->maxheight == 0)
		return true;
	if (CHASELINK(item->generic.y)-menu->yscroll < 0)
		return false;
	if (CHASELINK(item->generic.y)-menu->yscroll + Item_GetHeight(*item) > menu->maxheight)
		return false;
	return true;
}
