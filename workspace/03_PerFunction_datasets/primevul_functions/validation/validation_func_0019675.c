newLineBufferTask (TaskGroup *group,
                   InputStreamMutex *streamData,
                   ScanLineInputFile::Data *ifd,
                   int number,
                   int scanLineMin,
                   int scanLineMax,
                   OptimizationMode optimizationMode)
{


     LineBuffer *lineBuffer = ifd->getLineBuffer (number);

     try
     {
         lineBuffer->wait ();

         if (lineBuffer->number != number)
         {
             lineBuffer->minY = ifd->minY + number * ifd->linesInBuffer;
             lineBuffer->maxY = lineBuffer->minY + ifd->linesInBuffer - 1;

             lineBuffer->number = number;
             lineBuffer->uncompressedData = 0;

             readPixelData (streamData, ifd, lineBuffer->minY,
                            lineBuffer->buffer,
                            lineBuffer->dataSize);
         }
     }
     catch (std::exception &e)
     {
         if (!lineBuffer->hasException)
         {
             lineBuffer->exception = e.what();
             lineBuffer->hasException = true;
         }
         lineBuffer->number = -1;
         lineBuffer->post();
         throw;
     }
     catch (...)
     {


         lineBuffer->exception = "unrecognized exception";
         lineBuffer->hasException = true;
         lineBuffer->number = -1;
         lineBuffer->post();
         throw;
     }

     scanLineMin = max (lineBuffer->minY, scanLineMin);
     scanLineMax = min (lineBuffer->maxY, scanLineMax);


     Task* retTask = 0;

#ifdef IMF_HAVE_SSE2
     if (optimizationMode._optimizable)
     {

         retTask = new LineBufferTaskIIF (group, ifd, lineBuffer,
                                          scanLineMin, scanLineMax,
                                          optimizationMode);

     }
     else
#endif
     {
         retTask = new LineBufferTask (group, ifd, lineBuffer,
                                       scanLineMin, scanLineMax,
                                       optimizationMode);
     }

     return retTask;

 }
