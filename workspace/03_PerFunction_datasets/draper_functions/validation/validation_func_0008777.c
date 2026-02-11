get_armor_class(object *obj)
{
    if (obj) {
	return (obj->class + obj->d_enchant);
    }
    return (0);
}
