ffbfeof(fitsfile *fptr,
           int *status)
{


    int ii;

    for (ii = 0; ii < NIOBUF; ii++)
    {
        if ( (LONGLONG) (fptr->Fptr)->bufrecnum[ii] * IOBUFLEN >= fptr->Fptr->filesize)
        {
            (fptr->Fptr)->bufrecnum[ii] = -1;
        }
    }

    return(*status);
}
