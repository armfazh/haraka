/*
Optimized Implementations for Haraka256 and Haraka512
*/
#ifndef HARAKA_H_
#define HARAKA_H_

#include "immintrin.h"

#define ALIGN_BYTES 32
#ifdef __INTEL_COMPILER
#define ALIGN __declspec(align(ALIGN_BYTES))
#else
#define ALIGN __attribute__ ((aligned (ALIGN_BYTES)))
#endif

#define AESENC _mm_aesenc_si128
#define NUMROUNDS 5

#define u64 unsigned long
#define u128 __m128i

#define LOAD(src) _mm_load_si128((u128 *)(src))
#define STORE(dest,src) _mm_storeu_si128((u128 *)(dest),src)

#define AES2(s0, s1, rci) \
  s0 = AESENC(s0, _mm_load_si128((u128*)rc+rci + 0)); \
  s1 = AESENC(s1, _mm_load_si128((u128*)rc+rci + 1)); \
  s0 = AESENC(s0, _mm_load_si128((u128*)rc+rci + 2)); \
  s1 = AESENC(s1, _mm_load_si128((u128*)rc+rci + 3));

  
#define AES2_4x_my(rci) \
  tmp = _mm_load_si128((u128*)rc+rci+0); s00 = AESENC(s00, tmp); s10 = AESENC(s10, tmp); s20 = AESENC(s20, tmp); s30 = AESENC(s30, tmp);\
  tmp = _mm_load_si128((u128*)rc+rci+1); s01 = AESENC(s01, tmp); s11 = AESENC(s11, tmp); s21 = AESENC(s21, tmp); s31 = AESENC(s31, tmp);\
  tmp = _mm_load_si128((u128*)rc+rci+2); s00 = AESENC(s00, tmp); s10 = AESENC(s10, tmp); s20 = AESENC(s20, tmp); s30 = AESENC(s30, tmp);\
  tmp = _mm_load_si128((u128*)rc+rci+3); s01 = AESENC(s01, tmp); s11 = AESENC(s11, tmp); s21 = AESENC(s21, tmp); s31 = AESENC(s31, tmp);
  
//#define AES2_4x(s0, s1, s2, s3, rci) \
  AES2(s0[0], s0[1], rci); \
  AES2(s1[0], s1[1], rci); \
  AES2(s2[0], s2[1], rci); \
  AES2(s3[0], s3[1], rci);

#define AES2_8x(s0, s1, s2, s3, s4, s5, s6, s7, rci) \
  AES2_4x(s0, s1, s2, s3, rci); \
  AES2_4x(s4, s5, s6, s7, rci);

#define AES4(s0, s1, s2, s3, rci) \
  s0 = AESENC(s0, _mm_load_si128((u128*)rc+rci + 0)); \
  s1 = AESENC(s1, _mm_load_si128((u128*)rc+rci + 1)); \
  s2 = AESENC(s2, _mm_load_si128((u128*)rc+rci + 2)); \
  s3 = AESENC(s3, _mm_load_si128((u128*)rc+rci + 3)); \
  s0 = AESENC(s0, _mm_load_si128((u128*)rc+rci + 4)); \
  s1 = AESENC(s1, _mm_load_si128((u128*)rc+rci + 5)); \
  s2 = AESENC(s2, _mm_load_si128((u128*)rc+rci + 6)); \
  s3 = AESENC(s3, _mm_load_si128((u128*)rc+rci + 7)); \


  //AES4(s0[0], s0[1], s0[2], s0[3], rci); \
  //AES4(s1[0], s1[1], s1[2], s1[3], rci); \
  //AES4(s2[0], s2[1], s2[2], s2[3], rci); \
  //AES4(s3[0], s3[1], s3[2], s3[3], rci);

 //#define AES4_4x_my(rci)\
    AES4(s00,s01,s02,s03,rci);\
    AES4(s10,s11,s12,s13,rci);\
    AES4(s20,s21,s22,s23,rci);\
    AES4(s30,s31,s32,s33,rci);
 
 
 #define AES4_4x(s0, s1, s2, s3, rci) \
   AES4(s0[0], s0[1], s0[2], s0[3], rci); \
   AES4(s1[0], s1[1], s1[2], s1[3], rci); \
   AES4(s2[0], s2[1], s2[2], s2[3], rci); \
   AES4(s3[0], s3[1], s3[2], s3[3], rci); 

#define AES4_8x(s0, s1, s2, s3, s4, s5, s6, s7, rci) \
  AES4_4x(s0, s1, s2, s3, rci); \
  AES4_4x(s4, s5, s6, s7, rci);

#define MIX2(s0, s1) \
  tmp = _mm_unpacklo_epi32(s0, s1); \
  s1 = _mm_unpackhi_epi32(s0, s1); \
  s0 = tmp;

