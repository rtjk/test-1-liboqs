
/*
 * CC0 1.0 Universal or the following MIT License
 *
 * MIT License
 *
 * Copyright (c) 2023: Hanno Becker, Vincent Hwang, Matthias J. Kannwischer, Bo-Yin Yang, and Shang-Yi Yang
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef NTT_H
#define NTT_H
#include "params.h"
#include <stdint.h>

#include "NTT_params.h"

extern const int16_t zetas[128];

#define ntt KYBER_NAMESPACE(ntt)
void ntt(int16_t r[256]);
#define invntt KYBER_NAMESPACE(invntt)
void invntt(int16_t r[256]);


extern void PQCLEAN_KYBER1024_AARCH64__asm_ntt_SIMD_top(int16_t*, const int16_t*, const int16_t*);
extern void PQCLEAN_KYBER1024_AARCH64__asm_ntt_SIMD_bot(int16_t*, const int16_t*, const int16_t*);

extern void PQCLEAN_KYBER1024_AARCH64__asm_intt_SIMD_bot(int16_t*, const int16_t*, const int16_t*);
extern void PQCLEAN_KYBER1024_AARCH64__asm_intt_SIMD_top(int16_t*, const int16_t*, const int16_t*);

extern void PQCLEAN_KYBER1024_AARCH64__asm_point_mul_extended(int16_t*, const int16_t*, const int16_t*, const int16_t*);
extern void PQCLEAN_KYBER1024_AARCH64__asm_asymmetric_mul(const int16_t*, const int16_t*, const int16_t*, const int16_t*, int16_t*);
extern void PQCLEAN_KYBER1024_AARCH64__asm_asymmetric_mul_montgomery(const int16_t*, const int16_t*, const int16_t*, const int16_t*, int16_t*);

static const int16_t asymmetric_const[16] = {
Q1, Q1prime2, RmodQ1, RmodQ1Q1prime, R3modQ1_prime_half, R3modQ1_doubleprime
};

#define NTT(in) { \
        PQCLEAN_KYBER1024_AARCH64__asm_ntt_SIMD_top(in, streamlined_CT_negacyclic_table_Q1_extended, constants); \
        PQCLEAN_KYBER1024_AARCH64__asm_ntt_SIMD_bot(in, streamlined_CT_negacyclic_table_Q1_extended, constants); \
    }

#define iNTT(in) { \
	PQCLEAN_KYBER1024_AARCH64__asm_intt_SIMD_bot(in, streamlined_inv_CT_table_Q1_extended, constants); \
	PQCLEAN_KYBER1024_AARCH64__asm_intt_SIMD_top(in, streamlined_inv_CT_table_Q1_extended, constants); \
    }

static const int16_t constants[16] = {
Q1, Q1prime2, RmodQ1, RmodQ1Q1prime, roundRdivQ1,
invNQ1_R3modQ1_prime_half,
invNQ1_R3modQ1_doubleprime,
invNQ1_final_R3modQ1_prime_half,
invNQ1_final_R3modQ1_doubleprime
};

static const int16_t streamlined_CT_negacyclic_table_Q1_extended[(NTT_N + (1 << 0) + (1 << 4) + NTT_N) << 1] =
{
0, 0, -15749, -1600, -7373, -749, -394, -40, -6762, -687, 6201, 630, -14095, -1432, 8347, 848, 10453, 1062, -13879, -1410, 1900, 193, 7845, 797, -5345, -543, -679, -69, 5601, 569, -15582, -1583, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2914, 296, 2914, 296, 14036, 1426, 14036, 1426, -8682, -882, -8682, -882, -12156, -1235, -12156, -1235, 2845, 289, 2845, 289, -9942, -1010, -9942, -1010, -748, -76, -748, -76, 7943, 807, 7943, 807, 3258, 331, 3258, 331, 14125, 1435, 14125, 1435, -15483, -1573, -15483, -1573, 4449, 452, 4449, 452, 167, 17, 167, 17, 15592, 1584, 15592, 1584, 16113, 1637, 16113, 1637, 3691, 375, 3691, 375, -5591, -568, -5591, -568, -10148, -1031, -10148, -1031, 7117, 723, 7117, 723, -7678, -780, -7678, -780, 5739, 583, 5739, 583, -12717, -1292, -12717, -1292, -10247, -1041, -10247, -1041, -12196, -1239, -12196, -1239, -6693, -680, -6693, -680, -1073, -109, -1073, -109, 10828, 1100, 10828, 1100, 16192, 1645, 16192, 1645, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13180, 1339, 13180, 1339, 5266, 535, 5266, 535, 14529, 1476, 14529, 1476, -4400, -447, -4400, -447, 11782, 1197, 11782, 1197, 14155, 1438, 14155, 1438, -10355, -1052, -10355, -1052, 15099, 1534, 15099, 1534, -10089, -1025, -10089, -1025, -4538, -461, -4538, -461, -12540, -1274, -12540, -1274, -9125, -927, -9125, -927, 13869, 1409, 13869, 1409, 10463, 1063, 10463, 1063, 7441, 756, 7441, 756, -12107, -1230, -12107, -1230, -6565, -667, -6565, -667, 3140, 319, 3140, 319, -11546, -1173, -11546, -1173, 5522, 561, 5522, 561, -472, -48, -472, -48, -5473, -556, -5473, -556, -3091, -314, -3091, -314, -8495, -863, -8495, -863, 2293, 233, 2293, 233, 7451, 757, 7451, 757, -2746, -279, -2746, -279, -7235, -735, -7235, -735, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -2786, -283, -2786, -283, -9213, -936, -9213, -936, 551, 56, 551, 56, -4429, -450, -4429, -450, 6398, 650, 6398, 650, -6713, -682, -6713, -682, -8032, -816, -8032, -816, 14578, 1481, 14578, 1481, -13308, -1352, -13308, -1352, -7008, -712, -7008, -712, 6221, 632, 6221, 632, 6378, 648, 6378, 648, -16005, -1626, -16005, -1626, -5168, -525, -5168, -525, -14588, -1482, -14588, -1482, 11251, 1143, 11251, 1143, 16251, 1651, 16251, 1651, 10749, 1092, 10749, 1092, 9371, 952, 9371, 952, -11605, -1179, -11605, -1179, -5315, -540, -5315, -540, 3967, 403, 3967, 403, 14381, 1461, 14381, 1461, -5453, -554, -5453, -554, -15159, -1540, -15159, -1540, 10099, 1026, 10099, 1026, -6319, -642, -6319, -642, 8721, 886, 8721, 886, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -10719, -1089, -10719, -1089, -13338, -1355, -13338, -1355, 13121, 1333, 13121, 1333, 8081, 821, 8081, 821, -4567, -464, -4567, -464, -8416, -855, -8416, -855, 12993, 1320, 12993, 1320, 12078, 1227, 12078, 1227, 325, 33, 325, 33, -2156, -219, -2156, -219, -13918, -1414, -13918, -1414, 8957, 910, 8957, 910, 9243, 939, 9243, 939, -15818, -1607, -15818, -1607, 7215, 733, 7215, 733, -11999, -1219, -11999, -1219, -10050, -1021, -10050, -1021, 11930, 1212, 11930, 1212, -9764, -992, -9764, -992, -3878, -394, -3878, -394, -8780, -892, -8780, -892, -14322, -1455, -14322, -1455, 2638, 268, 2638, 268, 8711, 885, 8711, 885, -9262, -941, -9262, -941, 10129, 1029, 10129, 1029, 6309, 641, 6309, 641, -11566, -1175, -11566, -1175, 0, 0
};

static const int16_t pre_asymmetric_table_Q1_extended[ARRAY_N] =
{
167, 17, -167, -17, -5591, -568, 5591, 568, 5739, 583, -5739, -583, -6693, -680, 6693, 680, 16113, 1637, -16113, -1637, 7117, 723, -7117, -723, -10247, -1041, 10247, 1041, 10828, 1100, -10828, -1100, 13869, 1409, -13869, -1409, -6565, -667, 6565, 667, -472, -48, 472, 48, 2293, 233, -2293, -233, 7441, 756, -7441, -756, -11546, -1173, 11546, 1173, -3091, -314, 3091, 314, -2746, -279, 2746, 279, -16005, -1626, 16005, 1626, 16251, 1651, -16251, -1651, -5315, -540, 5315, 540, -15159, -1540, 15159, 1540, -14588, -1482, 14588, 1482, 9371, 952, -9371, -952, 14381, 1461, -14381, -1461, -6319, -642, 6319, 642, 9243, 939, -9243, -939, -10050, -1021, 10050, 1021, -8780, -892, 8780, 892, -9262, -941, 9262, 941, 7215, 733, -7215, -733, -9764, -992, 9764, 992, 2638, 268, -2638, -268, 6309, 641, -6309, -641, 15592, 1584, -15592, -1584, -10148, -1031, 10148, 1031, -12717, -1292, 12717, 1292, -1073, -109, 1073, 109, 3691, 375, -3691, -375, -7678, -780, 7678, 780, -12196, -1239, 12196, 1239, 16192, 1645, -16192, -1645, 10463, 1063, -10463, -1063, 3140, 319, -3140, -319, -5473, -556, 5473, 556, 7451, 757, -7451, -757, -12107, -1230, 12107, 1230, 5522, 561, -5522, -561, -8495, -863, 8495, 863, -7235, -735, 7235, 735, -5168, -525, 5168, 525, 10749, 1092, -10749, -1092, 3967, 403, -3967, -403, 10099, 1026, -10099, -1026, 11251, 1143, -11251, -1143, -11605, -1179, 11605, 1179, -5453, -554, 5453, 554, 8721, 886, -8721, -886, -15818, -1607, 15818, 1607, 11930, 1212, -11930, -1212, -14322, -1455, 14322, 1455, 10129, 1029, -10129, -1029, -11999, -1219, 11999, 1219, -3878, -394, 3878, 394, 8711, 885, -8711, -885, -11566, -1175, 11566, 1175
};

static const int16_t streamlined_inv_CT_table_Q1_extended[(NTT_N + (1 << 0) + (1 << 4) + NTT_N) << 1] =
{
0, 0, 15749, 1600, 394, 40, 7373, 749, -8347, -848, 14095, 1432, -6201, -630, 6762, 687, 15582, 1583, -5601, -569, 679, 69, 5345, 543, -7845, -797, -1900, -193, 13879, 1410, -10453, -1062, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -8081, -821, -8081, -821, -13121, -1333, -13121, -1333, 13338, 1355, 13338, 1355, 10719, 1089, 10719, 1089, -8957, -910, -8957, -910, 13918, 1414, 13918, 1414, 2156, 219, 2156, 219, -325, -33, -325, -33, -12078, -1227, -12078, -1227, -12993, -1320, -12993, -1320, 8416, 855, 8416, 855, 4567, 464, 4567, 464, 11566, 1175, 11566, 1175, -6309, -641, -6309, -641, -10129, -1029, -10129, -1029, 9262, 941, 9262, 941, -8711, -885, -8711, -885, -2638, -268, -2638, -268, 14322, 1455, 14322, 1455, 8780, 892, 8780, 892, 3878, 394, 3878, 394, 9764, 992, 9764, 992, -11930, -1212, -11930, -1212, 10050, 1021, 10050, 1021, 11999, 1219, 11999, 1219, -7215, -733, -7215, -733, 15818, 1607, 15818, 1607, -9243, -939, -9243, -939, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4429, 450, 4429, 450, -551, -56, -551, -56, 9213, 936, 9213, 936, 2786, 283, 2786, 283, -6378, -648, -6378, -648, -6221, -632, -6221, -632, 7008, 712, 7008, 712, 13308, 1352, 13308, 1352, -14578, -1481, -14578, -1481, 8032, 816, 8032, 816, 6713, 682, 6713, 682, -6398, -650, -6398, -650, -8721, -886, -8721, -886, 6319, 642, 6319, 642, -10099, -1026, -10099, -1026, 15159, 1540, 15159, 1540, 5453, 554, 5453, 554, -14381, -1461, -14381, -1461, -3967, -403, -3967, -403, 5315, 540, 5315, 540, 11605, 1179, 11605, 1179, -9371, -952, -9371, -952, -10749, -1092, -10749, -1092, -16251, -1651, -16251, -1651, -11251, -1143, -11251, -1143, 14588, 1482, 14588, 1482, 5168, 525, 5168, 525, 16005, 1626, 16005, 1626, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4400, 447, 4400, 447, -14529, -1476, -14529, -1476, -5266, -535, -5266, -535, -13180, -1339, -13180, -1339, 9125, 927, 9125, 927, 12540, 1274, 12540, 1274, 4538, 461, 4538, 461, 10089, 1025, 10089, 1025, -15099, -1534, -15099, -1534, 10355, 1052, 10355, 1052, -14155, -1438, -14155, -1438, -11782, -1197, -11782, -1197, 7235, 735, 7235, 735, 2746, 279, 2746, 279, -7451, -757, -7451, -757, -2293, -233, -2293, -233, 8495, 863, 8495, 863, 3091, 314, 3091, 314, 5473, 556, 5473, 556, 472, 48, 472, 48, -5522, -561, -5522, -561, 11546, 1173, 11546, 1173, -3140, -319, -3140, -319, 6565, 667, 6565, 667, 12107, 1230, 12107, 1230, -7441, -756, -7441, -756, -10463, -1063, -10463, -1063, -13869, -1409, -13869, -1409, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12156, 1235, 12156, 1235, 8682, 882, 8682, 882, -14036, -1426, -14036, -1426, -2914, -296, -2914, -296, -4449, -452, -4449, -452, 15483, 1573, 15483, 1573, -14125, -1435, -14125, -1435, -3258, -331, -3258, -331, -7943, -807, -7943, -807, 748, 76, 748, 76, 9942, 1010, 9942, 1010, -2845, -289, -2845, -289, -16192, -1645, -16192, -1645, -10828, -1100, -10828, -1100, 1073, 109, 1073, 109, 6693, 680, 6693, 680, 12196, 1239, 12196, 1239, 10247, 1041, 10247, 1041, 12717, 1292, 12717, 1292, -5739, -583, -5739, -583, 7678, 780, 7678, 780, -7117, -723, -7117, -723, 10148, 1031, 10148, 1031, 5591, 568, 5591, 568, -3691, -375, -3691, -375, -16113, -1637, -16113, -1637, -15592, -1584, -15592, -1584, -167, -17, -167, -17, 0, 0
};

#endif
