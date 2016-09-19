# spirv-stats #

spirv-stats is a command line tool to take one or more SPIR-V modules, and output statistics on the composition of the module.

## Build ##

spirv-stats exists in one C++ file - spirv-stats.cpp. Build that with the compiler of your choice. Alternatively, there is a CMakeLists.txt provided within the repository that will build the command line tool for you.

## Run ##

An expected run of spirv-stats is something like the below:

```
Totals: 35 hits 564 bytes
               OpDecorate =      5 hits (14.29%) 80 bytes (14.18%)
            OpTypePointer =      4 hits (11.43%) 64 bytes (11.35%)
               OpVariable =      4 hits (11.43%) 64 bytes (11.35%)
                   OpLoad =      3 hits ( 8.57%) 48 bytes ( 8.51%)
             OpTypeVector =      2 hits ( 5.71%) 32 bytes ( 5.67%)
          OpExtInstImport =      1 hits ( 2.86%) 24 bytes ( 4.26%)
            OpMemoryModel =      1 hits ( 2.86%) 12 bytes ( 2.13%)
             OpEntryPoint =      1 hits ( 2.86%) 32 bytes ( 5.67%)
          OpExecutionMode =      1 hits ( 2.86%) 12 bytes ( 2.13%)
             OpCapability =      1 hits ( 2.86%)  8 bytes ( 1.42%)
               OpTypeVoid =      1 hits ( 2.86%)  8 bytes ( 1.42%)
              OpTypeFloat =      1 hits ( 2.86%) 12 bytes ( 2.13%)
              OpTypeImage =      1 hits ( 2.86%) 36 bytes ( 6.38%)
       OpTypeSampledImage =      1 hits ( 2.86%) 12 bytes ( 2.13%)
           OpTypeFunction =      1 hits ( 2.86%) 12 bytes ( 2.13%)
               OpFunction =      1 hits ( 2.86%) 20 bytes ( 3.55%)
            OpFunctionEnd =      1 hits ( 2.86%)  4 bytes ( 0.71%)
                  OpStore =      1 hits ( 2.86%) 12 bytes ( 2.13%)
 OpImageSampleImplicitLod =      1 hits ( 2.86%) 20 bytes ( 3.55%)
                   OpFMul =      1 hits ( 2.86%) 20 bytes ( 3.55%)
                  OpLabel =      1 hits ( 2.86%)  8 bytes ( 1.42%)
                 OpReturn =      1 hits ( 2.86%)  4 bytes ( 0.71%)
```

It first outputs the total number of opcodes found (hits) and the bytes that this SPIR-V module inhabits. Then, on a per opcode basis, it lists the opcodes found in the module, the number of times that opcode occurred (hits), and the number of bytes that that opcode takes up in the SPIR-V binary.

## License ##

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>
