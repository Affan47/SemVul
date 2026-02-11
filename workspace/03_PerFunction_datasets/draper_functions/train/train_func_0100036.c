RetrievedDocument(Document & doc, const String & url, DocumentRef * ref)
{
	n_links = 0;
	current_ref = ref;
	current_title = 0;
	word_context.Anchor(0);
	current_time = 0;
	current_head = 0;
	current_meta_dsc = 0;


	Parsable *parsable = doc.getParsable();
	if (parsable)
		parsable->parse(*this, *base);
	else
	{
		ref->DocState(Reference_noindex);
		return;
	}


	if (no_store_phrases)
	{
	    DictionaryCursor cursor;
	    char *key;
	    HtWordReference wordRef;
	    for (words_to_add.Start_Get (cursor);
		    (key = words_to_add.Get_Next(cursor)); )
	    {
		word_entry *entry = (word_entry*) (words_to_add [key]);

		wordRef.Location(entry->location);
		wordRef.Flags(entry->flags);
		wordRef.Word(key);
		words.Replace(WordReference::Merge(wordRef, entry->context));

		delete entry;
	    }
	    words_to_add.Release ();
	}


	ref->DocHead((char *) current_head);
	ref->DocMetaDsc((char *) current_meta_dsc);
	if (current_time == 0)
		ref->DocTime(doc.ModTime());
	else
		ref->DocTime(current_time);
	ref->DocTitle((char *) current_title);
	ref->DocSize(doc.Length());
	ref->DocAccessed(time(0));
	ref->DocLinks(n_links);
}
