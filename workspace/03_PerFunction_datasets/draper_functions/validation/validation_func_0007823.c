copy_tree(bc_node *root_to, bc_node *root_from)
{
   int i, childNum;

   if (!root_to || !root_from){
      printf("copy_tree(): Empty root node(s)!\n");
      return(FUNCTION_TERMINATED_ABNORMALLY);
   }

   if (root_from){
      copy_node(root_to, root_from);
      childNum = root_to->bobj.child_num;
      if (childNum) {
	 root_to->children = (bc_node **) calloc(sizeof(bc_node*), childNum);
	 for (i = 0; i < childNum; i++){
	    root_to->children[i] = (bc_node *) calloc(1, sizeof(bc_node));
	    root_to->children[i]->parent = root_to;
	    copy_tree(root_to->children[i], root_from->children[i]);
	 }
      }
   }
   return(FUNCTION_TERMINATED_NORMALLY);
}
