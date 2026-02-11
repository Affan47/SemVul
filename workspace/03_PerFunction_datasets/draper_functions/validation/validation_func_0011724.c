undo_stack_ascend(HexDocument *doc)
{
#ifdef ENABLE_DEBUG
	g_message("undo_stack_ascend");
#endif

	if(doc->undo_stack == NULL || doc->undo_top == doc->undo_stack)
		return;

	if(doc->undo_top == NULL)
		doc->undo_top = g_list_last(doc->undo_stack);
	else
		doc->undo_top = doc->undo_top->prev;
	doc->undo_depth++;
}
