yydestruct (int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
#else
static void
yydestruct (yytype, yyvaluep, yylocationp)
    int yytype;
    YYSTYPE *yyvaluep;
    YYLTYPE *yylocationp;
#endif
{

  (void) yyvaluep;
  (void) yylocationp;

  switch (yytype)
    {

      default:
        break;
    }
}
