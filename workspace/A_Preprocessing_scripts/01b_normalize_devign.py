#!/usr/bin/env python3
"""
01b_normalize_devign_dynamic.py

DYNAMIC Normalization - No hardcoded strings!

Strategy:
  1. Parse code with tree-sitter
  2. Find all FUNCTION DEFINITIONS (user-defined)
  3. Find all FUNCTION CALLS
  4. If a function is CALLED but NOT DEFINED → External/Library → PRESERVE
  5. If a function is DEFINED in this file → User-defined → NORMALIZE
  
This automatically preserves:
  - strcpy, malloc, printf (called but not defined)
  - Any library function from any library
  
And normalizes:
  - User's own helper functions (defined in the file)
  - All variables

Additional strategies:
  - Cross-file frequency analysis
  - Include/header analysis
  - Type-based preservation

Usage:
  python 01b_normalize_devign_dynamic.py \
    --input-dir /path/to/devign/json \
    --output-dir /path/to/output \
    --strategy definition  # or: frequency, hybrid

  # Build frequency vocab from corpus first (optional)
  python 01b_normalize_devign_dynamic.py \
    --input-dir /path/to/devign/json \
    --build-vocab \
    --vocab-output /path/to/func_vocab.json
"""

import argparse
import json
import logging
import re
from collections import Counter, defaultdict
from pathlib import Path
from typing import Any, Dict, List, Optional, Set, Tuple

logger = logging.getLogger("dynamic_normalize")

# ============================================================================
# Tree-sitter setup
# ============================================================================

try:
    from tree_sitter import Language, Parser, Node
    HAS_TREESITTER = True
except ImportError:
    HAS_TREESITTER = False
    logger.warning("tree-sitter not available, using regex fallback")

# Will be initialized lazily
_C_PARSER = None
_CPP_PARSER = None

def get_parser(lang: str):
    """Lazy initialization of parsers."""
    global _C_PARSER, _CPP_PARSER
    
    if not HAS_TREESITTER:
        return None
    
    if _C_PARSER is None:
        TS_SO = Path("./external/linevul/build/my-languages.so")
        if TS_SO.exists():
            C_LANG = Language(str(TS_SO), "c")
            CPP_LANG = Language(str(TS_SO), "cpp")
            
            _C_PARSER = Parser()
            _C_PARSER.set_language(C_LANG)
            
            _CPP_PARSER = Parser()
            _CPP_PARSER.set_language(CPP_LANG)
    
    return _CPP_PARSER if lang == "cpp" else _C_PARSER


# ============================================================================
# C Keywords (always preserve - this is the ONLY hardcoded list, and it's
# the language specification, not application-specific)
# ============================================================================

C_KEYWORDS = frozenset({
    'auto', 'break', 'case', 'char', 'const', 'continue', 'default', 'do',
    'double', 'else', 'enum', 'extern', 'float', 'for', 'goto', 'if',
    'inline', 'int', 'long', 'register', 'restrict', 'return', 'short',
    'signed', 'sizeof', 'static', 'struct', 'switch', 'typedef', 'union',
    'unsigned', 'void', 'volatile', 'while', '_Bool', '_Complex', '_Imaginary',
    # C++ keywords
    'bool', 'true', 'false', 'nullptr', 'class', 'public', 'private', 'protected',
    'virtual', 'override', 'final', 'new', 'delete', 'this', 'throw', 'try', 'catch',
    'namespace', 'using', 'template', 'typename', 'explicit', 'mutable', 'friend',
    'operator', 'const_cast', 'static_cast', 'dynamic_cast', 'reinterpret_cast',
    # Common macros that are essentially keywords
    'NULL', 'EOF', 'TRUE', 'FALSE',
})


# ============================================================================
# Strategy 1: Definition-based (RECOMMENDED)
# ============================================================================

