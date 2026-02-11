plpgsql_build_variable(const char *refname, int lineno, PLpgSQL_type *dtype,
					   bool add2namespace)
{
	PLpgSQL_variable *result;

	switch (dtype->ttype)
	{
		case PLPGSQL_TTYPE_SCALAR:
			{

				PLpgSQL_var *var;

				var = palloc0(sizeof(PLpgSQL_var));
				var->dtype = PLPGSQL_DTYPE_VAR;
				var->refname = pstrdup(refname);
				var->lineno = lineno;
				var->datatype = dtype;


				var->value = 0;
				var->isnull = true;
				var->freeval = false;

				plpgsql_adddatum((PLpgSQL_datum *) var);
				if (add2namespace)
					plpgsql_ns_additem(PLPGSQL_NSTYPE_VAR,
									   var->varno,
									   refname);
				result = (PLpgSQL_variable *) var;
				break;
			}
		case PLPGSQL_TTYPE_ROW:
			{

				PLpgSQL_row *row;

				row = build_row_from_class(dtype->typrelid);

				row->dtype = PLPGSQL_DTYPE_ROW;
				row->refname = pstrdup(refname);
				row->lineno = lineno;

				plpgsql_adddatum((PLpgSQL_datum *) row);
				if (add2namespace)
					plpgsql_ns_additem(PLPGSQL_NSTYPE_ROW,
									   row->rowno,
									   refname);
				result = (PLpgSQL_variable *) row;
				break;
			}
		case PLPGSQL_TTYPE_REC:
			{


				PLpgSQL_rec *rec;

				rec = palloc0(sizeof(PLpgSQL_rec));
				rec->dtype = PLPGSQL_DTYPE_REC;
				rec->refname = pstrdup(refname);
				rec->lineno = lineno;

				plpgsql_adddatum((PLpgSQL_datum *) rec);
				if (add2namespace)
					plpgsql_ns_additem(PLPGSQL_NSTYPE_REC,
									   rec->recno,
									   refname);
				result = (PLpgSQL_variable *) rec;
				break;
			}
		case PLPGSQL_TTYPE_PSEUDO:
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("variable \"%s\" has pseudo-type %s",
							refname, format_type_be(dtype->typoid))));
			result = NULL;
			break;
		default:
			elog(ERROR, "unrecognized ttype: %d", dtype->ttype);
			result = NULL;
			break;
	}

	return result;
}
