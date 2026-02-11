loadPState(const char *studyUID,
                                    const char *seriesUID,
                                    const char *instanceUID,
                                    OFBool changeStatus)
{

    OFCondition status = lockDatabase();
    if (status != EC_Normal)
    {
        DCMPSTAT_LOGFILE("Load presentation state from database failed: could not lock index file");
        return status;
    }
    const char *filename = getFilename(studyUID, seriesUID, instanceUID);
    if (filename==NULL)
    {
        DCMPSTAT_LOGFILE("Load presentation state from database failed: UIDs not in index file");
        return EC_IllegalCall;
    }


    DcmFileFormat *pstate = NULL;
    DVPresentationState *newState = new DVPresentationState(OFstatic_cast(DiDisplayFunction **, displayFunction),
      minimumPrintBitmapWidth, minimumPrintBitmapHeight, maximumPrintBitmapWidth, maximumPrintBitmapHeight,
      maximumPreviewImageWidth, maximumPreviewImageHeight);
    if (newState==NULL)
    {
        DCMPSTAT_LOGFILE("Load presentation state from database failed: memory exhausted");
        return EC_MemoryExhausted;
    }

    if ((EC_Normal == (status = DVPSHelper::loadFileFormat(filename, pstate)))&&(pstate))
    {
        DcmDataset *dataset = pstate->getDataset();
        if (dataset) status = newState->read(*dataset); else status = EC_CorruptedData;
    }
    if (status == EC_Normal)
    {

        OFString ofstudyUID, ofseriesUID, ofsopclassUID, ofinstanceUID, offrames, aetitle, mediaID, mediaUID;
        status = newState->getImageReference(0, ofstudyUID, ofseriesUID, ofsopclassUID, ofinstanceUID,
          offrames, aetitle, mediaID, mediaUID);


        if (EC_Normal == status)
        {

            const char *imagefilename = NULL;
            imagefilename = getFilename(ofstudyUID.c_str(), ofseriesUID.c_str(), ofinstanceUID.c_str());


            if (imagefilename)
            {
                DcmFileFormat *fimage = NULL;
                if ((EC_Normal == (status = DVPSHelper::loadFileFormat(imagefilename, fimage)))&&(fimage))
                {
                    DcmDataset *dataset = pstate->getDataset();
                    if (dataset)
                    {
                        status = newState->attachImage(fimage, OFFalse);
                        if (EC_Normal == status)
                        {
                          exchangeImageAndPState(newState, fimage, pstate);
                          imageInDatabase = OFTrue;
                          if (changeStatus)
                          {

                              instanceReviewed(studyUID, seriesUID, instanceUID);
                              instanceReviewed(ofstudyUID.c_str(), ofseriesUID.c_str(), ofinstanceUID.c_str());
                          }
                        }
                    } else status = EC_CorruptedData;
                }
                if (status!=EC_Normal)
                {
                    delete fimage;
                    DCMPSTAT_LOGFILE("Load presentation state from database failed: could not read image data");
                }
            } else {
                status = EC_IllegalCall;
                DCMPSTAT_LOGFILE("Load presentation state from database failed: referenced image not in index file");
            }
        }
    } else
        DCMPSTAT_LOGFILE("Load presentation state from database failed: could not read fileformat");
    if (status!=EC_Normal)
    {
        delete pstate;
        delete newState;
    }
    return status;
}