class DefinitionBasedAnalyzer:
    """
    Analyzes code to find:
    - Functions DEFINED in this file → normalize
    - Functions CALLED but not defined → preserve (external/library)
    - Variables → normalize
    """
    
    def __init__(self):
        self.defined_functions: Set[str] = set()
        self.called_functions: Set[str] = set()
        self.all_identifiers: List[str] = []
        self.type_identifiers: Set[str] = set()  # struct names, typedefs, etc.
    
    def analyze(self, code: str) -> None:
        """Analyze code to extract definitions and calls."""
        self.defined_functions.clear()
        self.called_functions.clear()
        self.all_identifiers.clear()
        self.type_identifiers.clear()
        
        lang = detect_language(code)
        parser = get_parser(lang)
        
        if parser is None:
            self._analyze_regex(code)
            return
        
        try:
            code_bytes = code.encode('utf-8', errors='ignore')
            tree = parser.parse(code_bytes)
            if tree and tree.root_node:
                self._analyze_tree(tree.root_node, code_bytes)
        except Exception as e:
            logger.warning(f"Tree-sitter parse failed: {e}, using regex")
            self._analyze_regex(code)
    
    def _analyze_tree(self, node: 'Node', code_bytes: bytes) -> None:
        """Recursively analyze AST."""
        
        # Function definitions
        if node.type in ('function_definition', 'function_declarator'):
            for child in node.children:
                if child.type == 'identifier':
                    name = code_bytes[child.start_byte:child.end_byte].decode('utf-8', errors='ignore')
                    self.defined_functions.add(name)
                    break
                # Handle declarator wrapping
                if child.type in ('function_declarator', 'pointer_declarator'):
                    self._find_func_name(child, code_bytes)
        
        # Function calls
        if node.type == 'call_expression':
            # First child is usually the function being called
            func_node = node.children[0] if node.children else None
            if func_node:
                if func_node.type == 'identifier':
                    name = code_bytes[func_node.start_byte:func_node.end_byte].decode('utf-8', errors='ignore')
                    self.called_functions.add(name)
                elif func_node.type == 'field_expression':
                    # obj->method() or obj.method() - get the method name
                    for child in func_node.children:
                        if child.type == 'field_identifier':
                            name = code_bytes[child.start_byte:child.end_byte].decode('utf-8', errors='ignore')
                            self.called_functions.add(name)
        
        # Type declarations (struct, typedef, enum)
        if node.type in ('struct_specifier', 'union_specifier', 'enum_specifier', 'type_definition'):
            for child in node.children:
                if child.type in ('type_identifier', 'identifier'):
                    name = code_bytes[child.start_byte:child.end_byte].decode('utf-8', errors='ignore')
                    self.type_identifiers.add(name)
        
        # All identifiers (for variable collection)
        if node.type == 'identifier':
            name = code_bytes[node.start_byte:node.end_byte].decode('utf-8', errors='ignore')
            self.all_identifiers.append(name)
        
        # Recurse
        for child in node.children:
            self._analyze_tree(child, code_bytes)
    
    def _find_func_name(self, node: 'Node', code_bytes: bytes) -> None:
        """Find function name in nested declarators."""
        for child in node.children:
            if child.type == 'identifier':
                name = code_bytes[child.start_byte:child.end_byte].decode('utf-8', errors='ignore')
                self.defined_functions.add(name)
                return
            if child.type in ('function_declarator', 'pointer_declarator', 'parenthesized_declarator'):
                self._find_func_name(child, code_bytes)
    
    def _analyze_regex(self, code: str) -> None:
        """Fallback regex analysis."""
        # Function definitions: type name(...) {
        func_def_pattern = re.compile(
            r'(?:(?:static|inline|extern|const)\s+)*'
            r'(?:\w+\s*\*?\s+)+'  # return type
            r'(\w+)\s*\([^)]*\)\s*{'  # function name
        )
        for match in func_def_pattern.finditer(code):
            self.defined_functions.add(match.group(1))
        
        # Function calls: name(
        func_call_pattern = re.compile(r'\b(\w+)\s*\(')
        for match in func_call_pattern.finditer(code):
            name = match.group(1)
            # Exclude control flow keywords
            if name not in ('if', 'for', 'while', 'switch', 'sizeof', 'typeof'):
                self.called_functions.add(name)
        
        # All identifiers
        id_pattern = re.compile(r'\b([a-zA-Z_][a-zA-Z0-9_]*)\b')
        self.all_identifiers = id_pattern.findall(code)
    
    def get_external_functions(self) -> Set[str]:
        """Get functions that are called but not defined (external/library)."""
        return self.called_functions - self.defined_functions
    
    def get_user_defined_functions(self) -> Set[str]:
        """Get functions defined in this file."""
        return self.defined_functions
    
    def should_preserve(self, identifier: str) -> bool:
        """Determine if identifier should be preserved."""
        # Always preserve C keywords
        if identifier in C_KEYWORDS:
            return True
        
        # Preserve external function calls (library functions)
        external = self.get_external_functions()
        if identifier in external:
            return True
        
        # Preserve type names (structs, typedefs)
        if identifier in self.type_identifiers:
            return True
        
        return False


