scrollDown(int count_,int selectedRow_,MSBoolean drawNewRow_)
{
  if (firstRow()>0&&count_>0)
   {
     int oldFirstRow=firstRow();
     if (firstRow()-count_<0) count_=firstRow();
     if (count_>=rows()-1)
      {
        _firstRow-=count_;
        _selectedRow=selectedRow_;
	redrawImmediately();
      }
     else
      {
        int delta=count_*rowHeight();
        int offset=panner()->highlightThickness()+panner()->shadowThickness();
        int src_x=offset;
        int dest_x=src_x;
        int src_y=offset+headingsHeight();
        int dest_y=src_y+delta;
        int w=panner()->width()-2*offset;
        int h=(rows()-count_)*rowHeight();

	int oldRow=selectedRow();
	_selectedRow=selectedRow_;
	if (oldRow!=selectedRow()) undrawSelectedRow(oldRow);
        _firstRow-=count_;
        XCopyArea(display(),panner()->window(),panner()->window(),
		  panner()->backgroundShadowGC(),
		  src_x,src_y,w,h,dest_x,dest_y);
        int rs=firstRow();
        int re=firstRow()+count_;
        postVerticalScrollDraw(rs,re,drawNewRow_);
  	updateScrollBars();
      }
     if (oldFirstRow!=firstRow()) firstRowChangeNotify();
   }
}
