continue_seek2(int maxTries, char firstSeek)
{
	if( path_status != PATH_SEEKING )
		return path_status;


	cur_seek_path   = this;
	cur_dest_x	    = dest_x;
	cur_dest_y	  	 = dest_y;
	cur_node_matrix = node_matrix;
	cur_node_array  = node_array;

   cur_border_x1 	 = border_x1;
	cur_border_y1 	 = border_y1;
	cur_border_x2 	 = border_x2;
	cur_border_y2 	 = border_y2;


	int maxNode = (total_node_avail<maxTries) ? total_node_avail : maxTries;
	maxNode -= MAX_CHILD_NODE;
	Node *bestNodePtr;

	int i;
	for(i=0; i<maxNode; i++)
	{
		bestNodePtr = return_best_node();


		if( !bestNodePtr )
		{
			path_status = PATH_IMPOSSIBLE;
			break;
		}


		if( node_count >= maxNode )

		{
			path_status = PATH_NODE_USED_UP;
			break;
		}


		if( (bestNodePtr->node_x==dest_x && bestNodePtr->node_y==dest_y) ||
			 ( is_dest_blocked && abs(bestNodePtr->node_x-dest_x)<=1 && abs(bestNodePtr->node_y-dest_y)<=1 ) )
		{
			path_status 	 = PATH_FOUND;
			result_node_ptr = bestNodePtr;
			break;
		}


		if(bestNodePtr->generate_successors2(real_sour_x, real_sour_y))
		{
			path_status = PATH_REUSE_FOUND;
			result_node_ptr = reuse_result_node_ptr;
			break;
		}
	}

	err_when( cur_stack_pos!=0 );
	current_search_node_used = i+1;
	return path_status;
}
