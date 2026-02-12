static rfbBool MallocFrameBuffer(rfbClient* client) {
uint64_t allocSize;

  if(client->frameBuffer)
    free(client->frameBuffer);


  allocSize = (uint64_t)client->width * client->height * client->format.bitsPerPixel/8;

  if (allocSize >= SIZE_MAX) {
    rfbClientErr("CRITICAL: cannot allocate frameBuffer, requested size is too large\n");
    return FALSE;
  }

  client->frameBuffer=malloc( (size_t)allocSize );

  if (client->frameBuffer == NULL)
    rfbClientErr("CRITICAL: frameBuffer allocation failed, requested size too large or not enough memory?\n");

  return client->frameBuffer?TRUE:FALSE;
}
