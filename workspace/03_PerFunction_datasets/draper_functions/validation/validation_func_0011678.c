Draw( GRA_wxWidgets *graphicsOutput, wxDC &dc )
{
  double y0 = legend_->GetYHi() - 1.5*labelHeight_*(entryNumber_+1);


  double y = y0 + labelHeight_*0.5;
  double xStart = legend_->GetLineStart();
  double xEnd = legend_->GetLineEnd();
  double xLabel = legend_->GetXLabel();
  if( drawLineSegment_ )
  {
    int lineTypeSave = graphicsOutput->GetLineType();
    graphicsOutput->SetLineType( lineType_ );
    wxPen wxpen( dc.GetPen() );
    wxpen.SetWidth( lineWidth_ );
    wxpen.SetColour( ExGlobals::GetwxColor(lineColor_) );
    dc.SetPen( wxpen );
    graphicsOutput->StartLine( xStart, y );
    graphicsOutput->ContinueLine( xEnd, y, dc );
    graphicsOutput->SetLineType( lineTypeSave );
  }


  if( nSymbols_ > 0 )
  {
    if( nSymbols_ > 1 )
    {
      double xinc = (xEnd-xStart)/(nSymbols_-1.);
      for( int i=0; i<nSymbols_-1; ++i )
      {
        symbol_->SetLocation( xStart+i*xinc, y );
        symbol_->Draw( graphicsOutput, dc );
      }
      symbol_->SetLocation( xEnd, y );
      symbol_->Draw( graphicsOutput, dc );
    }
    else
    {
      symbol_->SetLocation( (xStart+xEnd)/2.0, y );
      symbol_->Draw( graphicsOutput, dc );
    }
  }


  label_->SetX( xLabel );
  label_->SetY( y0-0.25*labelHeight_ );
  label_->Draw( graphicsOutput, dc );
}