#define AES4_4x_my(rci) \
  tmp = _mm_load_si128((u128*)rc+rci+0); s00 = AESENC(s00, tmp); s10 = AESENC(s10, tmp); s20 = AESENC(s20, tmp); s30 = AESENC(s30, tmp); \
  tmp = _mm_load_si128((u128*)rc+rci+1); s01 = AESENC(s01, tmp); s11 = AESENC(s11, tmp); s21 = AESENC(s21, tmp); s31 = AESENC(s31, tmp); \
  tmp = _mm_load_si128((u128*)rc+rci+2); s02 = AESENC(s02, tmp); s12 = AESENC(s12, tmp); s22 = AESENC(s22, tmp); s32 = AESENC(s32, tmp); \
  tmp = _mm_load_si128((u128*)rc+rci+3); s03 = AESENC(s03, tmp); s13 = AESENC(s13, tmp); s23 = AESENC(s23, tmp); s33 = AESENC(s33, tmp); \
  tmp = _mm_load_si128((u128*)rc+rci+4); s00 = AESENC(s00, tmp); s10 = AESENC(s10, tmp); s20 = AESENC(s20, tmp); s30 = AESENC(s30, tmp); t0  = _mm_unpacklo_epi32(s00, s01); t1  = _mm_unpacklo_epi32(s10, s11); t2  = _mm_unpacklo_epi32(s20, s21); t3  = _mm_unpacklo_epi32(s30, s31);\
  tmp = _mm_load_si128((u128*)rc+rci+5); s01 = AESENC(s01, tmp); s11 = AESENC(s11, tmp); s21 = AESENC(s21, tmp); s31 = AESENC(s31, tmp); s00 = _mm_unpackhi_epi32(s00, s01); s10 = _mm_unpackhi_epi32(s10, s11); s20 = _mm_unpackhi_epi32(s20, s21); s30 = _mm_unpackhi_epi32(s30, s31);\
  tmp = _mm_load_si128((u128*)rc+rci+6); s02 = AESENC(s02, tmp); s12 = AESENC(s12, tmp); s22 = AESENC(s22, tmp); s32 = AESENC(s32, tmp); s01 = _mm_unpacklo_epi32(s02, s03); s11 = _mm_unpacklo_epi32(s12, s13); s21 = _mm_unpacklo_epi32(s22, s23); s31 = _mm_unpacklo_epi32(s32, s33);\
  tmp = _mm_load_si128((u128*)rc+rci+7); s03 = AESENC(s03, tmp); s13 = AESENC(s13, tmp); s23 = AESENC(s23, tmp); s33 = AESENC(s33, tmp); s02 = _mm_unpackhi_epi32(s02, s03); s12 = _mm_unpackhi_epi32(s12, s13); s22 = _mm_unpackhi_epi32(s22, s23); s32 = _mm_unpackhi_epi32(s32, s33);\
                                                                                                                                         s03 = _mm_unpacklo_epi32(s00, s02); s13 = _mm_unpacklo_epi32(s10, s12); s23 = _mm_unpacklo_epi32(s20, s22); s33 = _mm_unpacklo_epi32(s30, s32);\
                                                                                                                                         s00 = _mm_unpackhi_epi32(s00, s02); s10 = _mm_unpackhi_epi32(s10, s12); s20 = _mm_unpackhi_epi32(s20, s22); s30 = _mm_unpackhi_epi32(s30, s32);\
                                                                                                                                         s02 = _mm_unpackhi_epi32(s01, t0);  s12 = _mm_unpackhi_epi32(s11, t1);  s22 = _mm_unpackhi_epi32(s21, t2);  s32 = _mm_unpackhi_epi32(s31, t3); \
                                                                                                                                         s01 = _mm_unpacklo_epi32(s01, t0);  s11 = _mm_unpacklo_epi32(s11, t1);  s21 = _mm_unpacklo_epi32(s21, t2);  s31 = _mm_unpacklo_epi32(s31, t3); 
  
  
  
  
  
  

  
#define MIX4(s0, s1, s2, s3) \
  tmp  = _mm_unpacklo_epi32(s0, s1); \
  s0 = _mm_unpackhi_epi32(s0, s1); \
  s1 = _mm_unpacklo_epi32(s2, s3); \
  s2 = _mm_unpackhi_epi32(s2, s3); \
  s3 = _mm_unpacklo_epi32(s0, s2); \
  s0 = _mm_unpackhi_epi32(s0, s2); \
  s2 = _mm_unpackhi_epi32(s1, tmp); \
  s1 = _mm_unpacklo_epi32(s1, tmp);

#define TRUNCSTORE(out, s0, s1, s2, s3) \
  *(u64*)(out) = (u64*)(s0)[1]; \
  *(u64*)(out + 8) = (u64*)(s1)[1]; \
  *(u64*)(out + 16) = (u64*)(s2)[0]; \
  *(u64*)(out + 24) = (u64*)(s3)[0];

void load_constants();
void test_implementations();

void haraka256(unsigned char *out, const unsigned char *in);
void haraka256_4x(unsigned char *out, const unsigned char *in);
void haraka256_8x(unsigned char *out, const unsigned char *in);

void haraka512(unsigned char *out, const unsigned char *in);
void haraka512_4x(unsigned char *out, const unsigned char *in);
void haraka512_8x(unsigned char *out, const unsigned char *in);


#endif
