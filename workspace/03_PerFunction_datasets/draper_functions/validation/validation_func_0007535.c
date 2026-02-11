client_drop_item(struct config_item *parent_item,
			     struct config_item *item)
{
	struct config_item_type *type;

	type = parent_item->ci_type;
	BUG_ON(!type);


	if (type->ct_group_ops && type->ct_group_ops->drop_item)
		type->ct_group_ops->drop_item(to_config_group(parent_item),
					      item);
	else
		config_item_put(item);
}
