static_face_remove (gamgi_face *face)
{
gamgi_slist *slist;
gamgi_edge *edge;


slist = face->vertex;
while (slist != NULL)
  slist = gamgi_engine_slist_remove_start (slist);


slist = face->edge;
while (slist != NULL)
  {
  edge = (gamgi_edge *) slist->data;
  static_edge_remove (edge);
  slist = gamgi_engine_slist_remove_start (slist);
  }

free (face);
}
