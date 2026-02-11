operator<< (ostream& out, const AttributeValueList& al) {

    AttributeValueList* attrlist = (AttributeValueList*)&al;
    int maxout = attrlist->max_out();
    ALIterator i;
    for (attrlist->First(i); !attrlist->Done(i) && maxout!=0;) {
        maxout--;
	AttributeValue* attrval = attrlist->GetAttrVal(i);

	char* string;
        switch(attrval->type()) {
	    case AttributeValue::SymbolType:
	        out << attrval->symbol_ptr();
	        break;
	    case AttributeValue::StringType:
	      string = (char *) attrval->string_ptr();
	        out << "\"" << string << "\"";
	        break;
	    case AttributeValue::CharType:
	        out << "`\\" << std::setw(3) << std::setfill('0') << std::oct << (int)attrval->char_ref() << std::dec << "`" << std::resetiosflags(std::ios_base::basefield);
	        break;
	    case AttributeValue::UCharType:
	        out << "`\\" << std::setw(3) << std::setfill('0') << std::oct << (unsigned int) attrval->uchar_ref() << std::dec << "`" << std::resetiosflags(std::ios_base::basefield);
	        break;
	    case AttributeValue::ShortType:
	        out << attrval->short_ref();
	        break;
	    case AttributeValue::UShortType:
	        out << attrval->ushort_ref();
	        break;
	    case AttributeValue::IntType:
	        out << attrval->int_ref();
	        break;
	    case AttributeValue::UIntType:
	        out << attrval->uint_ref();
	        break;
	    case AttributeValue::LongType:
	        out << attrval->long_ref();
	        break;
	    case AttributeValue::ULongType:
	        out << attrval->ulong_ref();
	        break;
	    case AttributeValue::FloatType:
	        out << attrval->float_ref();
	        break;
	    case AttributeValue::DoubleType:
	        out << attrval->double_ref();
	        break;
	    case AttributeValue::BooleanType:
	        out << attrval->boolean_ref();
	        break;
	    case AttributeValue::ArrayType:
  	        out << "{";
	        out << *attrval->array_ref();
  	        out << "}";
	        break;
            default:
		out << "nil";
	        break;
	}

	attrlist->Next(i);
	if (!attrlist->Done(i))  out << ",";

    }
    if(maxout==0 && !attrlist->Done(i)) out << "...";
    return out;
}
