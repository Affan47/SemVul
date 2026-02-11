gnc_employee_set_property (GObject         *object,
                           guint            prop_id,
                           const GValue          *value,
                           GParamSpec      *pspec)
{
    GncEmployee *emp;

    g_return_if_fail(GNC_IS_EMPLOYEE(object));

    emp = GNC_EMPLOYEE(object);
    switch (prop_id)
    {
    case PROP_USERNAME:
        gncEmployeeSetUsername(emp, g_value_get_string(value));
        break;
    case PROP_ID:
        gncEmployeeSetID(emp, g_value_get_string(value));
        break;
    case PROP_ACTIVE:
        gncEmployeeSetActive(emp, g_value_get_boolean(value));
        break;
    case PROP_LANGUAGE:
        gncEmployeeSetLanguage(emp, g_value_get_string(value));
        break;
    case PROP_CURRENCY:
        gncEmployeeSetCurrency(emp, g_value_get_object(value));
        break;
    case PROP_ACL:
        gncEmployeeSetAcl(emp, g_value_get_string(value));
        break;
    case PROP_ADDRESS:
        qofEmployeeSetAddr(emp, g_value_get_object(value));
        break;
    case PROP_WORKDAY:
        gncEmployeeSetWorkday(emp, *(gnc_numeric*)g_value_get_boxed(value));
        break;
    case PROP_RATE:
        gncEmployeeSetRate(emp, *(gnc_numeric*)g_value_get_boxed(value));
        break;
    case PROP_CCARD:
        gncEmployeeSetCCard(emp, g_value_get_object(value));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
