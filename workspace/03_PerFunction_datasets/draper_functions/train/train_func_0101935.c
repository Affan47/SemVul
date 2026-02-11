check()
{
  for (ListType::iterator i = __listPlus.begin();
       i != __listPlus.end(); ++i) {
    (*(*i)).check();
  }

  for (ListType::iterator i = __listMinus.begin();
       i != __listMinus.end(); ++i) {
    (*(*i)).check();
  }
}
