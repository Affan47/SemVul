instance_get_leading_hierarchy(
                 funit_inst*  root,
   char*        leading_hierarchy,
        funit_inst** top_inst
) { PROFILE(INSTANCE_GET_LEADING_HIERARCHY);

  if( leading_hierarchy != NULL ) {
    strcat( leading_hierarchy, root->name );
  }

  *top_inst = root;

  if( root->funit == NULL ) {

    do {
      root = root->child_head;
      if( leading_hierarchy != NULL ) {
        strcat( leading_hierarchy, "." );
        strcat( leading_hierarchy, root->name );
      }
      *top_inst = root;
    } while( (root != NULL) && (root->funit == NULL) );

  }

  PROFILE_END;

}
