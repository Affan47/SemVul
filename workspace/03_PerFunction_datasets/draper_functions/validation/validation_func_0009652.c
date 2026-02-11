OptimizeOpVec(OpRcPtrVec & ops)
    {
        if(ops.empty()) return;


        if(IsDebugLoggingEnabled())
        {
            LogDebug("Optimizing Op Vec...");
            LogDebug(SerializeOpVec(ops, 4));
        }

        OpRcPtrVec::size_type originalSize = ops.size();
        int total_noops = 0;
        int total_inverseops = 0;
        int total_combines = 0;
        int passes = 0;

        while(passes<=MAX_OPTIMIZATION_PASSES)
        {
            int noops = RemoveNoOps(ops);
            int inverseops = RemoveInverseOps(ops);
            int combines = CombineOps(ops);

            if(noops == 0 && inverseops==0 && combines==0)
            {

                break;
            }

            total_noops += noops;
            total_inverseops += inverseops;
            total_combines += combines;

            ++passes;
        }

        OpRcPtrVec::size_type finalSize = ops.size();

        if(passes == MAX_OPTIMIZATION_PASSES)
        {
            std::ostringstream os;
            os << "The max number of passes, " << passes << ", ";
            os << "was reached during optimization. This is likely a sign ";
            os << "that either the complexity of the color transform is ";
            os << "very high, or that some internal optimizers are in conflict ";
            os << "(undo-ing / redo-ing the other's results).";
            LogDebug(os.str().c_str());
        }

        if(IsDebugLoggingEnabled())
        {
            std::ostringstream os;
            os << "Optimized ";
            os << originalSize << "->" << finalSize << ", ";
            os << passes << " passes, ";
            os << total_noops << " noops removed, ";
            os << total_inverseops << " inverse ops removed\n";
            os << total_combines << " ops combines\n";
            os << SerializeOpVec(ops, 4);
            LogDebug(os.str());
        }
    }
