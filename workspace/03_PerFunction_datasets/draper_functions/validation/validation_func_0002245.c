duplicateStringValue( const char *value,
                      unsigned int length = unknown )
{
   if ( length == unknown )
      length = (unsigned int)strlen(value);
   char *newString = static_cast<char *>( malloc( length + 1 ) );
   memcpy( newString, value, length );
   newString[length] = 0;
   return newString;
}
