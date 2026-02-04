#!/usr/bin/env python3
"""
vuln_features.py - Extract Explicit Vulnerability Features

Since generic embeddings (GraphCodeBERT) don't distinguish vulnerable
from safe code, we add hand-crafted features that capture known
vulnerability patterns.

Features (20 dimensions):
- Dangerous sink detection (memcpy, strcpy, sprintf, free, etc.)
- User input source detection (read, recv, scanf, getenv, etc.)
- Bounds checking patterns
- Loop and control flow features
- Pointer arithmetic detection
"""

import re
import numpy as np
from typing import Dict, List, Optional

# ═══════════════════════════════════════════════════════════════════
# VULNERABILITY PATTERN DEFINITIONS
# ═══════════════════════════════════════════════════════════════════

DANGEROUS_SINKS = {
    'strcpy', 'strcat', 'sprintf', 'vsprintf', 'gets',
    'memcpy', 'memmove', 'memset', 'bcopy',
    'printf', 'fprintf', 'sprintf', 'snprintf', 'vprintf',
    'vfprintf', 'vsprintf', 'vsnprintf', 'syslog',
    'free', 'realloc', 'delete',
    'system', 'popen', 'exec', 'execl', 'execle', 'execlp',
    'execv', 'execve', 'execvp',
    'fopen', 'open', 'creat', 'unlink', 'remove', 'rename',
    'send', 'sendto', 'sendmsg', 'write',
}

SAFE_ALTERNATIVES = {
    'strncpy', 'strncat', 'snprintf', 'vsnprintf',
    'fgets', 'memcpy_s', 'strcpy_s', 'strcat_s',
    'strlcpy', 'strlcat',
}

USER_INPUT_SOURCES = {
    'scanf', 'fscanf', 'sscanf', 'gets', 'fgets', 'getchar',
    'getc', 'fgetc', 'getline', 'getdelim',
    'recv', 'recvfrom', 'recvmsg', 'read',
    'getenv', 'getopt', 'getopt_long',
    'fread', 'pread',
}

BOUNDS_CHECK_FUNCS = {
    'strlen', 'sizeof', 'strnlen', 'wcslen',
    'min', 'max', 'MIN', 'MAX',
}

ALLOC_FUNCS = {
    'malloc', 'calloc', 'realloc', 'alloca',
    'kmalloc', 'kzalloc', 'vmalloc', 'new',
}

NULL_CHECK_PATTERNS = [
    r'!=\s*NULL', r'==\s*NULL', r'!=\s*0', r'==\s*0',
    r'if\s*\(\s*\w+\s*\)', r'!\s*\w+',
]

POINTER_OPS = {'*', '&', '->', '['}
INT_OPS = {'+', '-', '*', '<<', '>>'}