# ============================================================================
# Strategy 2: Frequency-based (corpus-wide analysis)
# ============================================================================

class FrequencyVocabulary:
    """
    Build vocabulary from corpus to identify common (library) vs rare (user) functions.
    
    Intuition:
    - `malloc` appears in thousands of files → likely library function → preserve
    - `my_helper` appears in 1 file → user-defined → normalize
    """
    
    def __init__(self):
        self.function_file_counts: Counter = Counter()  # func_name -> num_files
        self.function_total_counts: Counter = Counter()  # func_name -> total calls
        self.total_files: int = 0
        self.threshold_percentile: float = 0.9  # Top 10% most common = library
    
    def add_file(self, code: str) -> None:
        """Analyze one file and update counts."""
        analyzer = DefinitionBasedAnalyzer()
        analyzer.analyze(code)
        
        # Count external calls (library candidates)
        external = analyzer.get_external_functions()
        
        # Update file counts (each function counted once per file)
        for func in external:
            self.function_file_counts[func] += 1
        
        # Update total counts
        self.function_total_counts.update(external)
        self.total_files += 1
    
    def compute_preserved_set(self, min_file_count: int = None, 
                               min_file_ratio: float = 0.01) -> Set[str]:
        """
        Compute which functions to preserve based on frequency.
        
        Args:
            min_file_count: Minimum number of files function must appear in
            min_file_ratio: Minimum ratio of files (e.g., 0.01 = 1% of files)
        """
        if min_file_count is None:
            min_file_count = max(2, int(self.total_files * min_file_ratio))
        
        preserved = set()
        for func, count in self.function_file_counts.items():
            if count >= min_file_count:
                preserved.add(func)
        
        return preserved
    
    def save(self, path: Path) -> None:
        """Save vocabulary to JSON."""
        data = {
            'total_files': self.total_files,
            'function_file_counts': dict(self.function_file_counts),
            'function_total_counts': dict(self.function_total_counts),
        }
        with open(path, 'w') as f:
            json.dump(data, f, indent=2)
        logger.info(f"Saved vocabulary to {path}")
    
    @classmethod
    def load(cls, path: Path) -> 'FrequencyVocabulary':
        """Load vocabulary from JSON."""
        with open(path) as f:
            data = json.load(f)
        
        vocab = cls()
        vocab.total_files = data['total_files']
        vocab.function_file_counts = Counter(data['function_file_counts'])
        vocab.function_total_counts = Counter(data['function_total_counts'])
        return vocab


# ============================================================================
# Strategy 3: Hybrid (definition + frequency)
# ============================================================================

class HybridAnalyzer:
    """
    Combines definition-based and frequency-based analysis.
    
    Preserves:
    - Functions called but not defined (per-file definition analysis)
    - AND functions that appear frequently across corpus (frequency analysis)
    """
    
    def __init__(self, frequency_vocab: Optional[FrequencyVocabulary] = None):
        self.definition_analyzer = DefinitionBasedAnalyzer()
        self.frequency_vocab = frequency_vocab
        self.frequency_preserved: Set[str] = set()
        
        if frequency_vocab:
            self.frequency_preserved = frequency_vocab.compute_preserved_set()
    
    def analyze(self, code: str) -> None:
        """Analyze code."""
        self.definition_analyzer.analyze(code)
    
    def should_preserve(self, identifier: str) -> bool:
        """Determine if identifier should be preserved."""
        # Definition-based check
        if self.definition_analyzer.should_preserve(identifier):
            return True
        
        # Frequency-based check
        if identifier in self.frequency_preserved:
            return True
        
        return False


# ============================================================================
# Normalization engine
# ============================================================================

def detect_language(code: str) -> str:
    """Detect C vs C++."""
    cpp_markers = ("class ", "namespace ", "std::", "template<", "::")
    for marker in cpp_markers:
        if marker in code:
            return "cpp"
    return "c"


