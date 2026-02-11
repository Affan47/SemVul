getPointer(PointGroups* pointGroups, gint i)
{
	GList* l = NULL;;
	gint j = 0;
	if(!pointGroups) return NULL;
	for( l = pointGroups->listOfPointGroups; l != NULL;  l = l->next, j++)
		if(j==i) return (PointGroup*) l->data;
	return NULL;
}
