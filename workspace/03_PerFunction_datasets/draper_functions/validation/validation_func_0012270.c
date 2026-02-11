get_all_control_path( Block *first_block, int mt_num )
{
    IntSet path;
    List *head = NULL;

    construct_IntSet( path, mt_num + 1 );
    add1_IntSet( path, first_block->no );
    head = list_append( head, path );

    add_control_path( path, first_block, head );

    return head;
}
