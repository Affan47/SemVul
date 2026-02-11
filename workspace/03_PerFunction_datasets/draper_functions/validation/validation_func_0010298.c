OnMouse(wxMouseEvent &event)
{
   if (event.LeftDown() && event.GetX() >= mWidth) {
      wxContextMenuEvent e;
      OnContext(e);
   }
   else if (event.LeftDown()) {
      SetFocus();

      int bestDist = 9999;
      unsigned int i;

      mFocusedDigit = 0;
      for(i=0; i<mDigits.GetCount(); i++) {
         int dist = abs(event.m_x - (mDigits[i].digitBox.x +
                                     mDigits[i].digitBox.width/2));
         if (dist < bestDist) {
            mFocusedDigit = i;
            bestDist = dist;
         }
      }

      Refresh(false);
   }
   else if (event.RightDown() && mMenuEnabled) {
      wxContextMenuEvent e;
      OnContext(e);
   }
   else if( event.m_wheelRotation != 0 ) {
      double steps = event.m_wheelRotation /
         (event.m_wheelDelta > 0 ? (double)event.m_wheelDelta : 120.0) +
         mScrollRemainder;
      mScrollRemainder = steps - floor(steps);
      steps = floor(steps);

      if (steps < 0.0) {
         Decrease((int)-steps);
         Updated();
      }
      else {
         Increase((int)steps);
         Updated();
      }
   }
}
