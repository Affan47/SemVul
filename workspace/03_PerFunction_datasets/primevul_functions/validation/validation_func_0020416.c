composite_line(int y,
               int start,
               CompositeDeepScanLine::Data * _Data,
               vector<const char *> & names,
               const vector<vector< vector<float *> > >  & pointers,
               const vector<unsigned int> & total_sizes,
               const vector<unsigned int> & num_sources
              )
{
    vector<float> output_pixel(names.size());
    vector<const float *> inputs(names.size());
    DeepCompositing d;
    DeepCompositing * comp= _Data->_comp ? _Data->_comp : &d;

    int pixel = (y-start)*(_Data->_dataWindow.max.x+1-_Data->_dataWindow.min.x);

     for(int x=_Data->_dataWindow.min.x;x<=_Data->_dataWindow.max.x;x++)
     {


          if(_Data->_zback)
          {

              for(size_t channel=0;channel<names.size();channel++)
              {
                 inputs[channel]=pointers[0][channel][pixel];
              }

          }else{


              inputs[0]=pointers[0][0][pixel];
              inputs[1]=pointers[0][0][pixel];
              for(size_t channel=2;channel<names.size();channel++)
              {
                  inputs[channel]=pointers[0][channel][pixel];
              }

          }
          comp->composite_pixel(&output_pixel[0],
                                &inputs[0],
                                &names[0],
                                names.size(),
                                total_sizes[pixel],
                                num_sources[pixel]
                               );


           size_t channel_number=0;


           for(FrameBuffer::Iterator it = _Data->_outputFrameBuffer.begin();it !=_Data->_outputFrameBuffer.end();it++)
           {

               float value = output_pixel[ _Data->_bufferMap[channel_number] ];


               if(it.slice().type==OPENEXR_IMF_INTERNAL_NAMESPACE::FLOAT)
               {
                   * (float *)(it.slice().base + y*it.slice().yStride + x*it.slice().xStride) = value;
               }
               else if(it.slice().type==HALF)
               {
                   * (half *)(it.slice().base + y*it.slice().yStride + x*it.slice().xStride) = half(value);
               }

               channel_number++;

           }

           pixel++;

       }
}
