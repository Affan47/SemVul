readGeneric(istream *ifs, UINT32 objId)
  {
    char errorMsg[BUFF_SIZE];
    UINT16 tag;
    UINT16 size;
    UINT32 id;
    int depth = 1;

    while(ifs->good())
      {
        READ_INT16 (*ifs, tag);
        if(tag & kCDXTag_Object)
          {
            depth++;
            READ_INT32 (*ifs, id);

            snprintf(errorMsg, BUFF_SIZE, "Object ID (in generic %08X): %08X has type: %04X\n", objId, id, tag);
            obErrorLog.ThrowError(__FUNCTION__, errorMsg, obDebug);

            if ((tag == kCDXObj_BracketAttachment)
                || (tag == kCDXObj_CrossingBond)
                || (tag == kCDXObj_BracketedGroup)
                || (tag == kCDXObj_Text)
                || (tag == kCDXObj_Fragment))
              {
                readGeneric(ifs, id);
                depth--;
              }
            else {
              snprintf(errorMsg, BUFF_SIZE, "New object in generic, type %04X\n", tag);
              obErrorLog.ThrowError(__FUNCTION__, errorMsg, obDebug);
            }
          }
        else if(tag == 0)
          {
            depth--;
            snprintf(errorMsg, BUFF_SIZE, "End of Object in generic %08X\n", objId);
            obErrorLog.ThrowError(__FUNCTION__, errorMsg, obDebug);
          }
        else
          {
            READ_INT16 (*ifs, size);

            snprintf(errorMsg, BUFF_SIZE, "Generic Tag: %04X\tSize: %04X\n", tag, size);
            obErrorLog.ThrowError(__FUNCTION__, errorMsg, obDebug);


                ifs->seekg(size, ios_base::cur);


          }
        if(depth < 1)
          {
            return 0;
          }
      }
    return -1;
  }
