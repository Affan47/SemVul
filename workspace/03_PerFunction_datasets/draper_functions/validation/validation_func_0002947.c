get_any_key_for_address(struct ntb_keyring *keyring,
                        const struct ntb_address *address)
{
        struct ntb_key *key;
        int i;

        for (i = 0; i < ntb_pointer_array_length(&keyring->keys); i++) {
                key = ntb_pointer_array_get(&keyring->keys, i);

                if (ntb_address_equal(&key->address, address))
                        return key;
        }

        return NULL;
}
