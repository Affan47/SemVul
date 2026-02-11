camAllocateHLSImage(CamImage *image, int width, int height)
{
    int i,psize;
    image->nSize=sizeof(CamImage);
    image->channelSeq[0]='H';
    image->channelSeq[1]='L';
    image->channelSeq[2]='S';
    image->channelSeq[3]=0;
    image->colorModel[0]='H';
    image->colorModel[1]='L';
    image->colorModel[2]='S';
    image->colorModel[3]=0;
    image->nChannels=3;
    image->alphaChannel=0;
    image->depth=16;
    image->dataOrder=CAM_DATA_ORDER_PLANE;
    image->origin=CAM_ORIGIN_TL;
    image->align=CAM_ALIGN_16BYTES;
    image->width=width & ~CAM_HEADER_ONLY;
    image->height=height;
    image->roi=NULL;
    image->mask=NULL;
    image->imageId=NULL;
    image->misc=NULL;
    image->imageData=NULL;
    for (i=0;i<4;i++) {
	image->borderMode[i]=CAM_BORDER_REPLICATE;
	image->borderConst[i]=0;
    }
    psize=8;
    image->widthStep=(((image->width+image->align-1)*psize/8/image->align)*image->align);
    image->imageSize=image->widthStep*3*image->height*psize/8;
    if (width & CAM_HEADER_ONLY) {
        image->imageDataOrigin = NULL;
        image->imageData = NULL;
    } else {
        image->imageDataOrigin=(unsigned char*)malloc(image->imageSize+image->align);
        image->imageData=(unsigned char*)(((CAM_INT64)(image->imageDataOrigin-1)/image->align)*image->align+image->align);
        if (image->imageData == NULL) {
            camSetErrorStr("Memory allocation failed");
            return 0;
        }
    }
    return 1;
}
