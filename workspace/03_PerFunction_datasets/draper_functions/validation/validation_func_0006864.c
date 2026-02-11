GetServerParentId(midasResourceType::ResourceType type,
                                         int parentId)
{
  if(parentId)
    {
    std::stringstream fields;
    std::string server_parentId;

    std::string parentUuid = this->DatabaseProxy->GetUuid(type, parentId);


    fields << "midas.resource.get?uuid=" << parentUuid;
    mws::RestXMLParser parser;
    parser.AddTag("/rsp/id", server_parentId);
    mws::WebAPI::Instance()->GetRestAPI()->SetXMLParser(&parser);
    mws::WebAPI::Instance()->Execute(fields.str().c_str());
    parentId = atoi(server_parentId.c_str());
    }
  return parentId;
}
