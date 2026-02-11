Double(URL *aUrl,const char *value,
				double default_value ) {
double retValue=default_value;
String tmpStr=Find(aUrl,value);
 if (tmpStr[0]!=0) {
   retValue=atof(tmpStr.get());
 }
return retValue;
}
