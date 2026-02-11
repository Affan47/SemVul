set_extra_data(
  const any &extra_data, const std::string& name
  ,EPrePostDestruction destroy_when
  ,bool force_unique
  )
{
  if(extra_data_map_==NULL) {
    extra_data_map_ = new extra_data_map_t;
  }
  const std::string type_and_name( extra_data.typeName() + std::string(":") + name );
  extra_data_map_t::iterator itr = extra_data_map_->find(type_and_name);
#ifdef TEUCHOS_DEBUG
  TEUCHOS_TEST_FOR_EXCEPTION(
    (itr != extra_data_map_->end() && force_unique), std::invalid_argument
    ,"Error, the type:name pair \'" << type_and_name
    << "\' already exists and force_unique==true!" );
#endif
  if (itr != extra_data_map_->end()) {

    itr->second = extra_data_entry_t(extra_data,destroy_when);
  }
  else {

    (*extra_data_map_)[type_and_name] =
      extra_data_entry_t(extra_data,destroy_when);
  }
}
