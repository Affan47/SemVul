spell_print_tree(wordnode_T *root)
{
    if (root != NULL)
    {


	spell_clear_flags(root);


	spell_print_node(root, 0);
    }
}
