artFileIsValid (Article article)
{
  bool rval = false ;


  if (article->articleOk)
    {
#ifdef	XXX_RAWHACK
      int	fd = RAWartopen(article->fname, article->msgid);

      if (fd < 0) {
	rval = false;
      } else {

	rval = true;
      }
#else
      if (article->contents != NULL)
        rval = true ;
      else if (fileExistsP (article->fname))
        rval = true ;
#endif

#ifdef	XXX_RAWHACK
    notrval:
#endif
      if (!rval)
        {
          article->articleOk = false ;
          missingArticleCount++ ;
          if (logMissingArticles && !article->loggedMissing)
            {
              syslog (LOG_NOTICE,NO_ARTICLE,article->msgid,article->fname) ;
              article->loggedMissing = true ;
            }
        }
    }


  return rval ;
}
