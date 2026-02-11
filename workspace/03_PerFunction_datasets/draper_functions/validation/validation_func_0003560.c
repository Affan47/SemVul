us_socket_collection_group_fill_sets( us_socket_collection_group_t *self,
                                          fd_set *readable,
                                          fd_set *writable,
                                          int largest_fd )
{
    int i;
    for ( i = 0; i < self->num_collections; ++i )
    {
        us_socket_collection_t *c = self->collection[i];
        largest_fd = us_socket_collection_fill_read_set( c, readable, largest_fd );
        largest_fd = us_socket_collection_fill_write_set( c, writable, largest_fd );
    }
    return largest_fd;
}
