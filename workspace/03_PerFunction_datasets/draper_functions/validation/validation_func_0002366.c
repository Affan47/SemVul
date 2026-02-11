geocode_place_set_property(GObject      *object,
                           guint         property_id,
                           const GValue *value,
                           GParamSpec   *pspec)
{
        GeocodePlace *place = GEOCODE_PLACE (object);

        switch (property_id) {
        case PROP_NAME:
                place->priv->name = g_value_dup_string (value);
                break;

        case PROP_PLACE_TYPE:
                place->priv->place_type = g_value_get_enum (value);
                break;

        case PROP_LOCATION:
                place->priv->location = g_value_dup_object (value);
                break;

        case PROP_STREET_ADDRESS:
                geocode_place_set_street_address (place,
                                                  g_value_get_string (value));
                break;

        case PROP_STREET:
                geocode_place_set_street (place, g_value_get_string (value));
                break;

        case PROP_BUILDING:
                geocode_place_set_building (place, g_value_get_string (value));
                break;

        case PROP_POSTAL_CODE:
                geocode_place_set_postal_code (place,
                                               g_value_get_string (value));
                break;

        case PROP_AREA:
                geocode_place_set_area (place, g_value_get_string (value));
                break;

        case PROP_TOWN:
                geocode_place_set_town (place, g_value_get_string (value));
                break;

        case PROP_COUNTY:
                geocode_place_set_county (place, g_value_get_string (value));
                break;

        case PROP_STATE:
                geocode_place_set_state (place, g_value_get_string (value));
                break;

        case PROP_ADMINISTRATIVE_AREA:
                geocode_place_set_administrative_area (place,
                                                       g_value_get_string (value));
                break;

        case PROP_COUNTRY_CODE:
                geocode_place_set_country_code (place,
                                                g_value_get_string (value));
                break;

        case PROP_COUNTRY:
                geocode_place_set_country (place,
                                           g_value_get_string (value));
                break;

        case PROP_CONTINENT:
                geocode_place_set_continent (place, g_value_get_string (value));
                break;

        case PROP_ICON:
                _geocode_place_set_icon (place, g_value_get_object (value));
                break;

        default:
                G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
                break;
        }
}
