get_vertex(graph *g){
  vertex *ret;

  if(vertex_pool==0){
    int i;
    vertex_pool = calloc(CHUNK,sizeof(*vertex_pool));
    for(i=0;i<CHUNK-1;i++)
      vertex_pool[i].next=vertex_pool+i+1;
  }

  ret=vertex_pool;
  vertex_pool=ret->next;

  ret->x=0;
  ret->y=0;
  ret->active=0;
  ret->selected=0;
  ret->selected_volatile=0;
  ret->grabbed=0;
  ret->attached_to_grabbed=0;
  ret->fading=0;
  ret->edges=0;
  ret->num=g->vertex_num++;

  ret->next=g->verticies;
  g->verticies=ret;

  return ret;
}
