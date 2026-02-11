addr_book_change_list(char **error)
{
    char   *p;
    jmp_buf save_jmp_buf;
    int    *save_nesting_level;

    dprint((3, "--- addr_book_change_list ---\n"));

    save_nesting_level = cpyint(ab_nesting_level);
    memcpy(save_jmp_buf, addrbook_changed_unexpectedly, sizeof(jmp_buf));
    if(setjmp(addrbook_changed_unexpectedly)){
	q_status_message(SM_ORDER, 5, 10, _("Resetting address book..."));
	dprint((1, "RESETTING address book... addr_book_change_list!\n"));
	addrbook_reset();
	ab_nesting_level = *save_nesting_level;
    }

    ab_nesting_level++;


    p = addr_book(SelectNicksCom, _("ADDRESS BOOK (Update): SELECT ADDRESSES"),
		  error);

    if(ab_nesting_level <= 1)
      end_adrbks();
    else
      ab_nesting_level--;

    memcpy(addrbook_changed_unexpectedly, save_jmp_buf, sizeof(jmp_buf));
    if(save_nesting_level)
      fs_give((void **)&save_nesting_level);

    return(p);
}
