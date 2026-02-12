parse_fontdata(
    XOC		 oc,
    FontSet      font_set,
    FontData	 font_data,
    int		 font_data_count,
    char	 **name_list,
    int		 name_list_count,
    ClassType	 class,
    FontDataRec *font_data_return)
{

    char	**cur_name_list = name_list;
    char	*font_name      = (char *) NULL;
    char	*pattern        = (char *) NULL;
    int		found_num       = 0, ret = 0;
    int		count           = name_list_count;

    if(name_list == NULL || count <= 0) {
	return False;
    }

    if(font_data == NULL || font_data_count <= 0) {
	return False;
    }


    for ( ; font_data_count-- > 0; font_data++) {
	Bool	is_found = False;
	font_name = (char *) NULL;
	count = name_list_count;
	cur_name_list = name_list;


	while (count-- > 0) {
            pattern = *cur_name_list++;
	    if (pattern == NULL || *pattern == '\0')
		continue;
#ifdef FONTDEBUG
		fprintf(stderr,"Font pattern: %s %s\n",
		pattern,font_data->name);
#endif


	    if (strchr(pattern, '*') == NULL &&
		(font_name = get_font_name(oc, pattern))) {


		ret = parse_all_name(oc, font_data, font_name);
		Xfree(font_name);

                if (ret == -1)    return -1;
	        if (ret == False) continue;


		if (font_data_return) {
		    font_data_return->xlfd_name = strdup(font_data->xlfd_name);
		    if (!font_data_return->xlfd_name) return -1;

		    font_data_return->side      = font_data->side;
		}
#ifdef FONTDEBUG
		fprintf(stderr,"XLFD name: %s\n",font_data->xlfd_name);
#endif

		return True;
	    }


	    ret = parse_omit_name(oc, font_data, pattern);

            if (ret == -1)    return -1;
	    if (ret == False) continue;


	    if (font_data_return && font_data_return->xlfd_name == NULL) {

#ifdef FONTDEBUG
		fprintf(stderr,"XLFD name: %s\n",font_data->xlfd_name);
#endif
		font_data_return->xlfd_name = strdup(font_data->xlfd_name);
                if (!font_data_return->xlfd_name) return -1;

	        font_data_return->side      = font_data->side;
	    }

	    found_num++;
	    is_found = True;

	    break;
	}

	switch(class) {
	  case C_PRIMARY:
	       if(is_found == False) {


		  ret = parse_fontdata(oc, font_set, font_set->substitute,
				       font_set->substitute_num, name_list,
				       name_list_count, C_SUBSTITUTE,
				       font_data_return);
                  if (ret == -1)    return -1;
		  if (ret == False) continue;

		  found_num++;
		  is_found = True;
               }
#ifdef TESTVERSION
	       else
		   return True;
#endif
	       break;

	  case C_SUBSTITUTE:
	  case C_VMAP:
	       if(is_found == True)
		  return True;
	       break;

	  case C_VROTATE:
	       if(is_found == True) {
		  char	*rotate_name;

		  if((rotate_name = get_rotate_fontname(font_data->xlfd_name))
		     != NULL) {
		      Xfree(font_data->xlfd_name);
		      font_data->xlfd_name = rotate_name;

		      return True;
		  }
		  Xfree(font_data->xlfd_name);
		  font_data->xlfd_name = NULL;
		  return False;
	       }
	       break;
	}
    }

    if(class == C_PRIMARY && found_num >= 1)
	return True;

    return False;
}
