CommentAttribute(List *qualname, char *comment)
{
	int			nnames;
	List	   *relname;
	char	   *attrname;
	RangeVar   *rel;
	Relation	relation;
	AttrNumber	attnum;


	nnames = list_length(qualname);
	if (nnames < 2)
		elog(ERROR, "must specify relation and attribute");
	relname = list_truncate(list_copy(qualname), nnames - 1);
	attrname = strVal(lfirst(list_tail(qualname)));


	rel = makeRangeVarFromNameList(relname);
	relation = relation_openrv(rel, AccessShareLock);


	if (!pg_class_ownercheck(RelationGetRelid(relation), GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, ACL_KIND_CLASS,
					   RelationGetRelationName(relation));


	if (relation->rd_rel->relkind != RELKIND_RELATION &&
		relation->rd_rel->relkind != RELKIND_VIEW &&
		relation->rd_rel->relkind != RELKIND_COMPOSITE_TYPE)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("\"%s\" is not a table, view, or composite type",
						RelationGetRelationName(relation))));


	attnum = get_attnum(RelationGetRelid(relation), attrname);
	if (attnum == InvalidAttrNumber)
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_COLUMN),
				 errmsg("column \"%s\" of relation \"%s\" does not exist",
						attrname, RelationGetRelationName(relation))));


	CreateComments(RelationGetRelid(relation), RelationRelationId,
				   (int32) attnum, comment);


	relation_close(relation, NoLock);
}
