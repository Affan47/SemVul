extractDiff(MathData & ar)
{
	Buffer * buf = ar.buffer();

	for (size_t i = 0; i < ar.size(); ++i) {
		MathData::iterator it = ar.begin() + i;


		if (!testDiffFrac(*it))
			continue;

		InsetMathFrac const * f = (*it)->asFracInset();
		if (!f) {
			lyxerr << "should not happen" << endl;
			continue;
		}


		auto_ptr<InsetMathDiff> diff(new InsetMathDiff(buf));


		MathData::iterator jt = it + 1;

		MathData numer(f->cell(0));
		splitScripts(numer);
		if (numer.size() > 1 && numer[1]->asScriptInset()) {


			if (numer.size() > 2)
				diff->cell(0) = MathData(buf, numer.begin() + 2, numer.end());
			else
				jt = extractTerm(diff->cell(0), jt, ar.end());
		} else {

			if (numer.size() > 1)
				diff->cell(0) = MathData(buf, numer.begin() + 1, numer.end());
			else
				jt = extractTerm(diff->cell(0), jt, ar.end());
		}


		MathData denom(f->cell(1));
		splitScripts(denom);
		for (MathData::iterator dt = denom.begin(); dt != denom.end();) {

			MathData::iterator et
				= find_if(dt + 1, denom.end(), &testDiffItem);


			MathData::iterator st = et - 1;
			InsetMathScript const * script = (*st)->asScriptInset();
			if (script && script->hasUp()) {

				int mult = 1;
				if (extractNumber(script->up(), mult)) {

					for (int i = 0; i < mult; ++i)
						diff->addDer(MathData(buf, dt + 1, st));
				}
			} else {

				diff->addDer(MathData(buf, dt + 1, et));
			}
			dt = et;
		}


		ar.erase(it + 1, jt);
		*it = MathAtom(diff.release());
	}

}
