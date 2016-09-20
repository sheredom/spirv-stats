// This is free and unencumbered software released into the public domain.
//
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
//
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
//
// For more information, please refer to <http://unlicense.org/>

#ifdef _MSC_VER
// Disable warning about not inlining inline functions
#pragma warning(disable : 4710)
// Disable warning about inlining non-inline functions
#pragma warning(disable : 4711)
#pragma warning(push, 1)

// Disable warning in the CRT
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <map>
#include <vector>

#if defined(_MSC_VER)
#undef _CRT_SECURE_NO_WARNINGS
#pragma warning(pop)
#endif

const std::map<uint32_t, const char *> opcodes = {
    {0, "OpNop"},
    {1, "OpUndef"},
    {2, "OpSourceContinued"},
    {3, "OpSource"},
    {4, "OpSourceExtension"},
    {5, "OpName"},
    {6, "OpMemberName"},
    {7, "OpString"},
    {8, "OpLine"},
    {10, "OpExtension"},
    {11, "OpExtInstImport"},
    {12, "OpExtInst"},
    {14, "OpMemoryModel"},
    {15, "OpEntryPoint"},
    {16, "OpExecutionMode"},
    {17, "OpCapability"},
    {19, "OpTypeVoid"},
    {20, "OpTypeBool"},
    {21, "OpTypeInt"},
    {22, "OpTypeFloat"},
    {23, "OpTypeVector"},
    {24, "OpTypeMatrix"},
    {25, "OpTypeImage"},
    {26, "OpTypeSampler"},
    {27, "OpTypeSampledImage"},
    {28, "OpTypeArray"},
    {29, "OpTypeRuntimeArray"},
    {30, "OpTypeStruct"},
    {31, "OpTypeOpaque"},
    {32, "OpTypePointer"},
    {33, "OpTypeFunction"},
    {34, "OpTypeEvent"},
    {35, "OpTypeDeviceEvent"},
    {36, "OpTypeReserveId"},
    {37, "OpTypeQueue"},
    {38, "OpTypePipe"},
    {39, "OpTypeForwardPointer"},
    {41, "OpConstantTrue"},
    {42, "OpConstantFalse"},
    {43, "OpConstant"},
    {44, "OpConstantComposite"},
    {45, "OpConstantSampler"},
    {46, "OpConstantNull"},
    {48, "OpSpecConstantTrue"},
    {49, "OpSpecConstantFalse"},
    {50, "OpSpecConstant"},
    {51, "OpSpecConstantComposite"},
    {52, "OpSpecConstantOp"},
    {54, "OpFunction"},
    {55, "OpFunctionParameter"},
    {56, "OpFunctionEnd"},
    {57, "OpFunctionCall"},
    {59, "OpVariable"},
    {60, "OpImageTexelPointer"},
    {61, "OpLoad"},
    {62, "OpStore"},
    {63, "OpCopyMemory"},
    {64, "OpCopyMemorySized"},
    {65, "OpAccessChain"},
    {66, "OpInBoundsAccessChain"},
    {67, "OpPtrAccessChain"},
    {68, "OpArrayLength"},
    {69, "OpGenericPtrMemSemantics"},
    {70, "OpInBoundsPtrAccessChain"},
    {71, "OpDecorate"},
    {72, "OpMemberDecorate"},
    {73, "OpDecorationGroup"},
    {74, "OpGroupDecorate"},
    {75, "OpGroupMemberDecorate"},
    {77, "OpVectorExtractDynamic"},
    {78, "OpVectorInsertDynamic"},
    {79, "OpVectorShuffle"},
    {80, "OpCompositeConstruct"},
    {81, "OpCompositeExtract"},
    {82, "OpCompositeInsert"},
    {83, "OpCopyObject"},
    {84, "OpTranspose"},
    {86, "OpSampledImage"},
    {87, "OpImageSampleImplicitLod"},
    {88, "OpImageSampleExplicitLod"},
    {89, "OpImageSampleDrefImplicitLod"},
    {90, "OpImageSampleDrefExplicitLod"},
    {91, "OpImageSampleProjImplicitLod"},
    {92, "OpImageSampleProjExplicitLod"},
    {93, "OpImageSampleProjDrefImplicitLod"},
    {94, "OpImageSampleProjDrefExplicitLod"},
    {95, "OpImageFetch"},
    {96, "OpImageGather"},
    {97, "OpImageDrefGather"},
    {98, "OpImageRead"},
    {99, "OpImageWrite"},
    {100, "OpImage"},
    {101, "OpImageQueryFormat"},
    {102, "OpImageQueryOrder"},
    {103, "OpImageQuerySizeLod"},
    {104, "OpImageQuerySize"},
    {105, "OpImageQueryLod"},
    {106, "OpImageQueryLevels"},
    {107, "OpImageQuerySamples"},
    {109, "OpConvertFToU"},
    {110, "OpConvertFToS"},
    {111, "OpConvertSToF"},
    {112, "OpConvertUToF"},
    {113, "OpUConvert"},
    {114, "OpSConvert"},
    {115, "OpFConvert"},
    {116, "OpQuantizeToF16"},
    {117, "OpConvertPtrToU"},
    {118, "OpSatConvertSToU"},
    {119, "OpSatConvertUToS"},
    {120, "OpConvertUToPtr"},
    {121, "OpPtrCastToGeneric"},
    {122, "OpGenericCastToPtr"},
    {123, "OpGenericCastToPtrExplicit"},
    {124, "OpBitcast"},
    {126, "OpSNegate"},
    {127, "OpFNegate"},
    {128, "OpIAdd"},
    {129, "OpFAdd"},
    {130, "OpISub"},
    {131, "OpFSub"},
    {132, "OpIMul"},
    {133, "OpFMul"},
    {134, "OpUDiv"},
    {135, "OpSDiv"},
    {136, "OpFDiv"},
    {137, "OpUMod"},
    {138, "OpSRem"},
    {139, "OpSMod"},
    {140, "OpFRem"},
    {141, "OpFMod"},
    {142, "OpVectorTimesScalar"},
    {143, "OpMatrixTimesScalar"},
    {144, "OpVectorTimesMatrix"},
    {145, "OpMatrixTimesVector"},
    {146, "OpMatrixTimesMatrix"},
    {147, "OpOuterProduct"},
    {148, "OpDot"},
    {149, "OpIAddCarry"},
    {150, "OpISubBorrow"},
    {151, "OpUMulExtended"},
    {152, "OpSMulExtended"},
    {154, "OpAny"},
    {155, "OpAll"},
    {156, "OpIsNan"},
    {157, "OpIsInf"},
    {158, "OpIsFinite"},
    {159, "OpIsNormal"},
    {160, "OpSignBitSet"},
    {161, "OpLessOrGreater"},
    {162, "OpOrdered"},
    {163, "OpUnordered"},
    {164, "OpLogicalEqual"},
    {165, "OpLogicalNotEqual"},
    {166, "OpLogicalOr"},
    {167, "OpLogicalAnd"},
    {168, "OpLogicalNot"},
    {169, "OpSelect"},
    {170, "OpIEqual"},
    {171, "OpINotEqual"},
    {172, "OpUGreaterThan"},
    {173, "OpSGreaterThan"},
    {174, "OpUGreaterThanEqual"},
    {175, "OpSGreaterThanEqual"},
    {176, "OpULessThan"},
    {177, "OpSLessThan"},
    {178, "OpULessThanEqual"},
    {179, "OpSLessThanEqual"},
    {180, "OpFOrdEqual"},
    {181, "OpFUnordEqual"},
    {182, "OpFOrdNotEqual"},
    {183, "OpFUnordNotEqual"},
    {184, "OpFOrdLessThan"},
    {185, "OpFUnordLessThan"},
    {186, "OpFOrdGreaterThan"},
    {187, "OpFUnordGreaterThan"},
    {188, "OpFOrdLessThanEqual"},
    {189, "OpFUnordLessThanEqual"},
    {190, "OpFOrdGreaterThanEqual"},
    {191, "OpFUnordGreaterThanEqual"},
    {194, "OpShiftRightLogical"},
    {195, "OpShiftRightArithmetic"},
    {196, "OpShiftLeftLogical"},
    {197, "OpBitwiseOr"},
    {198, "OpBitwiseXor"},
    {199, "OpBitwiseAnd"},
    {200, "OpNot"},
    {201, "OpBitFieldInsert"},
    {202, "OpBitFieldSExtract"},
    {203, "OpBitFieldUExtract"},
    {204, "OpBitReverse"},
    {205, "OpBitCount"},
    {207, "OpDPdx"},
    {208, "OpDPdy"},
    {209, "OpFwidth"},
    {210, "OpDPdxFine"},
    {211, "OpDPdyFine"},
    {212, "OpFwidthFine"},
    {213, "OpDPdxCoarse"},
    {214, "OpDPdyCoarse"},
    {215, "OpFwidthCoarse"},
    {218, "OpEmitVertex"},
    {219, "OpEndPrimitive"},
    {220, "OpEmitStreamVertex"},
    {221, "OpEndStreamPrimitive"},
    {224, "OpControlBarrier"},
    {225, "OpMemoryBarrier"},
    {227, "OpAtomicLoad"},
    {228, "OpAtomicStore"},
    {229, "OpAtomicExchange"},
    {230, "OpAtomicCompareExchange"},
    {231, "OpAtomicCompareExchangeWeak"},
    {232, "OpAtomicIIncrement"},
    {233, "OpAtomicIDecrement"},
    {234, "OpAtomicIAdd"},
    {235, "OpAtomicISub"},
    {236, "OpAtomicSMin"},
    {237, "OpAtomicUMin"},
    {238, "OpAtomicSMax"},
    {239, "OpAtomicUMax"},
    {240, "OpAtomicAnd"},
    {241, "OpAtomicOr"},
    {242, "OpAtomicXor"},
    {245, "OpPhi"},
    {246, "OpLoopMerge"},
    {247, "OpSelectionMerge"},
    {248, "OpLabel"},
    {249, "OpBranch"},
    {250, "OpBranchConditional"},
    {251, "OpSwitch"},
    {252, "OpKill"},
    {253, "OpReturn"},
    {254, "OpReturnValue"},
    {255, "OpUnreachable"},
    {256, "OpLifetimeStart"},
    {257, "OpLifetimeStop"},
    {259, "OpGroupAsyncCopy"},
    {260, "OpGroupWaitEvents"},
    {261, "OpGroupAll"},
    {262, "OpGroupAny"},
    {263, "OpGroupBroadcast"},
    {264, "OpGroupIAdd"},
    {265, "OpGroupFAdd"},
    {266, "OpGroupFMin"},
    {267, "OpGroupUMin"},
    {268, "OpGroupSMin"},
    {269, "OpGroupFMax"},
    {270, "OpGroupUMax"},
    {271, "OpGroupSMax"},
    {274, "OpReadPipe"},
    {275, "OpWritePipe"},
    {276, "OpReservedReadPipe"},
    {277, "OpReservedWritePipe"},
    {278, "OpReserveReadPipePackets"},
    {279, "OpReserveWritePipePackets"},
    {280, "OpCommitReadPipe"},
    {281, "OpCommitWritePipe"},
    {282, "OpIsValidReserveId"},
    {283, "OpGetNumPipePackets"},
    {284, "OpGetMaxPipePackets"},
    {285, "OpGroupReserveReadPipePackets"},
    {286, "OpGroupReserveWritePipePackets"},
    {287, "OpGroupCommitReadPipe"},
    {288, "OpGroupCommitWritePipe"},
    {291, "OpEnqueueMarker"},
    {292, "OpEnqueueKernel"},
    {293, "OpGetKernelNDrangeSubGroupCount"},
    {294, "OpGetKernelNDrangeMaxSubGroupSize"},
    {295, "OpGetKernelWorkGroupSize"},
    {296, "OpGetKernelPreferredWorkGroupSizeMultiple"},
    {297, "OpRetainEvent"},
    {298, "OpReleaseEvent"},
    {299, "OpCreateUserEvent"},
    {300, "OpIsValidEvent"},
    {301, "OpSetUserEventStatus"},
    {302, "OpCaptureEventProfilingInfo"},
    {303, "OpGetDefaultQueue"},
    {304, "OpBuildNDRange"},
    {305, "OpImageSparseSampleImplicitLod"},
    {306, "OpImageSparseSampleExplicitLod"},
    {307, "OpImageSparseSampleDrefImplicitLod"},
    {308, "OpImageSparseSampleDrefExplicitLod"},
    {309, "OpImageSparseSampleProjImplicitLod"},
    {310, "OpImageSparseSampleProjExplicitLod"},
    {311, "OpImageSparseSampleProjDrefImplicitLod"},
    {312, "OpImageSparseSampleProjDrefExplicitLod"},
    {313, "OpImageSparseFetch"},
    {314, "OpImageSparseGather"},
    {315, "OpImageSparseDrefGather"},
    {316, "OpImageSparseTexelsResident"},
    {317, "OpNoLine"},
    {318, "OpAtomicFlagTestAndSet"},
    {319, "OpAtomicFlagClear"},
    {320, "OpImageSparseRead"},
    {4421, "OpSubgroupBallotKHR"},
    {4422, "OpSubgroupFirstInvocationKHR"}};

