void CommentParser::collectParameters(const std::string& fulltext, SourceFile *root_file)
{
	static auto EmptyStringLiteral(std::make_shared<Literal>(""));


	GroupList groupList = collectGroups(fulltext);
	int parseTill=getLineToStop(fulltext);

	for (auto &assignment : root_file->scope.assignments) {
		if (!assignment->getExpr()->isLiteral()) continue;


		int firstLine = assignment->location().firstLine();
		if(firstLine>=parseTill || (
			assignment->location().fileName() != "" &&
			assignment->location().fileName() != root_file->getFilename() &&
			assignment->location().fileName() != root_file->getFullpath()
			)) {
			continue;
		}

		AnnotationList *annotationList = new AnnotationList();


		std::string comment = getComment(fulltext, firstLine);

		shared_ptr<Expression> params = CommentParser::parser(comment.c_str());
		if (!params) {
			params = EmptyStringLiteral;
		}


		annotationList->push_back(Annotation("Parameter", params));


		std::string descr = getDescription(fulltext, firstLine - 1);
		if (descr != "") {

			shared_ptr<Expression> expr(new Literal(descr));
			annotationList->push_back(Annotation("Description", expr));
		}


		for (const auto &groupInfo :boost::adaptors::reverse(groupList)){
			if (groupInfo.lineNo < firstLine) {

				shared_ptr<Expression> expr(new Literal(groupInfo.commentString));
				annotationList->push_back(Annotation("Group", expr));
				break;
			}
		}
		assignment->addAnnotations(annotationList);
	}
}
