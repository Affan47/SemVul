parse_descr
(  const char* field
,  const char** descrp
,  const char** markp
,  int* mark_width
)
   {  const char* m = strstr(field, "\tM")
   ;  const char* n = m ? strstr(m+2, "\t") : NULL
   ;  const char* d = strstr(field, "\tD")

   ;  if (m && n)
         *mark_width =  n - m - 2
      ,  *markp = m + 2
   ;  else
         *markp = ""
      ,  *mark_width = 0

   ;  *descrp = d ? d + 2 : field
;  }
