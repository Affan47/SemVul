Update_P(arbre *tree, int t_edge_num)
{
  int i;
  double len;

  len = -1.0;
  For(i,tree->mod->n_catg)
    {
      tree->curr_catg = i;
      len = tree->t_edges[t_edge_num]->l*tree->mod->rr[i];
      if(len < BL_MIN) len = BL_MIN;
      tree->mod->update_eigen = 0;
      PMat(len,tree->mod,&tree->t_edges[t_edge_num]->Pij_rr[i]);

    }
}
