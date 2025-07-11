#!/usr/bin/env python3

# Copyright 2025 Technology Innovation Institute

# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at

#     http://www.apache.org/licenses/LICENSE-2.0

# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

class Prime:
    def __init__(self, name=None, reduction=None):
        self.name = name
        self.reduction = reduction
        self.prime = None
        self.optsub = None  # subtraction without using temp variables, only works for small primes
        self.full = False  # used in reduction, only set when a prime has full size (occupies all limbs fully), set to c
        self.lastbit = None  # used in reduction, set when the last limb has its most significant bit set
        self.pmp = False  # indicates a pseudo-Mersenne prime (PMP)
        self.n = None  # used for PMP, number of bits for the number used in reductions (may be larger than the actual prime, e.g. for C25519 n is set to 256)
        self.c = None  # used for PMP, value of the c used for reductions (may be different from actual prime, e.g. for C25519 c is set to 38)
        self.nlimbs = None  # number of 32bit limbs used to represent a number modulo prime
        self.realn = None  # used for PMP, number of bits for the real prime (e.g. for C25519, realn is set to 255)
        self.realc = None  # used for PMP, the real c value of the prime (e.g. for C25519, realc is set to 19)
        self.optfsb = None  # fsb without using temp variables, only works for small primes
        self.montmli = False  # captures the low degree polynomials of a solinas prime (only used in montgomery mli for primes with this format)
        self.modred_inplace = False  # indicates if modred function should be inplaced or not (currently always False)
        self.gap = None  # number of unused bits in the most significant limb

        # Add desired prime here if not already added
        if name == "m127":
            self.prime = 2**127 - 1
            self.n = 128
            self.realc = 1
            self.c = 2
            self.pmp = True
            self.optsub = True
            self.optfsb = True
        elif name == "PM266":
            self.prime = 2**266 - 3
            self.n = 266
            self.realc = 3
            self.c = 3
            self.pmp = True
            self.optsub = True
            self.optfsb = True
        elif name == "MFP7" or name == "apresSQIp7":
            self.prime = 2**145 * 3**9 * 59**3 * 311**3 * 317**3 * 503**3 - 1
            self.optsub = False
            self.optfsb = True
        elif name == "MFP4" or name == "apresSQIp4":
            self.prime = 2**246 * 3 * 67 - 1
            self.optsub = False
            self.optfsb = True
        elif name == "MFP1973":
            self.prime = 0x34E29E286B95D98C33A6A86587407437252C9E49355147FFFFFFFFFFFFFFFFFF
            self.optsub = False
            self.optfsb = True
        elif name == "C25519":
            self.prime = 2**255 - 19
            self.n = 256
            self.realn = 255
            self.realc = 19
            self.c = 38
            self.pmp = True
            self.optsub = True
            self.optfsb = True
        elif name == "NIST256":
            self.prime = 2**256 - 2**224 + 2**192 + 2**96 - 1
            self.lastbit = True
            self.optsub = True
            self.optfsb = True
        elif name == "x256189":
            self.prime = 2**256 - 189
            self.lastbit = True
            self.pmp = True
            self.optsub = False
        elif name == "C448":
            self.prime = 2**448 - 2**224 - 1
            self.lastbit = True
            self.optsub = False
            self.optfsb = True
            self.montmli = 2**224 + 1
        elif name == "GM480":
            self.prime = 2**480 - 2**240 - 1
            self.lastbit = True
            self.optsub = False
            self.optfsb = True
            self.montmli = 2**240 + 1
        elif name == "PM512" or name == "TII512569":
            self.prime = 2**512 - 569
            self.full = 569
            if reduction == "mont":
                self.full = False
            self.n = 512
            self.realc = 569
            self.c = 569
            self.pmp = True
            self.lastbit = True
            self.optsub = False
            self.optfsb = True
            self.modred_inplace = False
        elif name == "NIST521":
            self.prime = 2**521 - 1
            self.n = 521
            self.realc = 1
            self.c = 1
            self.pmp = True
            self.optsub = False
            self.optfsb = True
        elif name == "MFP47441":
            self.prime = 0x3DF6EEEAB0871A2C6AE604A45D10AD665BC2E0A90AEB751C722F669356EA4684C6174C1FFFFFFFFFFFFFFFFFFFFFFFF
            self.optsub = False
            self.optfsb = False
        elif name == "MFP318233":
            self.prime = 0x255946A8869BC68C15B0036936E79202BDBE6326507D01FE3AC5904A0DEA65FAF0A29A781974CE994C68ADA6E1FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
            self.optsub = False
            self.optfsb = False
        elif name == "MFP248":
            self.prime = 5 * 2**248 - 1
            self.optsub = True
            self.optfsb = True
        elif name == "MFP376":
            self.prime = 65 * 2**376 - 1
            self.optsub = False
            self.optfsb = True
        elif name == "MFP500":
            self.prime = 27 * 2**500 - 1
            self.optsub = False
            self.optfsb = True
        elif name == "PM336":
            self.prime = 2**336 - 3
            self.n = 336
            self.c = 3
            self.realc = 3
            self.pmp = True
            self.optsub = False
            self.optfsb = True
        elif name == "PM383":  # 2**383 - 31?
            self.prime = 2**383 - 187
            self.n = 383
            self.c = 187
            self.realc = 187
            self.pmp = True
            self.optsub = False
            self.optfsb = True
        elif name == "SECP256K1":
            self.prime = 2**256 - 2**32 - 977
            self.lastbit = True
            self.montmli = 2**32 + 977
            self.optsub = True
            self.optfsb = True
        elif name == "C41417":
            self.prime = 2**414 - 17
            self.n = 414
            self.c = 17
            self.realc = 17
            self.pmp = True
            self.optsub = False
            self.optfsb = True
        elif name == "PM225":
            self.prime = 2**225 - 49
            self.n = 225
            self.c = 49
            self.realc = 49
            self.pmp = True
            self.optsub = False
            self.optfsb = True

        # Arbitrary pseudo-Mersenne prime written as 2**n-c
        elif self.name_is_pmp():
            temp_n, temp_c = name[3:].split("-")
            self.name = "".join(c for c in name if c.isalnum())[:10]
            self.n = int(temp_n)
            self.c = int(temp_c)
            self.prime = 2**self.n - self.c
            self.realc = self.c
            self.pmp = True
            self.nlimbs = (self.n + 31) // 32

            self.optsub = (self.nlimbs <= 8) if self.optsub is None else self.optsub
            self.optfsb = (self.optsub or self.nlimbs <= 9) if self.optfsb is None else self.optfsb

            # self.lastbit = True if self.n % 32 == 0 else False

        # Arbitrary prime passed as a python expression
        elif name[0].isdigit():
            self.prime = eval(name)  # ast.literal_eval does not work here
            # Remove non-alphanumeric symbols
            self.name = "".join(c for c in name if c.isalnum())[:10]
            self.reduction = reduction or "mont"
            self.pmp = False if self.reduction == "mont" else True
            self.realn = self.realn or self.prime.bit_length()  # if not set, use prime size
            self.nlimbs = (self.realn + 31) // 32

        else:
            self.name = None
            self.prime = None
            self.reduction = None
            return
        # Set defaults if not set already
        if self.montmli == False:
            self.montmli = self.realc or False  # will only be set for solinas primes, so montmli=None when not a solinas prime
        self.n = self.n or self.prime.bit_length()  # if not set, use prime size
        self.realn = self.realn or self.n
        self.nlimbs = (self.n + 31) // 32  # calculates number of limbs necessary for a prime
        if self.pmp:
            self.c = self.c or 2**self.n - self.prime
        self.optsub = (self.nlimbs <= 8) if self.optsub is None else self.optsub
        self.optfsb = (self.optsub or self.nlimbs <= 8) if self.optfsb is None else self.optfsb
        self.lastbit = (self.realn % 32 == 0) if self.lastbit is None else self.lastbit
        self.gap = self.gap or self.nlimbs * 32 - self.n

    def __repr__(self):
        class_name = type(self).__name__
        return f"{class_name}(name={self.name!r}, reduction={self.reduction!r})"

    def __str__(self):
        return f"{self.prime}"

    # helper function for sqrt
    def makebig(self, value, nlimbs=None):
        nlimbs = nlimbs or self.nlimbs
        pw = []
        i = 0
        b = 2**32
        tp = value
        while i < self.nlimbs:
            pw.append(tp % b)
            tp = tp >> 32
            i = i + 1
        return pw

    # helper function for sqrt
    def inv_values(self, val, nlimbs=None):
        nlimbs = nlimbs or self.nlimbs
        p1 = val - 1
        PM1D2 = 0
        while (p1 % 2) == 0:
            PM1D2 += 1
            p1 >>= 1
        e = 1 << PM1D2
        PE = (val - 1 - e) // (2 * e)
        qnr = 0
        roi = 0
        if PM1D2 == 1:
            roi = val - 1
        if PM1D2 == 2:
            roi = pow(2, (val - 1) // 4, val)
        if PM1D2 > 2:
            qnr = 2
            while pow(qnr, (val - 1) // 2, val) == 1:
                qnr += 1
            roi = pow(qnr, (val - 1) // e, val)

        # convert to radix representation
        ROI = self.makebig(roi, nlimbs)
        return PM1D2, ROI, PE

    # helper function that calculates prime factors of a given prime
    def prime_factors(self, prime=None, nlimbs=None):
        prime = prime or self.prime
        nlimbs = nlimbs or self.nlimbs
        prime_factors = []
        for i in range(nlimbs):
            prime_factors.append((prime >> 32 * i) % (2**32))
        return prime_factors

    # checks if prime is written in pmp form (2**n-c)
    def name_is_pmp(self):
        if self.name[:3] != "2**" or self.name.count("-") != 1:
            return False
        n, c = self.name[3:].split("-")
        if n.isdigit() and c.isdigit():
            return True
        return False
