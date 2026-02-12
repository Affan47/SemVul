virtual Value evaluate(const Document& root) const {


        vector<Value> values;
        for (ExpressionVector::const_iterator i = vpOperand.begin(); i != vpOperand.end(); ++i) {
            values.push_back((*i)->evaluate(root));
        }
        return Value(values);
    }
