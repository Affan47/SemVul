data(const int iPatientColumn) const
    {

        QVariant val = _patientModel->data(_patientModel->index(_current, iPatientColumn));
        if (val.isValid() && !val.toString().isEmpty())
            return val;


        if (_episodeModel) {
            Form::FormItem *item = _formItemWithData.value(iPatientColumn, 0);
            if (item)
                return item->itemData()->data(item->patientDataRepresentation(), Form::IFormItemData::PatientModelRole);
        }
        return QVariant();
    }
