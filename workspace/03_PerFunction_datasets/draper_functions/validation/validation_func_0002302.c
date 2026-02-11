ValuesMatch( const WrappedType & W )
{
   if( W.eWrappedType != eWrappedType )
      return false;
   switch( eWrappedType )
   {
   case eWrappedString:
      return *W.mpStr == *mpStr;
      break;
   case eWrappedInt:
      return *W.mpInt == *mpInt;
      break;
   case eWrappedDouble:
      return *W.mpDouble == *mpDouble;
      break;
   case eWrappedBool:
      return *W.mpBool == *mpBool;
      break;
   case eWrappedEnum:
      wxASSERT( false );
      break;
   default:
      wxASSERT( false );
      break;
   }
   return false;
}
