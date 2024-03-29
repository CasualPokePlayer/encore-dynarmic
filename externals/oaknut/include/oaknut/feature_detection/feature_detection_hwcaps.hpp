// SPDX-FileCopyrightText: Copyright (c) 2023 merryhime <https://mary.rs>
// SPDX-License-Identifier: MIT

#pragma once

#include <cstddef>

#include "oaknut/feature_detection/cpu_feature.hpp"

namespace oaknut {

namespace detail {

template<std::size_t... bits>
constexpr bool bit_test(unsigned long value)
{
    return (((value >> bits) & 1) && ...);
}

}  // namespace detail

inline CpuFeatures detect_features_via_hwcap(unsigned long hwcap, unsigned long hwcap2)
{
    CpuFeatures result;

#define OAKNUT_DETECT_CAP(FEAT, ...)             \
    if (detail::bit_test<__VA_ARGS__>(hwcap)) {  \
        result |= CpuFeatures{CpuFeature::FEAT}; \
    }
#define OAKNUT_DETECT_CAP2(FEAT, ...)            \
    if (detail::bit_test<__VA_ARGS__>(hwcap2)) { \
        result |= CpuFeatures{CpuFeature::FEAT}; \
    }

    OAKNUT_DETECT_CAP(FP, 0)            // HWCAP_FP
    OAKNUT_DETECT_CAP(ASIMD, 1)         // HWCAP_ASIMD
                                        // HWCAP_EVTSTRM (2)
    OAKNUT_DETECT_CAP(AES, 3)           // HWCAP_AES
    OAKNUT_DETECT_CAP(PMULL, 4)         // HWCAP_PMULL
    OAKNUT_DETECT_CAP(SHA1, 5)          // HWCAP_SHA1
    OAKNUT_DETECT_CAP(SHA256, 6)        // HWCAP_SHA2
    OAKNUT_DETECT_CAP(CRC32, 7)         // HWCAP_CRC32
    OAKNUT_DETECT_CAP(LSE, 8)           // HWCAP_ATOMICS
    OAKNUT_DETECT_CAP(FP16Conv, 9, 10)  // HWCAP_FPHP && HWCAP_ASIMDHP
    OAKNUT_DETECT_CAP(FP16, 9, 10)      // HWCAP_FPHP && HWCAP_ASIMDHP
                                        // HWCAP_CPUID (11)
    OAKNUT_DETECT_CAP(RDM, 12)          // HWCAP_ASIMDRDM
    OAKNUT_DETECT_CAP(JSCVT, 13)        // HWCAP_JSCVT
    OAKNUT_DETECT_CAP(FCMA, 14)         // HWCAP_FCMA
    OAKNUT_DETECT_CAP(LRCPC, 15)        // HWCAP_LRCPC
    OAKNUT_DETECT_CAP(DPB, 16)          // HWCAP_DCPOP
    OAKNUT_DETECT_CAP(SHA3, 17)         // HWCAP_SHA3
    OAKNUT_DETECT_CAP(SM3, 18)          // HWCAP_SM3
    OAKNUT_DETECT_CAP(SM4, 19)          // HWCAP_SM4
    OAKNUT_DETECT_CAP(DotProd, 20)      // HWCAP_ASIMDDP
    OAKNUT_DETECT_CAP(SHA512, 21)       // HWCAP_SHA512
    OAKNUT_DETECT_CAP(SVE, 22)          // HWCAP_SVE
    OAKNUT_DETECT_CAP(FHM, 23)          // HWCAP_ASIMDFHM
    OAKNUT_DETECT_CAP(DIT, 24)          // HWCAP_DIT
    OAKNUT_DETECT_CAP(LSE2, 25)         // HWCAP_USCAT
    OAKNUT_DETECT_CAP(LRCPC2, 26)       // HWCAP_ILRCPC
    OAKNUT_DETECT_CAP(FlagM, 27)        // HWCAP_FLAGM
    OAKNUT_DETECT_CAP(SSBS, 28)         // HWCAP_SSBS
    OAKNUT_DETECT_CAP(SB, 29)           // HWCAP_SB
    OAKNUT_DETECT_CAP(PACA, 30)         // HWCAP_PACA
    OAKNUT_DETECT_CAP(PACG, 31)         // HWCAP_PACG

    OAKNUT_DETECT_CAP2(DPB2, 0)          // HWCAP2_DCPODP
    OAKNUT_DETECT_CAP2(SVE2, 1)          // HWCAP2_SVE2
    OAKNUT_DETECT_CAP2(SVE_AES, 2)       // HWCAP2_SVEAES
    OAKNUT_DETECT_CAP2(SVE_PMULL128, 3)  // HWCAP2_SVEPMULL
    OAKNUT_DETECT_CAP2(SVE_BITPERM, 4)   // HWCAP2_SVEBITPERM
    OAKNUT_DETECT_CAP2(SVE_SHA3, 5)      // HWCAP2_SVESHA3
    OAKNUT_DETECT_CAP2(SVE_SM4, 6)       // HWCAP2_SVESM4
    OAKNUT_DETECT_CAP2(FlagM2, 7)        // HWCAP2_FLAGM2
    OAKNUT_DETECT_CAP2(FRINTTS, 8)       // HWCAP2_FRINT
    OAKNUT_DETECT_CAP2(SVE_I8MM, 9)      // HWCAP2_SVEI8MM
    OAKNUT_DETECT_CAP2(SVE_F32MM, 10)    // HWCAP2_SVEF32MM
    OAKNUT_DETECT_CAP2(SVE_F64MM, 11)    // HWCAP2_SVEF64MM
    OAKNUT_DETECT_CAP2(SVE_BF16, 12)     // HWCAP2_SVEBF16
    OAKNUT_DETECT_CAP2(I8MM, 13)         // HWCAP2_I8MM
    OAKNUT_DETECT_CAP2(BF16, 14)         // HWCAP2_BF16
    OAKNUT_DETECT_CAP2(DGH, 15)          // HWCAP2_DGH
    OAKNUT_DETECT_CAP2(RNG, 16)          // HWCAP2_RNG
    OAKNUT_DETECT_CAP2(BTI, 17)          // HWCAP2_BTI
    OAKNUT_DETECT_CAP2(MTE, 18)          // HWCAP2_MTE
    OAKNUT_DETECT_CAP2(ECV, 19)          // HWCAP2_ECV
    OAKNUT_DETECT_CAP2(AFP, 20)          // HWCAP2_AFP
    OAKNUT_DETECT_CAP2(RPRES, 21)        // HWCAP2_RPRES
    OAKNUT_DETECT_CAP2(MTE3, 22)         // HWCAP2_MTE3
    OAKNUT_DETECT_CAP2(SME, 23)          // HWCAP2_SME
    OAKNUT_DETECT_CAP2(SME_I16I64, 24)   // HWCAP2_SME_I16I64
    OAKNUT_DETECT_CAP2(SME_F64F64, 25)   // HWCAP2_SME_F64F64
    OAKNUT_DETECT_CAP2(SME_I8I32, 26)    // HWCAP2_SME_I8I32
    OAKNUT_DETECT_CAP2(SME_F16F32, 27)   // HWCAP2_SME_F16F32
    OAKNUT_DETECT_CAP2(SME_B16F32, 28)   // HWCAP2_SME_B16F32
    OAKNUT_DETECT_CAP2(SME_F32F32, 29)   // HWCAP2_SME_F32F32
    OAKNUT_DETECT_CAP2(SME_FA64, 30)     // HWCAP2_SME_FA64
    OAKNUT_DETECT_CAP2(WFxT, 31)         // HWCAP2_WFXT
    OAKNUT_DETECT_CAP2(EBF16, 32)        // HWCAP2_EBF16
    OAKNUT_DETECT_CAP2(SVE_EBF16, 33)    // HWCAP2_SVE_EBF16
    OAKNUT_DETECT_CAP2(CSSC, 34)         // HWCAP2_CSSC
    OAKNUT_DETECT_CAP2(RPRFM, 35)        // HWCAP2_RPRFM
    OAKNUT_DETECT_CAP2(SVE2p1, 36)       // HWCAP2_SVE2P1
    OAKNUT_DETECT_CAP2(SME2, 37)         // HWCAP2_SME2
    OAKNUT_DETECT_CAP2(SME2p1, 38)       // HWCAP2_SME2P1
    OAKNUT_DETECT_CAP2(SME_I16I32, 39)   // HWCAP2_SME_I16I32
    OAKNUT_DETECT_CAP2(SME_BI32I32, 40)  // HWCAP2_SME_BI32I32
    OAKNUT_DETECT_CAP2(SME_B16B16, 41)   // HWCAP2_SME_B16B16
    OAKNUT_DETECT_CAP2(SME_F16F16, 42)   // HWCAP2_SME_F16F16
    OAKNUT_DETECT_CAP2(MOPS, 43)         // HWCAP2_MOPS
    OAKNUT_DETECT_CAP2(HBC, 44)          // HWCAP2_HBC

#undef OAKNUT_DETECT_CAP
#undef OAKNUT_DETECT_CAP2

    return result;
}

}  // namespace oaknut
