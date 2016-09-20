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

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include <algorithm>
#include <map>
#include <vector>

#if defined(_MSC_VER)
#undef _CRT_SECURE_NO_WARNINGS
#pragma warning(pop)
#endif

static const uint32_t magicNumber = 0x07230203u;
static const uint32_t reserveMagicNumber = 0x03022307u;
static const uint32_t numWordsInHeader = 5u;

int main(const int argc, const char *const argv[]) {
  std::map<uint32_t, const char *> opcodes;
  opcodes[0] = "OpNop";
  opcodes[1] = "OpUndef";
  opcodes[2] = "OpSourceContinued";
  opcodes[3] = "OpSource";
  opcodes[4] = "OpSourceExtension";
  opcodes[5] = "OpName";
  opcodes[6] = "OpMemberName";
  opcodes[7] = "OpString";
  opcodes[8] = "OpLine";
  opcodes[10] = "OpExtension";
  opcodes[11] = "OpExtInstImport";
  opcodes[12] = "OpExtInst";
  opcodes[14] = "OpMemoryModel";
  opcodes[15] = "OpEntryPoint";
  opcodes[16] = "OpExecutionMode";
  opcodes[17] = "OpCapability";
  opcodes[19] = "OpTypeVoid";
  opcodes[20] = "OpTypeBool";
  opcodes[21] = "OpTypeInt";
  opcodes[22] = "OpTypeFloat";
  opcodes[23] = "OpTypeVector";
  opcodes[24] = "OpTypeMatrix";
  opcodes[25] = "OpTypeImage";
  opcodes[26] = "OpTypeSampler";
  opcodes[27] = "OpTypeSampledImage";
  opcodes[28] = "OpTypeArray";
  opcodes[29] = "OpTypeRuntimeArray";
  opcodes[30] = "OpTypeStruct";
  opcodes[31] = "OpTypeOpaque";
  opcodes[32] = "OpTypePointer";
  opcodes[33] = "OpTypeFunction";
  opcodes[34] = "OpTypeEvent";
  opcodes[35] = "OpTypeDeviceEvent";
  opcodes[36] = "OpTypeReserveId";
  opcodes[37] = "OpTypeQueue";
  opcodes[38] = "OpTypePipe";
  opcodes[39] = "OpTypeForwardPointer";
  opcodes[41] = "OpConstantTrue";
  opcodes[42] = "OpConstantFalse";
  opcodes[43] = "OpConstant";
  opcodes[44] = "OpConstantComposite";
  opcodes[45] = "OpConstantSampler";
  opcodes[46] = "OpConstantNull";
  opcodes[48] = "OpSpecConstantTrue";
  opcodes[49] = "OpSpecConstantFalse";
  opcodes[50] = "OpSpecConstant";
  opcodes[51] = "OpSpecConstantComposite";
  opcodes[52] = "OpSpecConstantOp";
  opcodes[54] = "OpFunction";
  opcodes[55] = "OpFunctionParameter";
  opcodes[56] = "OpFunctionEnd";
  opcodes[57] = "OpFunctionCall";
  opcodes[59] = "OpVariable";
  opcodes[60] = "OpImageTexelPointer";
  opcodes[61] = "OpLoad";
  opcodes[62] = "OpStore";
  opcodes[63] = "OpCopyMemory";
  opcodes[64] = "OpCopyMemorySized";
  opcodes[65] = "OpAccessChain";
  opcodes[66] = "OpInBoundsAccessChain";
  opcodes[67] = "OpPtrAccessChain";
  opcodes[68] = "OpArrayLength";
  opcodes[69] = "OpGenericPtrMemSemantics";
  opcodes[70] = "OpInBoundsPtrAccessChain";
  opcodes[71] = "OpDecorate";
  opcodes[72] = "OpMemberDecorate";
  opcodes[73] = "OpDecorationGroup";
  opcodes[74] = "OpGroupDecorate";
  opcodes[75] = "OpGroupMemberDecorate";
  opcodes[77] = "OpVectorExtractDynamic";
  opcodes[78] = "OpVectorInsertDynamic";
  opcodes[79] = "OpVectorShuffle";
  opcodes[80] = "OpCompositeConstruct";
  opcodes[81] = "OpCompositeExtract";
  opcodes[82] = "OpCompositeInsert";
  opcodes[83] = "OpCopyObject";
  opcodes[84] = "OpTranspose";
  opcodes[86] = "OpSampledImage";
  opcodes[87] = "OpImageSampleImplicitLod";
  opcodes[88] = "OpImageSampleExplicitLod";
  opcodes[89] = "OpImageSampleDrefImplicitLod";
  opcodes[90] = "OpImageSampleDrefExplicitLod";
  opcodes[91] = "OpImageSampleProjImplicitLod";
  opcodes[92] = "OpImageSampleProjExplicitLod";
  opcodes[93] = "OpImageSampleProjDrefImplicitLod";
  opcodes[94] = "OpImageSampleProjDrefExplicitLod";
  opcodes[95] = "OpImageFetch";
  opcodes[96] = "OpImageGather";
  opcodes[97] = "OpImageDrefGather";
  opcodes[98] = "OpImageRead";
  opcodes[99] = "OpImageWrite";
  opcodes[100] = "OpImage";
  opcodes[101] = "OpImageQueryFormat";
  opcodes[102] = "OpImageQueryOrder";
  opcodes[103] = "OpImageQuerySizeLod";
  opcodes[104] = "OpImageQuerySize";
  opcodes[105] = "OpImageQueryLod";
  opcodes[106] = "OpImageQueryLevels";
  opcodes[107] = "OpImageQuerySamples";
  opcodes[109] = "OpConvertFToU";
  opcodes[110] = "OpConvertFToS";
  opcodes[111] = "OpConvertSToF";
  opcodes[112] = "OpConvertUToF";
  opcodes[113] = "OpUConvert";
  opcodes[114] = "OpSConvert";
  opcodes[115] = "OpFConvert";
  opcodes[116] = "OpQuantizeToF16";
  opcodes[117] = "OpConvertPtrToU";
  opcodes[118] = "OpSatConvertSToU";
  opcodes[119] = "OpSatConvertUToS";
  opcodes[120] = "OpConvertUToPtr";
  opcodes[121] = "OpPtrCastToGeneric";
  opcodes[122] = "OpGenericCastToPtr";
  opcodes[123] = "OpGenericCastToPtrExplicit";
  opcodes[124] = "OpBitcast";
  opcodes[126] = "OpSNegate";
  opcodes[127] = "OpFNegate";
  opcodes[128] = "OpIAdd";
  opcodes[129] = "OpFAdd";
  opcodes[130] = "OpISub";
  opcodes[131] = "OpFSub";
  opcodes[132] = "OpIMul";
  opcodes[133] = "OpFMul";
  opcodes[134] = "OpUDiv";
  opcodes[135] = "OpSDiv";
  opcodes[136] = "OpFDiv";
  opcodes[137] = "OpUMod";
  opcodes[138] = "OpSRem";
  opcodes[139] = "OpSMod";
  opcodes[140] = "OpFRem";
  opcodes[141] = "OpFMod";
  opcodes[142] = "OpVectorTimesScalar";
  opcodes[143] = "OpMatrixTimesScalar";
  opcodes[144] = "OpVectorTimesMatrix";
  opcodes[145] = "OpMatrixTimesVector";
  opcodes[146] = "OpMatrixTimesMatrix";
  opcodes[147] = "OpOuterProduct";
  opcodes[148] = "OpDot";
  opcodes[149] = "OpIAddCarry";
  opcodes[150] = "OpISubBorrow";
  opcodes[151] = "OpUMulExtended";
  opcodes[152] = "OpSMulExtended";
  opcodes[154] = "OpAny";
  opcodes[155] = "OpAll";
  opcodes[156] = "OpIsNan";
  opcodes[157] = "OpIsInf";
  opcodes[158] = "OpIsFinite";
  opcodes[159] = "OpIsNormal";
  opcodes[160] = "OpSignBitSet";
  opcodes[161] = "OpLessOrGreater";
  opcodes[162] = "OpOrdered";
  opcodes[163] = "OpUnordered";
  opcodes[164] = "OpLogicalEqual";
  opcodes[165] = "OpLogicalNotEqual";
  opcodes[166] = "OpLogicalOr";
  opcodes[167] = "OpLogicalAnd";
  opcodes[168] = "OpLogicalNot";
  opcodes[169] = "OpSelect";
  opcodes[170] = "OpIEqual";
  opcodes[171] = "OpINotEqual";
  opcodes[172] = "OpUGreaterThan";
  opcodes[173] = "OpSGreaterThan";
  opcodes[174] = "OpUGreaterThanEqual";
  opcodes[175] = "OpSGreaterThanEqual";
  opcodes[176] = "OpULessThan";
  opcodes[177] = "OpSLessThan";
  opcodes[178] = "OpULessThanEqual";
  opcodes[179] = "OpSLessThanEqual";
  opcodes[180] = "OpFOrdEqual";
  opcodes[181] = "OpFUnordEqual";
  opcodes[182] = "OpFOrdNotEqual";
  opcodes[183] = "OpFUnordNotEqual";
  opcodes[184] = "OpFOrdLessThan";
  opcodes[185] = "OpFUnordLessThan";
  opcodes[186] = "OpFOrdGreaterThan";
  opcodes[187] = "OpFUnordGreaterThan";
  opcodes[188] = "OpFOrdLessThanEqual";
  opcodes[189] = "OpFUnordLessThanEqual";
  opcodes[190] = "OpFOrdGreaterThanEqual";
  opcodes[191] = "OpFUnordGreaterThanEqual";
  opcodes[194] = "OpShiftRightLogical";
  opcodes[195] = "OpShiftRightArithmetic";
  opcodes[196] = "OpShiftLeftLogical";
  opcodes[197] = "OpBitwiseOr";
  opcodes[198] = "OpBitwiseXor";
  opcodes[199] = "OpBitwiseAnd";
  opcodes[200] = "OpNot";
  opcodes[201] = "OpBitFieldInsert";
  opcodes[202] = "OpBitFieldSExtract";
  opcodes[203] = "OpBitFieldUExtract";
  opcodes[204] = "OpBitReverse";
  opcodes[205] = "OpBitCount";
  opcodes[207] = "OpDPdx";
  opcodes[208] = "OpDPdy";
  opcodes[209] = "OpFwidth";
  opcodes[210] = "OpDPdxFine";
  opcodes[211] = "OpDPdyFine";
  opcodes[212] = "OpFwidthFine";
  opcodes[213] = "OpDPdxCoarse";
  opcodes[214] = "OpDPdyCoarse";
  opcodes[215] = "OpFwidthCoarse";
  opcodes[218] = "OpEmitVertex";
  opcodes[219] = "OpEndPrimitive";
  opcodes[220] = "OpEmitStreamVertex";
  opcodes[221] = "OpEndStreamPrimitive";
  opcodes[224] = "OpControlBarrier";
  opcodes[225] = "OpMemoryBarrier";
  opcodes[227] = "OpAtomicLoad";
  opcodes[228] = "OpAtomicStore";
  opcodes[229] = "OpAtomicExchange";
  opcodes[230] = "OpAtomicCompareExchange";
  opcodes[231] = "OpAtomicCompareExchangeWeak";
  opcodes[232] = "OpAtomicIIncrement";
  opcodes[233] = "OpAtomicIDecrement";
  opcodes[234] = "OpAtomicIAdd";
  opcodes[235] = "OpAtomicISub";
  opcodes[236] = "OpAtomicSMin";
  opcodes[237] = "OpAtomicUMin";
  opcodes[238] = "OpAtomicSMax";
  opcodes[239] = "OpAtomicUMax";
  opcodes[240] = "OpAtomicAnd";
  opcodes[241] = "OpAtomicOr";
  opcodes[242] = "OpAtomicXor";
  opcodes[245] = "OpPhi";
  opcodes[246] = "OpLoopMerge";
  opcodes[247] = "OpSelectionMerge";
  opcodes[248] = "OpLabel";
  opcodes[249] = "OpBranch";
  opcodes[250] = "OpBranchConditional";
  opcodes[251] = "OpSwitch";
  opcodes[252] = "OpKill";
  opcodes[253] = "OpReturn";
  opcodes[254] = "OpReturnValue";
  opcodes[255] = "OpUnreachable";
  opcodes[256] = "OpLifetimeStart";
  opcodes[257] = "OpLifetimeStop";
  opcodes[259] = "OpGroupAsyncCopy";
  opcodes[260] = "OpGroupWaitEvents";
  opcodes[261] = "OpGroupAll";
  opcodes[262] = "OpGroupAny";
  opcodes[263] = "OpGroupBroadcast";
  opcodes[264] = "OpGroupIAdd";
  opcodes[265] = "OpGroupFAdd";
  opcodes[266] = "OpGroupFMin";
  opcodes[267] = "OpGroupUMin";
  opcodes[268] = "OpGroupSMin";
  opcodes[269] = "OpGroupFMax";
  opcodes[270] = "OpGroupUMax";
  opcodes[271] = "OpGroupSMax";
  opcodes[274] = "OpReadPipe";
  opcodes[275] = "OpWritePipe";
  opcodes[276] = "OpReservedReadPipe";
  opcodes[277] = "OpReservedWritePipe";
  opcodes[278] = "OpReserveReadPipePackets";
  opcodes[279] = "OpReserveWritePipePackets";
  opcodes[280] = "OpCommitReadPipe";
  opcodes[281] = "OpCommitWritePipe";
  opcodes[282] = "OpIsValidReserveId";
  opcodes[283] = "OpGetNumPipePackets";
  opcodes[284] = "OpGetMaxPipePackets";
  opcodes[285] = "OpGroupReserveReadPipePackets";
  opcodes[286] = "OpGroupReserveWritePipePackets";
  opcodes[287] = "OpGroupCommitReadPipe";
  opcodes[288] = "OpGroupCommitWritePipe";
  opcodes[291] = "OpEnqueueMarker";
  opcodes[292] = "OpEnqueueKernel";
  opcodes[293] = "OpGetKernelNDrangeSubGroupCount";
  opcodes[294] = "OpGetKernelNDrangeMaxSubGroupSize";
  opcodes[295] = "OpGetKernelWorkGroupSize";
  opcodes[296] = "OpGetKernelPreferredWorkGroupSizeMultiple";
  opcodes[297] = "OpRetainEvent";
  opcodes[298] = "OpReleaseEvent";
  opcodes[299] = "OpCreateUserEvent";
  opcodes[300] = "OpIsValidEvent";
  opcodes[301] = "OpSetUserEventStatus";
  opcodes[302] = "OpCaptureEventProfilingInfo";
  opcodes[303] = "OpGetDefaultQueue";
  opcodes[304] = "OpBuildNDRange";
  opcodes[305] = "OpImageSparseSampleImplicitLod";
  opcodes[306] = "OpImageSparseSampleExplicitLod";
  opcodes[307] = "OpImageSparseSampleDrefImplicitLod";
  opcodes[308] = "OpImageSparseSampleDrefExplicitLod";
  opcodes[309] = "OpImageSparseSampleProjImplicitLod";
  opcodes[310] = "OpImageSparseSampleProjExplicitLod";
  opcodes[311] = "OpImageSparseSampleProjDrefImplicitLod";
  opcodes[312] = "OpImageSparseSampleProjDrefExplicitLod";
  opcodes[313] = "OpImageSparseFetch";
  opcodes[314] = "OpImageSparseGather";
  opcodes[315] = "OpImageSparseDrefGather";
  opcodes[316] = "OpImageSparseTexelsResident";
  opcodes[317] = "OpNoLine";
  opcodes[318] = "OpAtomicFlagTestAndSet";
  opcodes[319] = "OpAtomicFlagClear";
  opcodes[320] = "OpImageSparseRead";
  opcodes[4421] = "OpSubgroupBallotKHR";
  opcodes[4422] = "OpSubgroupFirstInvocationKHR";

  std::map<uint32_t, std::pair<uint32_t, uint32_t> > hits;
  uint64_t totalHits = 0;
  uint64_t totalBytes = 0;

  for (int i = 1; i < argc; i++) {
    FILE *file = fopen(argv[i], "rb");

    if (0 == file) {
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

  typedef std::pair<uint32_t, std::pair<uint32_t, uint32_t> > MapPair;

  std::vector<MapPair> hitsVector(hits.begin(), hits.end());

  struct Helper {
    static bool _(MapPair a, MapPair b) {
      return a.second.first > b.second.first;
    }
  };

  std::sort(hitsVector.begin(), hitsVector.end(), Helper::_);

  printf("Totals: %" PRIu64 " hits %" PRIu64 " bytes\n", totalHits, totalBytes);

  for (std::vector<MapPair>::iterator i = hitsVector.begin(),
                                      i_e = hitsVector.end();
       i != i_e; ++i) {
    printf("%30s = %6" PRIu32 " hits (%5.2f%%) %6" PRIu32 " bytes (%5.2f%%)\n",
           opcodes.at(i->first), i->second.first,
           static_cast<double>(i->second.first) / totalHits * 100.0,
           i->second.second,
           static_cast<double>(i->second.second) / totalBytes * 100.0);
  }
}
