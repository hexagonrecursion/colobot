#!/usr/bin/env python3

'''
Generate C++-centric iwyu mappings.

The default mappings shipped with iwyu prefer C library headers over their C++ counterparts.
This script generates new mappings with swapped C and C++ headers

Usage:
c-to-cpp.py path/to/iwyu output/path
'''

import yaml, glob, pathlib, sys


_, SRC_DIR, DST_DIR = sys.argv


mapping = {
    "<assert.h>": "<cassert>",
    "<complex.h>": "<ccomplex>",
    "<ctype.h>": "<cctype>",
    "<errno.h>": "<cerrno>",
    "<fenv.h>": "<cfenv>",
    "<float.h>": "<cfloat>",
    "<inttypes.h>": "<cinttypes>",
    "<iso646.h>": "<ciso646>",
    "<limits.h>": "<climits>",
    "<locale.h>": "<clocale>",
    "<math.h>": "<cmath>",
    "<setjmp.h>": "<csetjmp>",
    "<signal.h>": "<csignal>",
    "<stdalign.h>": "<cstdalign>",
    "<stdarg.h>": "<cstdarg>",
    "<stdbool.h>": "<cstdbool>",
    "<stddef.h>": "<cstddef>",
    "<stdint.h>": "<cstdint>",
    "<stdio.h>": "<cstdio>",
    "<stdlib.h>": "<cstdlib>",
    "<string.h>": "<cstring>",
    "<tgmath.h>": "<ctgmath>",
    "<time.h>": "<ctime>",
    "<uchar.h>": "<cuchar>",
    "<wchar.h>": "<cwchar>",
    "<wctype.h>": "<cwctype>",
}

for k, v in list(mapping.items()):
    mapping[v] = k

def transform_row(row):
    if 'ref' in row:
        return row
    ((key, value),) = row.items()
    return {
        key: [
            mapping.get(s, s)
            for s in value
        ]
    }

for name in pathlib.Path(SRC_DIR).glob('*.imp'):
    with name.open('r') as f:
        data = yaml.safe_load(f)
    data = [transform_row(row) for row in data]
    with (pathlib.Path(DST_DIR) / name.name).open('w') as f:
        yaml.dump(data, f)

