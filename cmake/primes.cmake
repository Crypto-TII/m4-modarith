option(USE_C25519 "Generate code for C25519 = 2^255 - 19" ON)
option(USE_C448 "Generate code for C448 = 2^448 - 2^224 - 1" ON)
option(USE_C41417 "Generate code C41417 = 2^414 - 17" ON)
option(USE_PM225 "Generate code PM225 = 2^225 - 49" ON)
option(USE_PM266 "Generate code for PM266 = 2^266 - 3" ON)
option(USE_PM512 "Generate code for PM512 = 2^512 - 569" ON)
option(USE_PM383 "Generate code PM383 = 2^383 - 187" ON)
option(USE_PM336 "Generate code PM336 = 2^336 - 3" ON)
option(USE_NIST521 "Generate code for NIST521 = 2^521 - 1" ON)
option(USE_NIST256 "Generate code for NIST256 = 2^256 - 2^224 + 2^192 + 2^96 - 1" ON)
option(USE_SECP256K1 "Generate code SECP256K1 = 2^256 - 2^32 - 977" ON)
option(USE_MFP248 "Generate code MFP248 = 5*2^248 - 1" ON)
option(USE_MFP376 "Generate code MFP376 = 65*2^376 - 1" ON)
option(USE_MFP500 "Generate code MFP500 = 27*2^500 - 1" ON)
option(USE_MFP47441 "Generate code for MFP47441 = 0x3df6eeeab0871a2c6ae604a45d10ad665bc2e0a90aeb751c722f669356ea4684c6174c1ffffffffffffffffffffffff" ON)
# legacy primes
option(USE_MFP4 "Generate code for MFP4 = 2^246*3*67 - 1" OFF)
option(USE_MFP7 "Generate code for MFP7 = 2^145*3^9*59^3*311^3*317^3*503^3 - 1" OFF)
option(USE_MFP1973 "Generate code for MFP1973 = 0x34e29e286b95d98c33a6a86587407437252c9e49355147ffffffffffffffffff" OFF)
option(USE_MFP318233 "Generate code for MFP47441 = 0x255946a8869bc68c15b0036936e79202bdbe6326507d01fe3ac5904a0dea65faf0a29a781974ce994c68ada6e1ffffffffffffffffffffffffffffffffffff" OFF)
# only for testing purposes
option(USE_PMLIST "Generate code for test only PMPs" OFF)
option(USE_MONTLIST "Generate code for test only general primes" OFF)

