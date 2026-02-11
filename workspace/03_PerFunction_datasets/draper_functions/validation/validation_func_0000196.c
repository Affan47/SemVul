save_path_1(int src,int dest,int flag, Node *node){
        int i,j,cost=0;

        i = dest;

        while(i!=src)
        {
                j = node[i].pred;
                node[j].next_hop = i;
                cost+=node[j].edge_cost[i];
                i = j;
        }

        node[i].cost = cost;


        Path *temp,*p;
        int next_hop = node[src].next_hop;
        temp = malloc(sizeof(Path));
        temp->nodes[0] = src;
        temp->nodes[1] = next_hop;

        path[flag] = temp;
        if(flag == 0){

                node[next_hop].edge_cost[src] = INF;


        }
        else{

                node[src].edge_cost[next_hop] = node[next_hop].edge_cost[src];


        }
	temp->cost = node[src].edge_cost[next_hop];

        i = next_hop;
        p = temp;
        while(i!=dest){
                next_hop = node[i].next_hop;
                temp = malloc(sizeof(Path));
                temp->nodes[0] = i;
                temp->nodes[1] = next_hop;
                temp->next = NULL;
                if(flag == 0){
                        node[next_hop].edge_cost[i] = INF;


                }
                else{
                        node[i].edge_cost[next_hop] = node[next_hop].edge_cost[i];


                }
		temp->cost = node[i].edge_cost[next_hop];

                p->next = temp;
                p = p->next;

                i = next_hop;
        }

}
