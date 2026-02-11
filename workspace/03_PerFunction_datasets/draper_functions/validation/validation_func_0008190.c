getCopy(Elements* elements)
{
	Elements nelements = newElements();
	GList* l = NULL;;
	for( l = elements->listOfElements; l != NULL;  l = l->next)
		nelements.addElement(&nelements, (Element*) l->data);
	return nelements;
}
