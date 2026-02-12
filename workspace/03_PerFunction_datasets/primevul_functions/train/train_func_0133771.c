void HtmlPage::dump(FILE *f, int pageNum, const std::vector<std::string>& backgroundImages)
{
  if (complexMode || singleHtml)
  {
    if (xml) dumpAsXML(f, pageNum);
    if (!xml) dumpComplex(f, pageNum, backgroundImages);
  }
  else
  {
    fprintf(f,"<a name=%d></a>",pageNum);

    for (auto ptr : *imgList) {
      auto img = static_cast<HtmlImage *>(ptr);


      const char *styles[4] = { "", " class=\"xflip\"", " class=\"yflip\"", " class=\"xyflip\"" };
      int style_index=0;
      if (img->xMin > img->xMax) style_index += 1;
      if (img->yMin > img->yMax) style_index += 2;

      fprintf(f,"<img%s src=\"%s\"/><br/>\n",styles[style_index],img->fName->c_str());
      delete img;
    }
    imgList->clear();

    GooString* str;
    for(HtmlString *tmp=yxStrings;tmp;tmp=tmp->yxNext){
      if (tmp->htext){
		str=new GooString(tmp->htext);
		fputs(str->c_str(),f);
		delete str;
		fputs("<br/>\n",f);
      }
    }
	fputs("<hr/>\n",f);
  }
}
