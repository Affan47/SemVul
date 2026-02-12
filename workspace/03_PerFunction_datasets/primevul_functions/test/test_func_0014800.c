stl_remove_unconnected_facets(stl_file *stl) {


  int i;

  if (stl->error) return;


  for(i = 0; i < stl->stats.number_of_facets; i++) {
    if(   !memcmp(&stl->facet_start[i].vertex[0],
                  &stl->facet_start[i].vertex[1], sizeof(stl_vertex))
          || !memcmp(&stl->facet_start[i].vertex[1],
                     &stl->facet_start[i].vertex[2], sizeof(stl_vertex))
          || !memcmp(&stl->facet_start[i].vertex[0],
                     &stl->facet_start[i].vertex[2], sizeof(stl_vertex))) {
      stl_remove_degenerate(stl, i);
      i--;
    }
  }

  if(stl->stats.connected_facets_1_edge < stl->stats.number_of_facets) {

    for(i = 0; i < stl->stats.number_of_facets; i++) {
      if(   (stl->neighbors_start[i].neighbor[0] == -1)
            && (stl->neighbors_start[i].neighbor[1] == -1)
            && (stl->neighbors_start[i].neighbor[2] == -1)) {

        stl_remove_facet(stl, i);
        i--;
      }
    }
  }
}
