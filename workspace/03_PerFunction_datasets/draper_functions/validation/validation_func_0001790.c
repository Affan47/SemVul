print_string_list(FILE *out, mylist<mystring> const &list)
{
  const mylist<mystring>::size_type len = list.length();

  for (mylist<mystring>::size_type i = 0; i < len; i++)
    {
      fprintf(out, "%s\n", list[i].c_str());
    }
}
