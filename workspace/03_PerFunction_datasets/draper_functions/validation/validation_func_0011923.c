add_DME_node(DME_NODE *l , DME_TREE_NODE ** Troot, int x, int y, DME_TREE_NODE *father){
int i, j ,n ;

	if ( l == NULL) return ;

	if ( Troot == NULL){
		Troot = (DME_TREE_NODE **) malloc ( sizeof (DME_TREE_NODE *));
		if ( Troot == NULL) {
			printf(" mallock Error 1 \n");
			exit(1);
		}
	}


	if ( (*Troot) == NULL ){
		(*Troot) = (DME_TREE_NODE *) malloc ( sizeof(DME_TREE_NODE)) ;
		if ( (*Troot) == NULL){
			printf(" mallock Error 2 \n");
			exit(1);
		}
		(*Troot) ->capacitance = l -> capacitance;
		(*Troot) ->altitude = Manhattan(l ->select_x, l ->select_y,x,y)  ;
		(*Troot) -> x = l->select_x ;
		(*Troot) -> y = l->select_y;
		(*Troot) ->detour = l ->detour ;
		(*Troot) -> delay = l->to_sink_delay;
		(*Troot) -> left_direction = l->left_direction ;
		(*Troot) -> right_direction = l ->right_direction;
		(*Troot) -> duplicate_first_buf = l ->duplicate_first_buf ;
		(*Troot) -> is_sink = 0 ;
		(*Troot) -> buf_num = l ->buf_num ;
		(*Troot) ->sink_index = l ->sink_index ;
		(*Troot) ->is_blk = l ->blockage_node ;

		(*Troot) ->first_buf_fraction = l -> first_buf_fraction ;
		(*Troot) ->factor = l ->factor;
		(*Troot) ->reduntant = l->reduntant ;
		(*Troot) ->left = (*Troot)->right =  0;
		(*Troot) ->ls = (*Troot) -> rs = NULL;
		(*Troot) ->fa = father ;
		(*Troot) ->is_fake = 0 ;
		(*Troot) ->wire_type = l->wire_type;
	}

	add_DME_node(l -> pleft, &((*Troot)->ls),l->select_x,l->select_y,(*Troot)) ;
	add_DME_node(l -> pright, &((*Troot)->rs),l->select_x,l->select_y,(*Troot)) ;

}