# List of new pseudo-Mersenne primes
# Usually the whole list does not fit into device memory, uncomment desired primes
set(PMLIST
    # "2**61-1"
    # "2**225-49"
    # "2**226-5"
    # "2**227-405"
    # "2**228-93"
    # "2**229-91"
    # "2**230-27"
    # "2**231-165"
    # "2**232-567"
    # "2**233-3"
    # "2**234-83"
    # "2**235-15"
    
    # "2**236-209"
    # "2**237-181"
    # "2**238-161"
    # "2**239-87"
    # "2**240-467"
    # "2**241-39"
    # "2**242-63"
    # "2**243-9"
    # "2**244-189"
    # "2**245-163"
    # "2**246-107"

    # "2**247-81"
    # "2**248-237"
    # "2**249-75"
    # "2**250-207"
    # "2**251-9"
    # "2**252-129"
    # "2**253-273"
    # "2**254-245"
    # "2**255-19"
    # "2**256-189"
    # "2**287-115"
    # "2**288-167"

    # "2**319-795"
    # "2**320-197"
    # "2**351-61"
    # "2**352-657"
    # "2**383-31"
    # "2**384-317"
    # "2**415-45"
    # "2**416-435"
    # "2**447-325"
    # "2**448-203"

    # "2**479-537"
    # "2**480-47"
    # "2**511-187"
    # "2**543-157"
    # "2**544-759"
    # "2**272-237"
    # "2**304-75"
    # "2**368-315"
    # "2**400-593"
    # "2**432-299"
    
    # "2**464-437"
    # "2**496-257"
    # "2**528-65"
    # "2**257-93"
    # "2**289-493"
    # "2**321-9"
    # "2**353-139"
    # "2**385-265"
    # "2**417-1029"
    # "2**449-241"
    
    # "2**481-273"
    # "2**513-445"
    # "2**544-759"
    # "2**576-789"
    # "2**608-527"
    # "2**640-305"
    # "2**672-399"
    # "2**704-245"
    # "2**736-509"
    
    # "2**768-825"
    # "2**800-105"
    # "2**832-143"
    # "2**864-243"
    # "2**896-213"
    # "2**928-645"
    # "2**960-167"
    # "2**992-1779"
    # "2**1024-105"
    
    # "2**1056-725"
    # "2**1088-89"
    # "2**1120-2555"
    # "2**1152-927"
    # "2**1184-107"
    # "2**1216-563"
    # "2**1248-635"
    
    # "2**1280-1175"
    # "2**1312-509"
    # "2**1344-1175"
    # "2**1376-929"
    # "2**1408-413"
    # "2**1440-857"
    # "2**1472-5309"
    
    # "2**1504-1019"
    # "2**1536-3453"
    # "2**1568-1137"
    # "2**1600-2273"
    # "2**1632-605"
    # "2**1664-1233"
    # "2**1696-1113"
    
    # "2**1728-1115"
    # "2**1760-2123"
    # "2**1792-963"
    # "2**1824-6723"
    # "2**1856-1767"
    # "2**1888-129"
    
    # "2**1920-1503"
    # "2**1952-3479"
    # "2**1984-815"
    # "2**2016-5133"
    # "2**2048-1557"
)
    
# Test primes not written in special form, Montgomery reduction will always be used
set(MONTLIST
    "3**421+248"
    "2**246*3*67-1"
    "17*2**201+49*3**176+11**89+385"
    "0xb145071476c44705cbfce5a54fd1830aefd00cf846cba1c15a85ce51b0766efa9cc5"
    "0xa9e28143061e8e6222e0db977f9bbc5f9e514810d227a72be884890fe347a4052d73df8a9733c5ef45eda6c42b21eef7"
    "0x12242898909cc858c67db9c9c5849ea577483d26a6c9ea415afdac5341750d464d9f71b929661e6f8d58393f442d2d68b37773f0ad076f73466509c16a65"
    "0x17976392dd985a7007b4b3859f4993c9cd44d8145380d1fb92ada902332486735ce87552fdcbcee54e5329382950eac97d686d66465e39bc6cc6a40e50b44fbb6c5be80886a72a324d270bdbf"
    "0x10f7ba830589efca230d79319f5a70e6cb99339f688a852e64912c3c27ec189a9cd469ef6410994dd359695abb5aa0c169e7066a9eeed20dec4bdb3f6f73688ad3574411f87f5cf8cfa9e6b034915937c9f056a3fcfb46ff172473f8b"
    "0xed2ba1e801d3d0fb410ba8b8f7fb585eed08bf9af3e5b03e5494cfa92bb73fb98d8b5c05c276efcee55a1d55f9be5811eb6eec19bfc42b7479b80d9903be33465f58043b0298a935c96ff4be7026e315628a816449cb04998199d738c4725fb0eb967f77047fc2d53abbd3a73e2fffa00311"
    "0x1d6fcfce0755a893f0123f9737bbe0f7fcda5ba61e491540a81052a23ccde4d0ebefcbe7a201cfb90a738488565578984e9d139d652887f76ae5294a2456ea999bfb59caed8fcc487e459d8eb50ec69281a1651d7c85d33f0afad261f45535f60eefba6892ce26a8374a37abd10b715e88e83c1e16881c8e324d7aa6681"
)

message(STATUS "PMLIST: ${PMLIST}")
message(STATUS "MONTLIST: ${MONTLIST}")

