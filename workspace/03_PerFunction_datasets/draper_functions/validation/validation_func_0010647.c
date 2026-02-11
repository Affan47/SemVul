EmitBaseTransformKeyValues(YAML::Emitter & out,
                                        const ConstTransformRcPtr & t)
        {
            if(t->getDirection() != TRANSFORM_DIR_FORWARD)
            {
                out << YAML::Key << "direction";
                out << YAML::Value << YAML::Flow << t->getDirection();
            }
        }
