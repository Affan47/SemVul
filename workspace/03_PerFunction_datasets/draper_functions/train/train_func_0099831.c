CollectActions(XMLNode actions,std::list<std::string>& actions_list) {
  for(int n = 0;;++n) {
    XMLNode action = actions.Child(n);
    if(!action) break;
    actions_list.push_back(action.Name());
  };
}
