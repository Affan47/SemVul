rfbClientListInit(rfbScreenInfoPtr rfbScreen)
{
    if(sizeof(rfbBool)!=1) {

        fprintf(stderr,"rfbBool's size is not 1 (%lu)!\n",(unsigned long)sizeof(rfbBool));

	exit(1);
    }
    rfbScreen->rfbClientHead = NULL;
}
