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

import re

montyprimes = {
    "C448": "2**448-2**224-1",
    "C25519": "2**255-19",
    "MFP4": "3*67*(2**246)-1\n    if WL==64:\n        base=52",
    "MFP7": "2**145*(3**9)*(59**3)*(311**3)*(317**3)*(503**3)-1\n    if WL==64:\n        base=52",
    "MFP248": "5 * 2**248 - 1",
    "MFP376": "65 * 2**376 - 1",
    "MFP500": "27 * 2**500 - 1",
    "MFP1973": "0x34e29e286b95d98c33a6a86587407437252c9e49355147ffffffffffffffffff\n\tif WL==64:\n\t\tbase=52",
    "MFP47441": "0x3df6eeeab0871a2c6ae604a45d10ad665bc2e0a90aeb751c722f669356ea4684c6174c1ffffffffffffffffffffffff",
    "MFP318233": "0x255946a8869bc68c15b0036936e79202bdbe6326507d01fe3ac5904a0dea65faf0a29a781974ce994c68ada6e1ffffffffffffffffffffffffffffffffffff",
    "NIST256": "2**256-2**224+2**192+2**96-1",
    "NIST521": "2**521-1",
    "PM266": "2**266-3",
    "PM512": "2**512-569\n    if WL==64 :\n        base=58",
    "PM225": "2**225-49",
}
pseudoprimes = {
    "C25519": "2**255-19",
    "NIST521": "2**521-1",
    "PM266": "2**266-3",
    "PM225": "2**225-49",
}

replacements = {
    '    str+="\\tres=modfsb(a);\\n"\n': '    str+="\\tres=modfsb{}(a);\\n".format(DECOR)\n',
    '    subprocess.call(cline, shell=True)\n': '    subprocess.call(cline, shell=True, stderr=subprocess.DEVNULL)\n',
    'subprocess.call("rm time.c", shell=True)\n': 'subprocess.call("rm -f time.c", shell=True)\n',
}

for file_name in ["monty.py", "pseudo.py"]:
    with open(file_name, "r") as file:
        lines = file.readlines()

    with open(file_name, "w") as file:
        embedded_fixed = False
        decoration_fixed = False
        tobedeleted = []
        for line in lines:
            if line in replacements:
                line = replacements[line]

            # Matches the final line of the script, "sys.exit(base)", to replace it with sys.exit(0)
            re_sys_exit = r"sys\.exit\((.*)\)"
            re_sys_exit_res = re.search(re_sys_exit, line)

            if re_sys_exit_res:
                if re_sys_exit_res.group(1) == "base":
                    line = re.sub(re_sys_exit, "sys.exit(0)", line)
            elif line[0:10] == "if prime==":
                i = 11
                currentPrime = ""
                while line[i] != '"':
                    currentPrime += line[i]
                    i += 1
                if file_name == "monty.py":
                    for primename in montyprimes:
                        if currentPrime == primename:
                            tobedeleted.append(primename)
                elif file_name == "pseudo.py":
                    for primename in pseudoprimes:
                        if currentPrime == primename:
                            tobedeleted.append(primename)
            elif line == "### End of user editable area\n":
                if file_name == "monty.py":
                    for primename in tobedeleted:
                        del montyprimes[primename]
                    for remprime in montyprimes:
                        file.write(
                            f"""if prime=="{remprime}":
    p={montyprimes[remprime]}

"""
                        )
                elif file_name == "pseudo.py":
                    for primename in tobedeleted:
                        del pseudoprimes[primename]
                    for remprime in pseudoprimes:
                        file.write(
                            f"""if prime=="{remprime}":
    p={pseudoprimes[remprime]}

"""
                        )

            if 'print("\\n//Command line' in line:
                continue
            line = line.replace("-march=native", "")
            line = line.replace("-mtune=native", "")
            if not embedded_fixed and line.startswith("embedded=False"):
                line = line.replace("embedded=False", "embedded=True ")
                embedded_fixed = True
            elif not decoration_fixed and line.startswith("decoration=False"):
                line = line.replace("decoration=False", "decoration=True")
                decoration_fixed = True
            file.write(line)