if(USE_C25519)
    list(APPEND PRIMES_PSEUDO_MONTY C25519)
    list(APPEND PRIMES_PSEUDO_MONTY_REDUCTION pmp_asm)
    list(APPEND PRIMES_CUSTOM_PSEUDO C25519)
    list(APPEND PRIMES_CUSTOM_PSEUDO_REDUCTION pmp_asm)
endif()

if(USE_PM266)
    list(APPEND PRIMES_PSEUDO_MONTY PM266)

    list(APPEND PRIMES_PSEUDO_MONTY_REDUCTION pmp_asm)
    # list(APPEND PRIMES_PSEUDO_MONTY_REDUCTION pmp_c)
endif()

if(USE_PM512)
    list(APPEND PRIMES_PSEUDO_MONTY PM512)
    list(APPEND PRIMES_PSEUDO_MONTY_REDUCTION pmp_asm)
endif()

if(USE_NIST521)
    list(APPEND PRIMES_PSEUDO_MONTY NIST521)

    list(APPEND PRIMES_PSEUDO_MONTY_REDUCTION pmp_asm)
    # list(APPEND PRIMES_PSEUDO_MONTY_REDUCTION pmp_c)
endif()

if(USE_MFP4)
    list(APPEND PRIMES_MONTY MFP4)
    list(APPEND PRIMES_CUSTOM_MONTY MFP4)
endif()

if(USE_MFP7)
    list(APPEND PRIMES_MONTY MFP7)
    list(APPEND PRIMES_CUSTOM_MONTY MFP7)
endif()

if(USE_MFP1973)
    list(APPEND PRIMES_MONTY MFP1973)
endif()

if(USE_NIST256)
    list(APPEND PRIMES_MONTY NIST256)
endif()

if(USE_C448)
    list(APPEND PRIMES_MONTY C448)
    list(APPEND PRIMES_CUSTOM_PSEUDO C448)
    list(APPEND PRIMES_CUSTOM_PSEUDO_REDUCTION pmp_c)
endif()

if(USE_MFP47441)
    list(APPEND PRIMES_MONTY MFP47441)
endif()

if(USE_MFP318233)
    list(APPEND PRIMES_MONTY MFP318233)
endif()

if(USE_MFP248)
    list(APPEND PRIMES_MONTY MFP248)
    list(APPEND PRIMES_CUSTOM_MONTY MFP248)
endif()

if(USE_MFP376)
    list(APPEND PRIMES_MONTY MFP376)
endif()

if(USE_MFP500)
    list(APPEND PRIMES_MONTY MFP500)
endif()

if(USE_PM383)
    list(APPEND PRIMES_PSEUDO_MONTY PM383)
    list(APPEND PRIMES_PSEUDO_MONTY_REDUCTION pmp_asm)
endif()

if(USE_C41417)
    list(APPEND PRIMES_PSEUDO_MONTY C41417)
    list(APPEND PRIMES_PSEUDO_MONTY_REDUCTION pmp_asm)
endif()

if(USE_SECP256K1)
    list(APPEND PRIMES_MONTY SECP256K1)
endif()

if(USE_PM336)
    list(APPEND PRIMES_PSEUDO_MONTY PM336)
    list(APPEND PRIMES_PSEUDO_MONTY_REDUCTION pmp_asm)
endif()

if(USE_PM225)
    list(APPEND PRIMES_PSEUDO_MONTY PM225)
    list(APPEND PRIMES_PSEUDO_MONTY_REDUCTION pmp_asm)
endif()

if(USE_PMLIST)
    foreach(PRIME IN LISTS PMLIST)
        list(APPEND PRIMES_M4_EXTRA ${PRIME})
        list(APPEND PRIMES_M4_EXTRA_REDUCTION pmp_asm)
    endforeach()
endif()

if(USE_MONTLIST)
    foreach(PRIME IN LISTS MONTLIST)
        list(APPEND PRIMES_M4_EXTRA ${PRIME})
        list(APPEND PRIMES_M4_EXTRA_REDUCTION mont)
    endforeach()
endif()