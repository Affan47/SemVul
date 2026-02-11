next_row(EW * ewptr, EW * boundary,
	     SHORT * new, SHORT south
    )
{
    if (ewptr->next)
	if (ewptr->next == ewptr)
	    return (NULL);
	else
	    return (ewptr->next);
    else if (ewptr != boundary) {
	*new = 1;
	return (ewptr += south);
    }
    else
	return (NULL);
}
