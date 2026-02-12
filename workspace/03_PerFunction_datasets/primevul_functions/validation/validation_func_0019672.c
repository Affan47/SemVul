void LineBufferTaskIIF::getWritePointer
                            (int y,
                             unsigned short*& outWritePointerRight,
                             size_t& outPixelsToCopySSE,
                             size_t& outPixelsToCopyNormal,
                             int channelBank
                            ) const
{


      size_t nbSlicesInBank = _ifd->optimizationData.size();

      int sizeOfSingleValue = sizeof(TYPE);

      if(_ifd->optimizationData.size()>4)
      {

          nbSlicesInBank/=2;
      }


      size_t firstChannel = 0;
      if(channelBank==1)
      {
          firstChannel = _ifd->optimizationData.size()/2;
      }

       sliceOptimizationData& firstSlice = _ifd->optimizationData[firstChannel];

      if (modp (y, firstSlice.ySampling) != 0)
      {
          outPixelsToCopySSE    = 0;
          outPixelsToCopyNormal = 0;
          outWritePointerRight  = 0;
      }

      intptr_t base = reinterpret_cast<intptr_t>(firstSlice.base);

      intptr_t linePtr1  = (base +
      divp (y, firstSlice.ySampling) *
      firstSlice.yStride);

      int dMinX1 = divp (_ifd->minX, firstSlice.xSampling);
      int dMaxX1 = divp (_ifd->maxX, firstSlice.xSampling);


      outWritePointerRight =  reinterpret_cast<unsigned short*>(linePtr1 +
      dMinX1 * firstSlice.xStride );

      size_t bytesToCopy  = ((dMaxX1 * firstSlice.xStride ) - (dMinX1 * firstSlice.xStride )) + 2;
      size_t shortsToCopy = bytesToCopy / sizeOfSingleValue;
      size_t pixelsToCopy = (shortsToCopy / nbSlicesInBank ) + 1;


      outPixelsToCopySSE    = pixelsToCopy / 8;
      outPixelsToCopyNormal = pixelsToCopy % 8;

}
