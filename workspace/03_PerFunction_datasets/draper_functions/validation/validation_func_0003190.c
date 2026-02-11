RelationClearRelation(Relation relation, bool rebuild)
{


	Assert(rebuild ?
		   !RelationHasReferenceCountZero(relation) :
		   RelationHasReferenceCountZero(relation));


	RelationCloseSmgr(relation);


	if (relation->rd_isnailed)
	{
		relation->rd_targblock = InvalidBlockNumber;
		relation->rd_fsm_nblocks = InvalidBlockNumber;
		relation->rd_vm_nblocks = InvalidBlockNumber;
		if (relation->rd_rel->relkind == RELKIND_INDEX)
		{
			relation->rd_isvalid = false;
			if (relation->rd_refcnt > 1)
				RelationReloadIndexInfo(relation);
		}
		return;
	}


	if (relation->rd_rel->relkind == RELKIND_INDEX &&
		relation->rd_refcnt > 0 &&
		relation->rd_indexcxt != NULL)
	{
		relation->rd_isvalid = false;
		RelationReloadIndexInfo(relation);
		return;
	}


	relation->rd_isvalid = false;


	CatalogCacheFlushRelation(RelationGetRelid(relation));


	if (!rebuild)
	{

		RelationCacheDelete(relation);


		RelationDestroyRelation(relation);
	}
	else
	{


		Relation	newrel;
		Oid			save_relid = RelationGetRelid(relation);
		bool		keep_tupdesc;
		bool		keep_rules;


		newrel = RelationBuildDesc(save_relid, false);
		if (newrel == NULL)
		{

			RelationCacheDelete(relation);
			RelationDestroyRelation(relation);
			elog(ERROR, "relation %u deleted while still in use", save_relid);
		}

		keep_tupdesc = equalTupleDescs(relation->rd_att, newrel->rd_att);
		keep_rules = equalRuleLocks(relation->rd_rules, newrel->rd_rules);


#define SWAPFIELD(fldtype, fldname) \
		do { \
			fldtype _tmp = newrel->fldname; \
			newrel->fldname = relation->fldname; \
			relation->fldname = _tmp; \
		} while (0)


		{
			RelationData tmpstruct;

			memcpy(&tmpstruct, newrel, sizeof(RelationData));
			memcpy(newrel, relation, sizeof(RelationData));
			memcpy(relation, &tmpstruct, sizeof(RelationData));
		}


		SWAPFIELD(SMgrRelation, rd_smgr);

		SWAPFIELD(int, rd_refcnt);

		Assert(newrel->rd_isnailed == relation->rd_isnailed);

		SWAPFIELD(SubTransactionId, rd_createSubid);
		SWAPFIELD(SubTransactionId, rd_newRelfilenodeSubid);

		SWAPFIELD(Form_pg_class, rd_rel);

		memcpy(relation->rd_rel, newrel->rd_rel, CLASS_TUPLE_SIZE);

		if (keep_tupdesc)
			SWAPFIELD(TupleDesc, rd_att);
		if (keep_rules)
		{
			SWAPFIELD(RuleLock *, rd_rules);
			SWAPFIELD(MemoryContext, rd_rulescxt);
		}

		SWAPFIELD(struct PgStat_TableStatus *, pgstat_info);

#undef SWAPFIELD


		RelationDestroyRelation(newrel);
	}
}
