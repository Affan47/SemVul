compare_vertex_attr(va,vb)
vertex_id va,vb;
{ int i,j;
  conmap_t * con1,*con2;
  int same = 0;


  con1 = get_v_constraint_map(va);
  con2 = get_v_constraint_map(vb);

  for ( i = 1 ; i <= (int)con2[0] ; i++ )
  { for ( j = 1 ; j <= (int)con1[0] ; j++ )
      if ( (con1[j]&CONMASK) == (con2[i]&CONMASK) )
      { same++;
        break;
      }
  }

  if ( (same==(int)con1[0]) && (same==(int)con2[0]) )
    return A_EQ_B;
  if ( (same==(int)con1[0]) && (same < (int)con2[0]) )
    return A_SUB_B;
  if ( (same < (int)con1[0]) && (same==(int)con2[0]) )
    return A_SUPER_B;
  return INCOMPARABLE;
}
