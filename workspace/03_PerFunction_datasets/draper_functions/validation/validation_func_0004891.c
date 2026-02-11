eb_initialize_booklist(EB_BookList *booklist)
{
    LOG(("in: eb_initialize_booklist()"));

    booklist->entry_count = 0;
    booklist->max_entry_count = 0;
    booklist->entries = NULL;
    eb_initialize_lock(&booklist->lock);

    LOG(("out: eb_initialize_booklist()"));
}
