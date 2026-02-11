glp_create_graph(int v_size, int a_size)
{     glp_graph *G;
      if (!(0 <= v_size && v_size <= 256))
         xerror("glp_create_graph: v_size = %d; invalid size of vertex "
            "data\n", v_size);
      if (!(0 <= a_size && a_size <= 256))
         xerror("glp_create_graph: a_size = %d; invalid size of arc dat"
            "a\n", a_size);
      G = xmalloc(sizeof(glp_graph));
      create_graph(G, v_size, a_size);
      return G;
}
