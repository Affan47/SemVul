ganv_group_add(GanvItem* parent, GanvItem* item)
{
	GanvGroup* group = GANV_GROUP(parent);
	g_object_ref_sink(G_OBJECT(item));

	if (!group->item_list) {
		group->item_list     = g_list_append(group->item_list, item);
		group->item_list_end = group->item_list;
	} else {
		group->item_list_end = g_list_append(group->item_list_end, item)->next;
	}

	if (group->item.object.flags & GANV_ITEM_REALIZED) {
		(*GANV_ITEM_GET_CLASS(item)->realize)(item);
	}

	if (group->item.object.flags & GANV_ITEM_MAPPED) {
		(*GANV_ITEM_GET_CLASS(item)->map)(item);
	}

	g_object_notify(G_OBJECT(item), "parent");
}
