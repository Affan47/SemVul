insert_hash_edge(stl_file *stl, stl_hash_edge edge,
                 void (*match_neighbors)(stl_file *stl,
                     stl_hash_edge *edge_a, stl_hash_edge *edge_b)) {
  stl_hash_edge *link;
  stl_hash_edge *new_edge;
  stl_hash_edge *temp;
  int            chain_number;

  if (stl->error) return;

  chain_number = stl_get_hash_for_edge(stl->M, &edge);

  link = stl->heads[chain_number];

  if(link == stl->tail) {

    new_edge = (stl_hash_edge*)malloc(sizeof(stl_hash_edge));
    if(new_edge == NULL) perror("insert_hash_edge");
    stl->stats.malloced++;
    *new_edge = edge;
    new_edge->next = stl->tail;
    stl->heads[chain_number] = new_edge;
    return;
  } else  if(!stl_compare_function(&edge, link)) {

    match_neighbors(stl, &edge, link);

    stl->heads[chain_number] = link->next;
    free(link);
    stl->stats.freed++;
    return;
  } else {

    for(;;) {
      if(link->next == stl->tail) {

        new_edge = (stl_hash_edge*)malloc(sizeof(stl_hash_edge));
        if(new_edge == NULL) perror("insert_hash_edge");
        stl->stats.malloced++;
        *new_edge = edge;
        new_edge->next = stl->tail;
        link->next = new_edge;
        stl->stats.collisions++;
        return;
      } else  if(!stl_compare_function(&edge, link->next)) {

        match_neighbors(stl, &edge, link->next);


        temp = link->next;
        link->next = link->next->next;
        free(temp);
        stl->stats.freed++;
        return;
      } else {

        link = link->next;
        stl->stats.collisions++;
      }
    }
  }
}