static const uint32_t magicNumber = 0x07230203u;
static const uint32_t reserveMagicNumber = 0x03022307u;
static const uint32_t numWordsInHeader = 5u;

int main(const int argc, const char *const argv[]) {
  std::map<uint32_t, std::pair<uint32_t, uint32_t>> hits;
  uint64_t totalHits = 0;
  uint64_t totalBytes = 0;

  for (int i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "rb");

    if (nullptr == file) {
      fprintf(stderr, "Error: couldn't open input file '%s' for reading!\n",
              argv[i]);
      return 1;
    }

    uint32_t header[numWordsInHeader];

    if (numWordsInHeader !=
        fread(header, sizeof(uint32_t), numWordsInHeader, file)) {
      fprintf(stderr, "Error: SPIR-V input file was too short to be valid!\n");
      return 1;
    }

    // the header is part of the total bytes we record
    totalBytes += sizeof(uint32_t) * numWordsInHeader;

    if ((magicNumber != header[0]) && (reserveMagicNumber != header[0])) {
      fprintf(
          stderr,
          "Error: magic number identifying file as SPIR-V was incorrect!\n");
      return 1;
    }

    const bool wrongEndian = reserveMagicNumber == header[0];

    uint32_t word;
    while (1 == fread(&word, sizeof(word), 1, file)) {
      if (wrongEndian) {
        word = (0x000000ffu & (word >> 24)) | (0x0000ff00u & (word >> 8)) |
               (0x00ff0000u & (word << 8)) | (0xff000000u & (word << 24));
      }
      const uint32_t wordCount = word >> 16;
      const uint32_t opcode = word & 0xFFFFu;

      hits[opcode].first++;
      hits[opcode].second += sizeof(uint32_t) * wordCount;

      totalHits++;
      totalBytes += sizeof(uint32_t) * wordCount;

      // skip the remaining words in the opcode
      fseek(file, static_cast<long>(sizeof(uint32_t) * (wordCount - 1)),
            SEEK_CUR);
    }

    fclose(file);
  }

  typedef std::pair<uint32_t, std::pair<uint32_t, uint32_t>> MapPair;

  std::vector<MapPair> hitsVector(
      hits.begin(), hits.end());

  std::sort(hitsVector.begin(), hitsVector.end(),
            [](MapPair a, MapPair b) { return a.second.first > b.second.first; });

  printf("Totals: %llu hits %llu bytes\n", totalHits, totalBytes);
  for (MapPair i : hitsVector) {
    printf("%30s = %6u hits (%5.2f%%) %6u bytes (%5.2f%%)\n",
           opcodes.at(i.first), i.second.first,
           static_cast<double>(i.second.first) / totalHits * 100.0,
           i.second.second,
           static_cast<double>(i.second.second) / totalBytes * 100.0);
  }
}
