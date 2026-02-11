construct_combined_esclist(ESCKEY_S *list1, ESCKEY_S *list2)
{
    ESCKEY_S *list;
    int       i, j=0, count;

    count = 2;
    for(i=0; list1 && list1[i].ch != -1; i++)
      count++;
    for(i=0; list2 && list2[i].ch != -1; i++)
      count++;

    list = (ESCKEY_S *) fs_get((count + 1) * sizeof(*list));
    memset(list, 0, (count + 1) * sizeof(*list));

    list[j].ch    = -2;
    list[j].rval  = 0;
    list[j].name  = NULL;
    list[j++].label = NULL;

    list[j].ch    = 'o';
    list[j].rval  = OTHER_RETURN_VAL;
    list[j].name  = "O";
    list[j].label = N_("OTHER CMDS");


    for(i=0; list1 && list1[i].ch != -1; i++){
	if(list1[i].rval == list[j].rval)
	  panic("1bad rval in d_r");
	if(F_OFF(F_USE_FK,ps_global) && list1[i].ch == list[j].ch)
	  panic("1bad ch in ccl");
    }

    for(i=0; list2 && list2[i].ch != -1; i++){
	if(list2[i].rval == list[j].rval)
	  panic("2bad rval in d_r");
	if(F_OFF(F_USE_FK,ps_global) && list2[i].ch == list[j].ch)
	  panic("2bad ch in ccl");
    }

    j++;


    for(i=0; list1 && list1[i].ch != -1; i++){
	if(i >= KEYS_PER_LIST && list1[i].label[0] != '\0')
	  panic("too many visible keys in ccl");

	list[j++] = list1[i];
    }


    for(i=0; list2 && list2[i].ch != -1; i++){
	list[j] = list2[i];
	list[j].label = "";
	list[j++].name  = "";
    }

    list[j].ch = -1;

    return(list);
}
