close_cb(Fl_Object *, void *)
{
    IMAGEPARM          *p;
    mi                  q;
    const char         *imTempPSFileName;


    dbgprintf("Close dialog callback\n");


    do  {
        p = (IMAGEPARM *)mainMenuBar->getSelectedItemArgument(IMAGE_LIST_ID);

	if (p == 0)
	    return;


	if ((q = psfilemap.find(p->itempath)) != psfilemap.end()) {


	    imTempPSFileName = (q->second).getfilename().c_str();
	    dbgprintf("Erasing the rendered PS file %s\n", imTempPSFileName);
	    unlink(imTempPSFileName);
	    psfilemap.erase(q);
	} else 	if (deleteAfter) {

	    if (strstr(p->itempath, "/tmp/") != 0) {
		dbgprintf("Physically deleting the image %s\n", p->itempath);
		unlink(p->itempath);
	    } else {
		dbgprintf("Not deleting %s after all\n", p->itempath);
	    }
	}


	IOBlackBox->closeHeader(p->itempath);

	mainMenuBar->removeFromItemList(p->itempath, IMAGE_LIST_ID);
        p = (IMAGEPARM *)mainMenuBar->getSelectedItemArgument(IMAGE_LIST_ID);
    } while ((p != 0) && (openimage(p->itempath) != 0));

    if (p == 0) {

        mainViewer->close();
        showSimpleBanner();
    }

    return;
}
