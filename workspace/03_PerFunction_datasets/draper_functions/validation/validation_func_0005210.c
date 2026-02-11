icalcomponent_new_impl (icalcomponent_kind kind)
{
    struct icalcomponent_impl* comp;

    if ( ( comp = (struct icalcomponent_impl*)
	   malloc(sizeof(struct icalcomponent_impl))) == 0) {
	icalerror_set_errno(ICAL_NEWFAILED_ERROR);
	return 0;
    }

    strcpy(comp->id,"comp");

    comp->kind = kind;
    comp->properties = pvl_newlist();
    comp->property_iterator = 0;
    comp->components = pvl_newlist();
    comp->component_iterator = 0;
    comp->x_name = 0;
    comp->parent = 0;

    return comp;
}
