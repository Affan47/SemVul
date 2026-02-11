ShowPromiseTypesFor(char *s)

{ int i,j;
  struct SubTypeSyntax *st;

printf("<div id=\"promisetype\">");
printf("<h4>Promise types for %s bundles</h4>\n",s);
printf("<table class=border><tr><td>\n");

for (i = 0; i < CF3_MODULES; i++)
   {
   st = CF_ALL_SUBTYPES[i];

   for (j = 0; st[j].btype != NULL; j++)
      {
      if (strcmp(s,st[j].btype) == 0 || strcmp("*",st[j].btype) == 0)
         {
         printf("<h4>PROMISE TYPE %s</h4>\n",st[j].subtype);
         ShowBodyParts(st[j].bs);
         }
      }
   }

printf("</td></tr></table>\n");
printf("</div>\n\n");
}
