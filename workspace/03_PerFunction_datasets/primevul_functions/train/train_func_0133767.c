void HtmlOutputDev::endPage() {
  Links *linksList = docPage->getLinks();
  for (int i = 0; i < linksList->getNumLinks(); ++i)
  {
      doProcessLink(linksList->getLink(i));
  }
  delete linksList;

  pages->conv();
  pages->coalesce();
  pages->dump(page, pageNum, backgroundImages);


  maxPageWidth = pages->pageWidth;
  maxPageHeight = pages->pageHeight;


  if(!stout && !globalParams->getErrQuiet()) printf("Page-%d\n",(pageNum));
}
