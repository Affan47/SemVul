dig_del_line(struct Plus_head *plus, int line)
{
    int i, mv;
    P_LINE *Line;
    P_NODE *Node;


    G_debug(3, "dig_del_line() line =  %d", line);

    Line = plus->Line[line];
    dig_spidx_del_line(plus, line);


    Node = plus->Node[Line->N1];
    mv = 0;
    for (i = 0; i < Node->n_lines; i++) {
	if (mv) {
	    Node->lines[i - 1] = Node->lines[i];
	    Node->angles[i - 1] = Node->angles[i];
	}
	else {
	    if (abs(Node->lines[i]) == line)
		mv = 1;
	}
    }
    Node->n_lines--;
    if (Node->n_lines == 0) {
	G_debug(3, "    node %d has 0 lines -> delete", Line->N1);
	dig_spidx_del_node(plus, Line->N1);
	plus->Node[Line->N1] = NULL;
    }
    else {
	if (plus->do_uplist)
	    dig_node_add_updated(plus, Line->N1);
    }

    if (Line->type & GV_LINES) {
	Node = plus->Node[Line->N2];
	mv = 0;
	for (i = 0; i < Node->n_lines; i++) {
	    if (mv) {
		Node->lines[i - 1] = Node->lines[i];
		Node->angles[i - 1] = Node->angles[i];
	    }
	    else {
		if (abs(Node->lines[i]) == line)
		    mv = 1;
	    }
	}
	Node->n_lines--;
	if (Node->n_lines == 0) {
	    G_debug(3, "    node %d has 0 lines -> delete", Line->N2);
	    dig_spidx_del_node(plus, Line->N2);
	    plus->Node[Line->N2] = NULL;
	}
	else {
	    if (plus->do_uplist)
		dig_node_add_updated(plus, Line->N2);
	}
    }


    plus->Line[line] = NULL;

    return 0;
}