def strip_comments(code: str) -> str:
    """Strip C/C++ comments."""
    if not code:
        return code

    IN_CODE, IN_STR, IN_CHAR, IN_SL_COMMENT, IN_ML_COMMENT = range(5)
    state = IN_CODE
    result = []
    i = 0
    n = len(code)

    while i < n:
        ch = code[i]
        nxt = code[i + 1] if i + 1 < n else ""

        if state == IN_CODE:
            if ch == "/" and nxt == "/":
                state = IN_SL_COMMENT
                i += 2
                continue
            if ch == "/" and nxt == "*":
                state = IN_ML_COMMENT
                i += 2
                continue
            if ch == '"':
                state = IN_STR
            elif ch == "'":
                state = IN_CHAR
            result.append(ch)
            i += 1

        elif state == IN_SL_COMMENT:
            if ch == "\n":
                result.append(ch)
                state = IN_CODE
            i += 1

        elif state == IN_ML_COMMENT:
            if ch == "*" and nxt == "/":
                state = IN_CODE
                i += 2
            else:
                i += 1

        elif state == IN_STR:
            result.append(ch)
            if ch == "\\" and nxt:
                result.append(nxt)
                i += 2
                continue
            if ch == '"':
                state = IN_CODE
            i += 1

        elif state == IN_CHAR:
            result.append(ch)
            if ch == "\\" and nxt:
                result.append(nxt)
                i += 2
                continue
            if ch == "'":
                state = IN_CODE
            i += 1

    return "".join(result)


def normalize_whitespace(code: str) -> str:
    """Normalize whitespace."""
    if not code:
        return code
    code = code.replace("\r\n", "\n").replace("\r", "\n")
    code = code.replace("\t", "    ")
    lines = [ln.rstrip() for ln in code.split("\n")]
    # Collapse multiple blank lines
    result = []
    prev_blank = False
    for ln in lines:
        is_blank = not ln.strip()
        if is_blank and prev_blank:
            continue
        result.append(ln)
        prev_blank = is_blank
    return "\n".join(result)


def normalize_code_dynamic(
    code: str,
    analyzer: Optional[DefinitionBasedAnalyzer] = None,
    hybrid_analyzer: Optional[HybridAnalyzer] = None
) -> str:
    """
    Normalize code using dynamic analysis.
    
    Args:
        code: Source code to normalize
        analyzer: Definition-based analyzer (created if None)
        hybrid_analyzer: Hybrid analyzer (takes precedence if provided)
    """
    if not code:
        return code
    
    # Preprocess
    code = strip_comments(code)
    code = normalize_whitespace(code)
    
    # Analyze
    if hybrid_analyzer:
        hybrid_analyzer.analyze(code)
        should_preserve = hybrid_analyzer.should_preserve
    else:
        if analyzer is None:
            analyzer = DefinitionBasedAnalyzer()
        analyzer.analyze(code)
        should_preserve = analyzer.should_preserve
    
    # Get all identifiers
    if hybrid_analyzer:
        all_ids = hybrid_analyzer.definition_analyzer.all_identifiers
        defined_funcs = hybrid_analyzer.definition_analyzer.defined_functions
    else:
        all_ids = analyzer.all_identifiers
        defined_funcs = analyzer.defined_functions
    
    # Build replacement map
    replacements: Dict[str, str] = {}
    var_idx = 1
    func_idx = 0
    
    for ident in all_ids:
        if ident in replacements:
            continue
        
        if should_preserve(ident):
            continue
        
        if ident in defined_funcs:
            replacements[ident] = f"Func{func_idx}"
            func_idx += 1
        else:
            replacements[ident] = f"Var{var_idx}"
            var_idx += 1
    
    if not replacements:
        return code
    
    # Apply replacements (longest first to avoid partial matches)
    tokens = sorted(replacements.keys(), key=len, reverse=True)
    pattern = re.compile(r"\b(" + "|".join(map(re.escape, tokens)) + r")\b")
    
    return pattern.sub(lambda m: replacements.get(m.group(0), m.group(0)), code)


# ============================================================================
# Vocabulary building (for frequency-based approach)
# ============================================================================

