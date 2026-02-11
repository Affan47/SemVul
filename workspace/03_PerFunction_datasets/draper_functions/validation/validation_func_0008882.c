restore_dusts(list_t* orig, list_t* copy)
{
if(orig != NULL && copy != NULL)
	{
	if (((struct token_t*)orig->data)->tag & (TOK_OPT_TAG|TOK_OPT_STR))
		{
		((struct token_t *)orig->data)->dustlen =
			*((int *)copy->data);
		restore_dusts(orig->next,copy->next);
		}
	else
		restore_dusts(orig->next,copy);
	}

}
