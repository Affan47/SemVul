ms_obj_attr_get_gobject (MSObjAttrBag *attrs, MSObjAttrID id)
{
	MSObjAttr *attr;

	g_return_val_if_fail (attrs != NULL, NULL);
	g_return_val_if_fail (id & MS_OBJ_ATTR_IS_GOBJECT_MASK, NULL);

	attr = ms_obj_attr_bag_lookup (attrs, id);
	if (attr == NULL)
		return NULL;
	return attr->v.v_object;
}
