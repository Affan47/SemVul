bufferAtEnd()
{
  if ( readBufferPos >= readBufferLen ||
       readBuffer[readBufferPos] == '\0'
     ) {
    return true;

  } else {
    return false;
  }
}
