drawBinding(Window window_)
{
  if (showBinding()==MSTrue&&bindingWidth()>=MSNotebookMinimumBindingWidth)
   {
     if (width()>=MSNotebookMinimumBindingWidth&&height()>=MSNotebookMinimumBindingWidth)
      {
	if (outputMode()==Print) drawSpiral();
	else
	 {
	   int w,h,xoff,yoff;
	   if (orientation()==Horizontal)
	    {
	      w=bindingWidth();
	      h=height()-highlightThickness()*2-shadowThickness()*2-borderHeight()*2-backpageMargin()-labelHeight();
              if (tabAlignment()==MSLeft)
               {
                 xoff=width()-highlightThickness()-shadowThickness()-borderWidth()-bindingWidth();
                 yoff=highlightThickness()+shadowThickness()+borderHeight()+labelHeight();
               }
              else
               {
                 xoff=highlightThickness()+shadowThickness()+borderWidth();
                 yoff=highlightThickness()+shadowThickness()+borderHeight()+labelHeight();
               }
	    }
	   else
	    {
	      w=width()-highlightThickness()*2-shadowThickness()*2-borderWidth()*2-backpageMargin();
	      h=bindingWidth();
              if (tabAlignment()==MSTop)
               {
                 xoff=highlightThickness()+shadowThickness()+borderWidth();
                 yoff=height()-highlightThickness()-shadowThickness()-borderHeight()-bindingWidth();
               }
              else
               {
                 xoff=highlightThickness()+shadowThickness()+borderWidth();
                 yoff=highlightThickness()+shadowThickness()+borderHeight()+labelHeight();
               }
	    }
	   XCopyArea(display(),bindingPixmap(),window_,notebookGC(),0,0,w,h,xoff,yoff);
	 }
      }
   }
}
