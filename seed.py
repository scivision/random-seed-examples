#!/usr/bin/env python3
"""
example of setting RNG seed
"""

import numpy.random
import numpy as np

# r = numpy.random.default_rng(seed=0)
r = numpy.random.Generator(numpy.random.MT19937(seed=0))

print(np.array2string(r.standard_normal(3), precision=6)[1:-1])

# Twister MT19937: -0.625151 -0.596945  0.139097