class VulnFeatureExtractor:
    """Extract vulnerability-relevant features from code."""
    
    def __init__(self):
        self.dangerous_sinks = {s.lower() for s in DANGEROUS_SINKS}
        self.safe_alternatives = {s.lower() for s in SAFE_ALTERNATIVES}
        self.user_sources = {s.lower() for s in USER_INPUT_SOURCES}
        self.bounds_checks = {s.lower() for s in BOUNDS_CHECK_FUNCS}
        self.alloc_funcs = {s.lower() for s in ALLOC_FUNCS}
        self.null_patterns = [re.compile(p) for p in NULL_CHECK_PATTERNS]
    
    def extract_from_code(self, code: str) -> Dict[str, float]:
        """Extract features from code string."""
        if not code or not isinstance(code, str):
            return self._empty_features()
        
        code_lower = code.lower()
        tokens = set(re.findall(r'\b\w+\b', code_lower))
        
        features = {}
        
        # 1. Dangerous sinks
        dangerous = tokens & self.dangerous_sinks
        features['has_dangerous_sink'] = 1.0 if dangerous else 0.0
        features['num_dangerous_sinks'] = float(len(dangerous))
        features['dangerous_ratio'] = len(dangerous) / max(len(tokens), 1)
        
        # 2. Safe alternatives
        safe = tokens & self.safe_alternatives
        features['has_safe_alternative'] = 1.0 if safe else 0.0
        features['num_safe_alternatives'] = float(len(safe))
        
        # 3. User input sources
        inputs = tokens & self.user_sources
        features['has_user_input'] = 1.0 if inputs else 0.0
        features['num_user_inputs'] = float(len(inputs))
        
        # 4. Bounds checks
        bounds = tokens & self.bounds_checks
        features['has_bounds_check'] = 1.0 if bounds else 0.0
        features['num_bounds_checks'] = float(len(bounds))
        
        # 5. Allocations
        allocs = tokens & self.alloc_funcs
        features['has_allocation'] = 1.0 if allocs else 0.0
        features['num_allocations'] = float(len(allocs))
        
        # 6. NULL checks
        null_checks = sum(1 for p in self.null_patterns if p.search(code))
        features['has_null_check'] = 1.0 if null_checks > 0 else 0.0
        features['num_null_checks'] = float(null_checks)
        
        # 7. Pointer operations
        ptr_ops = sum(1 for c in code if c in POINTER_OPS)
        features['has_pointer_ops'] = 1.0 if ptr_ops > 0 else 0.0
        features['pointer_op_ratio'] = ptr_ops / max(len(code), 1)
        
        # 8. Loop detection
        loop_kw = {'for', 'while', 'do'}
        features['has_loop'] = 1.0 if (tokens & loop_kw) else 0.0
        
        # 9. Array access
        array_count = code.count('[')
        features['has_array_access'] = 1.0 if array_count > 0 else 0.0
        features['num_array_accesses'] = float(array_count)
        
        # 10. Risk score
        risk = (
            features['has_dangerous_sink'] * 2.0 +
            features['has_user_input'] * 1.5 +
            features['has_pointer_ops'] * 1.0 +
            features['has_array_access'] * 0.5 -
            features['has_bounds_check'] * 1.5 -
            features['has_null_check'] * 1.0 -
            features['has_safe_alternative'] * 2.0
        )
        features['risk_score'] = max(0.0, risk)
        
        return features
    
    def _empty_features(self) -> Dict[str, float]:
        """Return empty feature dict."""
        return {
            'has_dangerous_sink': 0.0, 'num_dangerous_sinks': 0.0,
            'dangerous_ratio': 0.0,
            'has_safe_alternative': 0.0, 'num_safe_alternatives': 0.0,
            'has_user_input': 0.0, 'num_user_inputs': 0.0,
            'has_bounds_check': 0.0, 'num_bounds_checks': 0.0,
            'has_allocation': 0.0, 'num_allocations': 0.0,
            'has_null_check': 0.0, 'num_null_checks': 0.0,
            'has_pointer_ops': 0.0, 'pointer_op_ratio': 0.0,
            'has_loop': 0.0, 'has_array_access': 0.0,
            'num_array_accesses': 0.0, 'risk_score': 0.0,
        }
    
    def extract_node_features(self, node_code: str, node_type: str) -> np.ndarray:
        """
        Extract vulnerability features for a single node.
        Returns a 20-dimensional feature vector.
        """
        features = self.extract_from_code(node_code)
        
        # Node type indicators
        node_upper = node_type.upper() if node_type else ''
        is_call = 1.0 if 'CALL' in node_upper else 0.0
        is_identifier = 1.0 if 'IDENTIFIER' in node_upper else 0.0
        is_literal = 1.0 if 'LITERAL' in node_upper else 0.0
        is_control = 1.0 if 'CONTROL' in node_upper else 0.0
        
        # Build 20-dim vector
        vec = np.array([
            features['has_dangerous_sink'],
            features['num_dangerous_sinks'],
            features['has_safe_alternative'],
            features['has_user_input'],
            features['num_user_inputs'],
            features['has_bounds_check'],
            features['num_bounds_checks'],
            features['has_allocation'],
            features['has_null_check'],
            features['has_pointer_ops'],
            features['pointer_op_ratio'],
            features['has_loop'],
            features['has_array_access'],
            features['num_array_accesses'],
            features['risk_score'],
            is_call,
            is_identifier,
            is_literal,
            is_control,
            features['dangerous_ratio'],
        ], dtype=np.float32)
        
        return vec
    
    @staticmethod
    def get_feature_dim() -> int:
        """Return feature vector dimension."""
        return 20


def test_feature_extraction():
    """Test the feature extractor."""
    
    extractor = VulnFeatureExtractor()
    
    vuln_samples = [
        "strcpy(buffer, user_input)",
        "sprintf(buf, \"%s\", data)",
        "gets(line)",
        "memcpy(dest, src, len)",
    ]
    
    safe_samples = [
        "strncpy(buffer, user_input, sizeof(buffer)-1)",
        "snprintf(buf, sizeof(buf), \"%s\", data)",
        "fgets(line, sizeof(line), stdin)",
        "if (len < sizeof(dest)) memcpy(dest, src, len)",
    ]
    
    print("=" * 60)
    print("VULNERABILITY FEATURE EXTRACTION TEST")
    print("=" * 60)
    
    print("\nVULNERABLE CODE:")
    for code in vuln_samples:
        f = extractor.extract_from_code(code)
        print(f"  {code}")
        print(f"    dangerous={f['has_dangerous_sink']}, safe_alt={f['has_safe_alternative']}, risk={f['risk_score']:.1f}")
    
    print("\nSAFE CODE:")
    for code in safe_samples:
        f = extractor.extract_from_code(code)
        print(f"  {code}")
        print(f"    dangerous={f['has_dangerous_sink']}, safe_alt={f['has_safe_alternative']}, bounds={f['has_bounds_check']}, risk={f['risk_score']:.1f}")
    
    print(f"\nFeature dimension: {VulnFeatureExtractor.get_feature_dim()}")
    print("=" * 60)


if __name__ == "__main__":
    test_feature_extraction()