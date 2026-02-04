#!/usr/bin/env bash
set -euo pipefail

# ─── CONFIG ───────────────────────────────────────────────────────────────────
JOERN_CLI="./external/joern-4.0.386/joern-cli/joern"
BASE_DIR="./external/joern_sota/cpg"
EXPORT_ROOT="./external/joern_sota/func_exports"
SC_FILE="$(mktemp --suffix=.sc)"

# ─── EMBEDDED SCALA SCRIPT ────────────────────────────────────────────────────
cat > "${SC_FILE}" <<'EOF'
import io.shiftleft.codepropertygraph.Cpg
import io.shiftleft.semanticcpg.language._
import java.nio.file.{Files, Paths, StandardOpenOption}
import org.json4s._
import org.json4s.native.Serialization
import org.json4s.native.Serialization.write

implicit val formats: Formats = Serialization.formats(NoTypeHints)

@main def exportFunctions(): Unit = {
  // CLI args: 0 = path to CPG, 1 = output dir
  val Array(cpgBin, outDir) = sys.args
  val cpg = Cpg.apply(cpgBin)        // Joern 4 API
  cpg.method.groupBy(_.filename).foreach { case (file, methods) =>
    val base    = Paths.get(file).getFileName.toString.stripSuffix(".c")
    val outPath = Paths.get(outDir, s"$base.json")

    val funcs = methods.map { m =>
      val astNodes = m.astMinusRoot.toList

      def edgeMap(e: overflowdb.Edge) = Map(
        "src"  -> e.outNode.id,
        "dst"  -> e.inNode.id,
        "type" -> e.label
      )

      val astEs = astNodes.flatMap(_.outE.filter(_.label == "AST"))
      val cfgEs = astNodes.flatMap(_.outE.filter(_.label == "CFG"))
      val pdgEs = astNodes.flatMap(_.outE.filter(e =>
        Seq("REACHING_DEF","LAST_WRITE","CONTROLS","USE","REF").contains(e.label)
      ))

      val allEdges = (astEs ++ cfgEs ++ pdgEs).distinct.map(edgeMap)

      Map(
        "function" -> m.name,
        "file"     -> file,
        "nodes"    -> astNodes.map(n => Map(
                        "id"   -> n.id,
                        "type" -> n.label,
                        "code" -> n.code,
                        "line" -> n.lineNumber.getOrElse(-1)
                      )),
        "edges"    -> allEdges
      )
    }

    Files.write(outPath, write(funcs).getBytes, StandardOpenOption.CREATE)
  }
  cpg.close()
}
EOF

# ─── RUN EXPORT ────────────────────────────────────────────────────────────────
for split in train test valid; do
  # detect either cpg/bin or bare file
  if [[ -f "${BASE_DIR}/${split}/cpg.bin" ]]; then
    in_bin="${BASE_DIR}/${split}/cpg.bin"
  elif [[ -f "${BASE_DIR}/${split}" ]]; then
    in_bin="${BASE_DIR}/${split}"
  else
    echo "→ [${split}] no CPG found, skipping"
    continue
  fi

  out_dir="${EXPORT_ROOT}/${split}"
  mkdir -p "${out_dir}"
  echo "→ [${split}] exporting from ${in_bin}"
  # Pass positional args: <script> <cpg path> <outDir>
  "${JOERN_CLI}" "${SC_FILE}" "${in_bin}" "${out_dir}"
  echo "   ✓ $(find "${out_dir}" -name '*.json' | wc -l) files written"
done

# ─── CLEANUP ─────────────────────────────────────────────────────────────────
rm -f "${SC_FILE}"
echo "✅ Done. Per‐function AST+CFG+PDG exports in ${EXPORT_ROOT}"
