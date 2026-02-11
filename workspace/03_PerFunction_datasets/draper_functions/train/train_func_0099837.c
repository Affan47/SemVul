gnc_vendor_set_property (GObject         *object,
                         guint            prop_id,
                         const GValue          *value,
                         GParamSpec      *pspec)
{
    GncVendor *vendor;

    g_return_if_fail(GNC_IS_VENDOR(object));

    vendor = GNC_VENDOR(object);
    switch (prop_id)
    {
    case PROP_NAME:
        gncVendorSetName(vendor, g_value_get_string(value));
        break;
    case PROP_ID:
        gncVendorSetID(vendor, g_value_get_string(value));
        break;
    case PROP_NOTES:
        gncVendorSetNotes(vendor, g_value_get_string(value));
        break;
    case PROP_CURRENCY:
        gncVendorSetCurrency(vendor, g_value_get_object(value));
        break;
    case PROP_ACTIVE:
        gncVendorSetActive(vendor, g_value_get_boolean(value));
        break;
    case PROP_TAXTABLE_OVERRIDE:
        gncVendorSetTaxTableOverride(vendor, g_value_get_boolean(value));
        break;
    case PROP_BILLTERMS:
        gncVendorSetTerms(vendor, g_value_get_object(value));
        break;
    case PROP_TAXTABLE:
        gncVendorSetTaxTable(vendor, g_value_get_object(value));
        break;
    case PROP_ADDRESS:
        qofVendorSetAddr(vendor, g_value_get_object(value));
        break;
    case PROP_TAX_INCLUDED:
        gncVendorSetTaxIncluded(vendor, (GncTaxIncluded)g_value_get_int(value));
        break;
    case PROP_TAX_INCLUDED_STR:
        qofVendorSetTaxIncluded(vendor, g_value_get_string(value));
        break;
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
