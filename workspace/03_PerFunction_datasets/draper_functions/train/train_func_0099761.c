dc_setNodeBufferSize(struct vsp_node *node, size_t newSize)
{

	char *tmpBuffer;

	if(node == NULL) return;

	if( node->ahead == NULL ) {

		node->ahead = (ioBuffer *)malloc( sizeof(ioBuffer) );

		if(node->ahead == NULL) {
			dc_debug(DC_ERROR, "Failed allocate memory for read-ahead, so skipping");
		}else{
			node->ahead->buffer = NULL;
			node->ahead->cur  = 0;
			node->ahead->base = 0;
			node->ahead->used = 0;
			node->ahead->size = 0;
			node->ahead->isDirty = 0;
		}

	}


	if(node->ahead != NULL) {

		if( node->ahead->buffer == NULL ) {


			dc_debug(DC_INFO, "[%d] Allocating %d bytes as Read-ahead buffer.", node->dataFd, newSize);
			node->ahead->buffer = (char *)malloc(newSize);

			if( node->ahead->buffer == NULL ) {
				dc_debug(DC_ERROR, "[%d] Failed to allocate %ld bytes for Read-ahead buffer.", node->dataFd, newSize);
			}else{
				node->ahead->size = newSize;
				node->ahead->used = 0;
				node->ahead->cur = 0;
				node->ahead->isDirty = 0;
			}
		}else{


			if( newSize == node->ahead->size) {

				return;
			}

			dc_debug(DC_INFO, "[%d] Changing Read-ahead buffer size from %ld to %ld.",
 				node->dataFd, node->ahead->size, newSize);

			tmpBuffer = (char *)realloc(node->ahead->buffer, newSize);
			if( tmpBuffer == NULL ) {
				dc_debug(DC_INFO, "[%d] Failed to change read-ahead buffer size.", node->queueID);
				return;
			}


			node->ahead->buffer = tmpBuffer;

			if( newSize < node->ahead->size ) {


				if(node->ahead->used > newSize) {

					node->seek = node->ahead->base + newSize;
					node->whence = SEEK_SET;

					dc_set_pos(node, DCFT_POSITION, -1);

					node->ahead->used = newSize;

					if(node->ahead->cur > newSize) {
						node->ahead->cur = newSize;
					}
				}
			}

			node->ahead->size = newSize;
		}

    }

   return;

}
