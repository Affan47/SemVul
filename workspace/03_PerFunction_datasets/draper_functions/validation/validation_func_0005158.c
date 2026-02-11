draw_edges(cairo_t *c, vertex *v, int offx, int offy){
  if(v){
    edge_list *el=v->edges;
    while (el){
      edge *e=el->edge;

      if(e->A->grabbed==0 || e->B->grabbed==0 || v==e->A){
	if(e->A->grabbed)
	  cairo_move_to(c,e->A->x+offx,e->A->y+offy);
	else
	  cairo_move_to(c,e->A->x,e->A->y);

	if(e->B->grabbed)
	  cairo_line_to(c,e->B->x+offx,e->B->y+offy);
	else
	  cairo_line_to(c,e->B->x,e->B->y);
      }
      el=el->next;
    }
  }
}