def build_frequency_vocab(input_dir: Path, splits: List[str], func_key: str) -> FrequencyVocabulary:
    """Build frequency vocabulary from corpus."""
    vocab = FrequencyVocabulary()
    
    for split in splits:
        jsonl_path = input_dir / f"{split}.jsonl"
        if not jsonl_path.exists():
            continue
        
        logger.info(f"Processing {jsonl_path} for vocabulary...")
        
        with open(jsonl_path) as f:
            for i, line in enumerate(f):
                line = line.strip()
                if not line:
                    continue
                
                try:
                    rec = json.loads(line)
                    code = rec.get(func_key) or rec.get("code") or rec.get("func_src")
                    if code:
                        vocab.add_file(code)
                except:
                    continue
                
                if (i + 1) % 5000 == 0:
                    logger.info(f"  Processed {i+1} records...")
    
    logger.info(f"Vocabulary built from {vocab.total_files} files")
    logger.info(f"Unique external functions: {len(vocab.function_file_counts)}")
    
    # Show top functions
    logger.info("Top 30 most common external functions:")
    for func, count in vocab.function_file_counts.most_common(30):
        logger.info(f"  {func}: {count} files ({100*count/vocab.total_files:.1f}%)")
    
    return vocab


# ============================================================================
# Main processing
# ============================================================================

def process_split(
    input_dir: Path,
    output_dir: Path,
    split: str,
    func_key: str,
    strategy: str,
    frequency_vocab: Optional[FrequencyVocabulary] = None
) -> None:
    """Process one split."""
    in_path = input_dir / f"{split}.jsonl"
    out_path = output_dir / f"{split}_normalized.jsonl"
    
    if not in_path.exists():
        logger.warning(f"Input not found: {in_path}")
        return
    
    output_dir.mkdir(parents=True, exist_ok=True)
    
    # Setup analyzer based on strategy
    if strategy == 'frequency' and frequency_vocab:
        preserved = frequency_vocab.compute_preserved_set()
        logger.info(f"Frequency-preserved functions: {len(preserved)}")
    elif strategy == 'hybrid' and frequency_vocab:
        hybrid = HybridAnalyzer(frequency_vocab)
    else:
        hybrid = None
    
    analyzer = DefinitionBasedAnalyzer()
    
    num_total = 0
    num_normalized = 0
    
    # Track what gets preserved (for reporting)
    preserved_funcs: Counter = Counter()
    
    with open(in_path) as src, open(out_path, 'w') as dst:
        for line in src:
            line = line.strip()
            if not line:
                continue
            
            try:
                rec = json.loads(line)
            except:
                continue
            
            num_total += 1
            code = rec.get(func_key) or rec.get("code") or rec.get("func_src")
            
            if isinstance(code, str):
                if strategy == 'hybrid' and hybrid:
                    norm_code = normalize_code_dynamic(code, hybrid_analyzer=hybrid)
                    # Track preserved
                    hybrid.analyze(code)
                    for func in hybrid.definition_analyzer.get_external_functions():
                        preserved_funcs[func] += 1
                else:
                    norm_code = normalize_code_dynamic(code, analyzer=analyzer)
                    # Track preserved
                    for func in analyzer.get_external_functions():
                        preserved_funcs[func] += 1
                
                rec = dict(rec)
                rec[func_key] = norm_code
                num_normalized += 1
            
            dst.write(json.dumps(rec, ensure_ascii=False) + "\n")
            
            if num_total % 2000 == 0:
                logger.info(f"[{split}] Processed {num_total}...")
    
    logger.info(f"[{split}] Done: {num_normalized}/{num_total} normalized")
    
    # Report most commonly preserved functions
    logger.info(f"[{split}] Top 20 preserved external functions:")
    for func, count in preserved_funcs.most_common(20):
        logger.info(f"  {func}: {count}")


def demonstrate():
    """Show how dynamic normalization works."""
    example = '''
int process_data(char *user_input, size_t input_len) {
    char *buffer = malloc(input_len + 1);
    if (buffer == NULL) {
        perror("malloc failed");
        return -1;
    }
    
    // This is vulnerable - no bounds check!
    strcpy(buffer, user_input);
    
    // Process the data
    int result = my_helper_func(buffer);
    
    printf("Result: %d\\n", result);
    free(buffer);
    return result;
}

static int my_helper_func(const char *data) {
    return strlen(data);
}
'''
    
    print("=" * 70)
    print("DYNAMIC NORMALIZATION DEMO")
    print("=" * 70)
    
    print("\n[ORIGINAL CODE]")
    print(example.strip())
    
    analyzer = DefinitionBasedAnalyzer()
    analyzer.analyze(example)
    
    print("\n[ANALYSIS RESULTS]")
    print(f"Defined functions: {analyzer.defined_functions}")
    print(f"Called functions: {analyzer.called_functions}")
    print(f"External (library) functions: {analyzer.get_external_functions()}")
    
    print("\n[NORMALIZED CODE]")
    normalized = normalize_code_dynamic(example, analyzer=analyzer)
    print(normalized.strip())
    
    print("\n" + "=" * 70)
    print("KEY INSIGHT")
    print("=" * 70)
    print("""
PRESERVED (called but not defined = external/library):
  ✅ malloc, perror, strcpy, printf, free, strlen

NORMALIZED (defined in this file = user code):
  ❌ process_data → Func0
  ❌ my_helper_func → Func1
  ❌ user_input → Var1, buffer → Var2, etc.

NO HARDCODED LISTS! The analyzer automatically detects that:
  - malloc() is called but never defined → must be external → preserve
  - my_helper_func() is defined below → user code → normalize
""")


