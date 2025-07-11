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

class Interval:
    USEHEX = True

    def __init__(self, lb, ub):
        self.lb = lb
        self.ub = ub

    def __add__(self, other):
        if isinstance(other, Interval):
            return Interval(self.lb + other.lb, self.ub + other.ub)
        elif isinstance(other, int):
            return Interval(self.lb + other, self.ub + other)
        else:
            raise Exception()
    
    def __mul__(self, other):
        if isinstance(other, Interval):
            return Interval(self.lb * other.lb, self.ub * other.ub)
        elif isinstance(other, int):
            return Interval(self.lb * other, self.ub * other)
        else:
            raise Exception()
    
    def __sub__(self, other):
        if isinstance(other, Interval):
            return Interval(self.lb - other.ub, self.ub - other.lb)
        elif isinstance(other, int):
            return Interval(self.lb - other, self.ub - other)
        else:
            raise Exception()
    
    def __lshift__(self, other):
        if isinstance(other, int):
            return Interval(self.lb << other, self.ub << other)
        else:
            raise Exception()
    
    def __rshift__(self, other):
        if isinstance(other, int):
            return Interval(self.lb >> other, self.ub >> other)
        else:
            raise Exception()
    
    def __floordiv__(self, other):
        if isinstance(other, Interval):
            return Interval(self.lb // other.ub, self.ub // other.lb)
        elif isinstance(other, int):
            return Interval(self.lb // other, self.ub // other)
        else:
            raise Exception()
    
    # <other> needs to be a valid mask (of the form 2^n-1)
    def __and__(self, other):
        if not isinstance(other, int):
            raise Exception()
        if (other & other + 1) != 0:
            raise Exception() # <other> is not 2^n-1
        
        q = self // (other + 1)
        if q.lb == q.ub:
            return Interval(self.lb & other, self.ub & other)
        else:
            return Interval(0, other)
    
    def limb_and(self, index, other):
        if not isinstance(other, int):
            raise Exception()
        if (other & other + 1) != 0:
            raise Exception() # <other> is not 2^n-1
        
        other = (other << (32*index)) + 2**(32*index) - 1
        q = self // (other + 1)
        return Interval(self.lb & other, self.ub & other)
    
    def nlimbs(self):
        return (self.ub.bit_length() + 31) // 32
    
    def contains(self, other):
        if isinstance(other, int):
            return self.lb <= other and self.ub >= other
        elif isinstance(other, Interval):
            return self.lb <= other.lb and self.ub >= other.ub
        else:
            raise Exception()
    
    def __getitem__(self, index):     
        # TODO refactoring
        if self.nlimbs() == 1 and index == 0:
            return self
        if index == self.nlimbs() - 1:
            len32 = self.ub.bit_length() % 32
            if len32 == 0:
                len32 = 32
            leftover = self.ub // 2**(self.ub.bit_length() - len32)

            return Interval(0, leftover)
        elif index >= self.nlimbs():
            return Interval(0, 0)
        else:
            return Interval(0, 2**32 - 1)
    
    def __setitem__(self, index, value):
        if index < self.nlimbs() - 1:
            return
        self.lb = 0
        if isinstance(value, int):
            self.ub = (value + 1) * 2**(32*index) - 1
        elif isinstance(value, Interval):
            self.ub = (value.ub + 1) * 2**(32*index) - 1
        else:
            raise Exception()  

    def __repr__(self):
        if Interval.USEHEX:
            r = f"[{self.lb:x}, {self.ub:032x}]"
        else:
            r = f"[{self.lb}, {self.ub}]"
        r += f"\n{self.nlimbs()} Limbs: {{\n"
        
        for i in range(self.nlimbs()):
            if Interval.USEHEX:
                r += f"\t[{self[i].lb:x}, {self[i].ub:08x}],\n"
            else:
                r += f"\t[{self[i].lb}, {self[i].ub}],\n"
        r += "}"
        return r

class Verifier:
    zero = Interval(0, 0)
    one = Interval(1, 1)

    def __init__(self, input_ub, output_ub):
        self.input = Interval(0, input_ub)
        self.required = Interval(0, output_ub)
        self.output = Interval(0, 0)
    
    def validate(self):
        return self.required.contains(self.output)

    def umaal(rdlow, rdhigh, rn, rm):
        res = rn * rm + rdlow + rdhigh
        rdlow = res[0]
        rdhigh = res[1]
        return (rdlow, rdhigh)

    def umull(rn, rm):
        res = rn * rm
        rdlow = res[0]
        rdhigh = res[1]
        return (rdlow, rdhigh)

    def adds(a, b):
        r = a + b
        return r[0], r[1]

    def adcs(a, b, c):
        r = a + b + c
        return r[0], r[1]
    

    # Each of the following methods mirror the logic of the respective m4generator function,
    # but all operations are done over intervals instead of integers
    # Only the necessary parameters are passed
    # Results are stored directly in self.output to be verified later

    def modred_pmp_standard(self, c, nlimbs, lgap, rgap):
        t0 = Interval(0, 0)
        k = c
        mask = 2**rgap-1

        t1 = Interval(0, 0)
        for i in range(0, nlimbs):
            m = self.input[i + nlimbs] if lgap == 0 else (self.input[i + nlimbs] << lgap) + (self.input[i+nlimbs-1] >> rgap)
            t = self.input[i]
            if lgap > 0 and i == nlimbs - 1:
                t &= mask
            t, t0 = Verifier.umaal(t, t0, m, k)
            if lgap > 0 and i == nlimbs - 1:
                t0 = (t0 << lgap) + (t >> rgap)
                t &= mask
        
        t0 *= k
        self.output[0], t1 = Verifier.umaal(self.output[0], t1, Verifier.one, t0)
        for i in range(1, nlimbs - 1):
            self.output[i], t1 = Verifier.umaal(self.output[i], t1, Verifier.zero, Verifier.zero)
        if lgap > 0:
            self.output[nlimbs-1], t1 = Verifier.umaal(self.output[nlimbs-1], t1, Verifier.zero, Verifier.zero)
            t1 = self.output[nlimbs-1] >> rgap
            self.output[nlimbs-1] &= mask
        else:
            self.output[nlimbs-1], t1 = Verifier.umaal(self.output[nlimbs-1], t1, Verifier.zero, Verifier.zero)
        t1 *= k
        self.output[0] += t1

    
    def modred_pmp_smaller_lastlimb(self, n, c, shr, shl, in_limbs):
        if n % 32 > 16:
            rH = Interval(0, 0)
            cc = Interval(0, 0)
            loop_range = in_limbs - 1
        else:
            rH = Interval(0, 0)
            rT = Interval(0, 0)
            cc = Interval(0, 0)
            loop_range = in_limbs - 2

        rH = self.input[loop_range]
        rH, cc = Verifier.umaal(rH, cc, self.input[loop_range + in_limbs], c << shl)

        if n % 32 > 16:
            cc = ((cc << shl) + rH >> shr) * c
            rH &= (1 << shr) - 1
        else:
            rT = self.input[in_limbs - 1]
            rT, cc = Verifier.umaal(rT, cc, self.input[2 * in_limbs - 1], c << shl)
            cc = ((cc << shl) + rT >> shr) * c
            rT &= (1 << shr) - 1

        for i in range(loop_range):
            self.output[i], cc = Verifier.umaal(self.input[i], cc, self.input[in_limbs + i], c << shl)

        if n % 32 > 16:
            self.output[in_limbs - 1] = rH + cc
        else:
            self.output[in_limbs - 2], cc = Verifier.umaal(rH, cc, Verifier.zero, Verifier.zero)
            self.output[in_limbs - 1] = rT + cc


    # TODO
    def modred_pmp_full_lastlimb(self):
        pass