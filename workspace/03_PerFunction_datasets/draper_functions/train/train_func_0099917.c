getDescription() const
{
   ASCString s = "Put Mine";
   if ( getUnit() ) {
      s += " by " + getUnit()->getName();
   }
   s += " on " + target.toString();
   return s;
}