# ============================================================================
# CLI
# ============================================================================

def main():
    parser = argparse.ArgumentParser(
        description="Dynamic normalization - no hardcoded function lists!"
    )
    parser.add_argument("--input-dir", type=str, help="Input directory")
    parser.add_argument("--output-dir", type=str, help="Output directory")
    parser.add_argument("--splits", nargs="+", default=["train", "validation", "test"])
    parser.add_argument("--func-key", default="func")
    parser.add_argument(
        "--strategy",
        choices=["definition", "frequency", "hybrid"],
        default="definition",
        help="Strategy: definition (per-file), frequency (corpus-wide), hybrid (both)"
    )
    parser.add_argument("--build-vocab", action="store_true",
                       help="Build frequency vocabulary from corpus")
    parser.add_argument("--vocab-output", type=str,
                       help="Output path for frequency vocabulary")
    parser.add_argument("--vocab-input", type=str,
                       help="Load pre-built frequency vocabulary")
    parser.add_argument("--demo", action="store_true", help="Show demo")
    parser.add_argument("--log-level", default="INFO")
    
    args = parser.parse_args()
    
    logging.basicConfig(
        level=getattr(logging, args.log_level),
        format="%(asctime)s [%(levelname)s] %(message)s"
    )
    
    if args.demo:
        demonstrate()
        return
    
    if not args.input_dir:
        parser.error("--input-dir required unless --demo")
    
    input_dir = Path(args.input_dir).expanduser().resolve()
    
    # Build vocabulary if requested
    if args.build_vocab:
        vocab = build_frequency_vocab(input_dir, args.splits, args.func_key)
        if args.vocab_output:
            vocab.save(Path(args.vocab_output))
        return
    
    # Load vocabulary if provided
    frequency_vocab = None
    if args.vocab_input:
        frequency_vocab = FrequencyVocabulary.load(Path(args.vocab_input))
        logger.info(f"Loaded vocabulary with {len(frequency_vocab.function_file_counts)} functions")
    
    if not args.output_dir:
        parser.error("--output-dir required for normalization")
    
    output_dir = Path(args.output_dir).expanduser().resolve()
    
    logger.info(f"Strategy: {args.strategy}")
    logger.info(f"Input: {input_dir}")
    logger.info(f"Output: {output_dir}")
    
    for split in args.splits:
        process_split(
            input_dir, output_dir, split,
            args.func_key, args.strategy, frequency_vocab
        )
    
    logger.info("Done!")


if __name__ == "__main__":
    main()

"""
python 01b_normalize_devign.py \
  --input-dir "./datasets/devign_full/json" \
  --output-dir "./workspace/01_Normalized_datasets/05_normalized_devign" \
  --splits train validation test \
  --func-key func \
  --log-level INFO





# Step 1: Build vocabulary from corpus (analyzes what functions are common)
python 01b_normalize_devign.py \
    --input-dir "./datasets/devign_full/json" \
    --build-vocab \
    --splits train validation test \
    --vocab-output ./Clean_exports/devign_vocab_normfunc_v2/func_vocab.json



# Step 2: Normalize using HYBRID (definition + frequency)

python 01b_normalize_devign.py \
    --input-dir "./datasets/devign_full/json" \
    --output-dir "./workspace/01_Normalized_datasets/05_normalized_devign" \
    --splits train validation test \
    --strategy frequency \
    --vocab-output ./Clean_exports/devign_vocab_normfunc_v2/func_vocab.json

"""
