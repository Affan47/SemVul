processExtendedAttributes(imapFolder &f)
{
	if (f.getPath() != folderName)
		return;

	vector<mail::imapparsefmt *>::iterator b=xattributes.children.begin(),
		e=xattributes.children.end();

	while (b != e)
	{
		mail::imapparsefmt *node= *b++;

		if (node->children.size() < 2)
			continue;

		string name=(*node->children.begin())->value;

		mail::upper(name);

		if (name != "ACL")
			continue;

		mail::imapparsefmt *rights_list=node->children.begin()[1];

		vector<mail::imapparsefmt *>::iterator
			bb=rights_list->children.begin(),
			ee=rights_list->children.end();

		while (bb != ee)
		{
			mail::imapparsefmt *node= *bb++;

			if (node->children.size() < 2)
				continue;

			string identifier=node->children.begin()[0]->value;
			string r=node->children.begin()[1]->value;

			size_t p=r.find(ACL_DELETE_SPECIAL[0]);

			if (p != std::string::npos)
				r.replace(r.begin()+p, r.begin()+p+1,
					  ACL_DELETEMSGS ACL_DELETEFOLDER
					  ACL_EXPUNGE);

			sort(r.begin(), r.end());
			rights.push_back(make_pair(identifier, r));
		}
		break;
	}
}
