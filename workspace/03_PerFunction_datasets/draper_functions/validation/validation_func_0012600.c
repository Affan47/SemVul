s_netattrib_create_pins(TOPLEVEL * pr_current, OBJECT * o_current,
			NETLIST * netlist, char *value,
			char *hierarchy_tag)
{
    NETLIST *netlist_tail = NULL;
    CPINLIST *cpinlist_tail = NULL;
    CPINLIST *new_cpin = NULL;
    CPINLIST *old_cpin = NULL;
    char *connected_to = NULL;
    char *net_name = NULL;
    char *start_of_pinlist = NULL;
    char *char_ptr = NULL;
    char *current_pin = NULL;


    char_ptr = strchr(value, ':');

    if (char_ptr == NULL) {
	return;
    }


    net_name = s_netattrib_extract_netname(value);


    start_of_pinlist = char_ptr + 1;
    current_pin = strtok(start_of_pinlist, DELIMITERS);
    while (current_pin) {

	netlist_tail = s_netlist_return_tail(netlist);
	cpinlist_tail = s_cpinlist_return_tail(netlist_tail->cpins);

	if (netlist->component_uref) {

	    old_cpin =
		s_cpinlist_search_pin(netlist_tail->cpins, current_pin);

	    if (old_cpin) {

		g_assert (old_cpin->nets != NULL);

		if (old_cpin->nets->net_name) {
		    fprintf(stderr,
			    "Found a cpinlist head with a netname! [%s]\n",
			    old_cpin->nets->net_name);
		    g_free(old_cpin->nets->net_name);
		}


		old_cpin->nets->net_name =
		    s_hierarchy_create_netattrib(pr_current, net_name,
						 hierarchy_tag);
		old_cpin->nets->net_name_has_priority = TRUE;
		connected_to = g_strdup_printf("%s %s",
                                   netlist->component_uref,
                                   current_pin);
		old_cpin->nets->connected_to = g_strdup(connected_to);
		old_cpin->nets->nid = o_current->sid;
		g_free(connected_to);
	    } else {


		new_cpin = s_cpinlist_add(cpinlist_tail);

		new_cpin->pin_number = g_strdup (current_pin);
		new_cpin->net_name = NULL;

		new_cpin->plid = o_current->sid;

		new_cpin->nets = s_net_add(NULL);
		new_cpin->nets->net_name_has_priority = TRUE;
		new_cpin->nets->net_name =
		    s_hierarchy_create_netattrib(pr_current, net_name,
						 hierarchy_tag);

		connected_to = g_strdup_printf("%s %s",
                                   netlist->component_uref,
                                   current_pin);
		new_cpin->nets->connected_to = g_strdup(connected_to);
		new_cpin->nets->nid = o_current->sid;

#if DEBUG
		printf("Finished creating: %s\n", connected_to);
		printf("netname: %s %s\n", new_cpin->nets->net_name,
		       hierarchy_tag);
#endif

		g_free(connected_to);
	    }

	} else {

	}
	current_pin = strtok(NULL, DELIMITERS);
    }

    g_free(net_name);
}
