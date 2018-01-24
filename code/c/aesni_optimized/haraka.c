#include "haraka.h"
#include <stdio.h>
#include <stdint.h>

static const ALIGN uint32_t rc[40*4] = {
    0x75817b9d,0xb2c5fef0,0xe620c00a,0x0684704c,
    0x2f08f717,0x640f6ba4,0x88f3a06b,0x8b66b4e1,
    0x9f029114,0xcf029d60,0x53f28498,0x3402de2d,
    0xfd5b4f79,0xbbf3bcaf,0x2e7b4f08,0x0ed6eae6,
    0xbe397044,0x79eecd1c,0x4872448b,0xcbcfb0cb,
    0x2b8a057b,0x8d5335ed,0x6e9032b7,0x7eeacdee,
    0xda4fef1b,0xe2412761,0x5e2e7cd0,0x67c28f43,
    0x1fc70b3b,0x675ffde2,0xafcacc07,0x2924d9b0,
    0xb9d465ee,0xecdb8fca,0xe6867fe9,0xab4d63f1,
    0xad037e33,0x5b2a404f,0xd4b7cd64,0x1c30bf84,
    0x8df69800,0x69028b2e,0x941723bf,0xb2cc0bb9,
    0x5c9d2d8a,0x4aaa9ec8,0xde6f5572,0xfa0478a6,
    0x29129fd4,0x0efa4f2e,0x6b772a12,0xdfb49f2b,
    0xbb6a12ee,0x32d611ae,0xf449a236,0x1ea10344,
    0x9ca8eca6,0x5f9600c9,0x4b050084,0xaf044988,
    0x27e593ec,0x78a2c7e3,0x9d199c4f,0x21025ed8,
    0x82d40173,0xb9282ecd,0xa759c9b7,0xbf3aaaf8,
    0x10307d6b,0x37f2efd9,0x6186b017,0x6260700d,
    0xf6fc9ac6,0x81c29153,0x21300443,0x5aca45c2,
    0x36d1943a,0x2caf92e8,0x226b68bb,0x9223973c,
    0xe51071b4,0x6cbab958,0x225886eb,0xd3bf9238,
    0x24e1128d,0x933dfddd,0xaef0c677,0xdb863ce5,
    0xcb2212b1,0x83e48de3,0xffeba09c,0xbb606268,
    0xc72bf77d,0x2db91a4e,0xe2e4d19c,0x734bd3dc,
    0x2cb3924e,0x4b1415c4,0x61301b43,0x43bb47c3,
    0x16eb6899,0x03b231dd,0xe707eff6,0xdba775a8,
    0x7eca472c,0x8e5e2302,0x3c755977,0x6df3614b,
    0xb88617f9,0x6d1be5b9,0xd6de7d77,0xcda75a17,
    0xa946ee5d,0x9d6c069d,0x6ba8e9aa,0xec6b43f0,
    0x3bf327c1,0xa2531159,0xf957332b,0xcb1e6950,
    0x600ed0d9,0xe4ed0353,0x00da619c,0x2cee0c75,
    0x63a4a350,0x80bbbabc,0x96e90cab,0xf0b1a5a1,
    0x938dca39,0xab0dde30,0x5e962988,0xae3db102,
    0x2e75b442,0x8814f3a8,0xd554a40b,0x17bb8f38,
    0x360a16f6,0xaeb6b779,0x5f427fd7,0x34bb8a5b,
    0xffbaafde,0x43ce5918,0xcbe55438,0x26f65241,
    0x839ec978,0xa2ca9cf7,0xb9f3026a,0x4ce99a54,
    0x22901235,0x40c06e28,0x1bdff7be,0xae51a51a,
    0x48a659cf,0xc173bc0f,0xba7ed22b,0xa0c1613c,
    0xe9c59da1,0x4ad6bdfd,0x02288288,0x756acc03
};


void load_constants() { }

void test_implementations() {
  unsigned char *in = (unsigned char *)_mm_malloc(64*8*sizeof(unsigned char),ALIGN_BYTES);
  unsigned char *out256 = (unsigned char *)_mm_malloc(32*8*sizeof(unsigned char),ALIGN_BYTES);
  unsigned char *out512 = (unsigned char *)_mm_malloc(32*8*sizeof(unsigned char),ALIGN_BYTES);
  unsigned char testvector256[32] = {0x80, 0x27, 0xcc, 0xb8, 0x79, 0x49, 0x77, 0x4b,
                                     0x78, 0xd0, 0x54, 0x5f, 0xb7, 0x2b, 0xf7, 0x0c,
                                     0x69, 0x5c, 0x2a, 0x09, 0x23, 0xcb, 0xd4, 0x7b,
                                     0xba, 0x11, 0x59, 0xef, 0xbf, 0x2b, 0x2c, 0x1c};

 unsigned char testvector512[32] = {0xbe, 0x7f, 0x72, 0x3b, 0x4e, 0x80, 0xa9, 0x98,
                                    0x13, 0xb2, 0x92, 0x28, 0x7f, 0x30, 0x6f, 0x62,
                                    0x5a, 0x6d, 0x57, 0x33, 0x1c, 0xae, 0x5f, 0x34,
                                    0xdd, 0x92, 0x77, 0xb0, 0x94, 0x5b, 0xe2, 0xaa};



  int i;

  // Input for testvector
  for(i = 0; i < 512; i++) {
    in[i] = i % 64;
  }

  load_constants();
  haraka512_8x(out512, in);

  // Verify output
  for(i = 0; i < 32; i++) {
    if (out512[i % 32] != testvector512[i]) {
      printf("Error: testvector incorrect.\n");
      return;
    }
  }

  _mm_free(in);
  _mm_free(out256);
  _mm_free(out512);
}

void haraka256(unsigned char *out, const unsigned char *in) {
  __m128i s[2], tmp;

  s[0] = LOAD(in);
  s[1] = LOAD(in + 16);

  AES2(s[0], s[1], 0);
  MIX2(s[0], s[1]);

  AES2(s[0], s[1], 4);
  MIX2(s[0], s[1]);

  AES2(s[0], s[1], 8);
  MIX2(s[0], s[1]);

  AES2(s[0], s[1], 12);
  MIX2(s[0], s[1]);

  AES2(s[0], s[1], 16);
  MIX2(s[0], s[1]);

  s[0] = _mm_xor_si128(s[0], LOAD(in));
  s[1] = _mm_xor_si128(s[1], LOAD(in + 16));

  STORE(out, s[0]);
  STORE(out + 16, s[1]);
}

void haraka256_4x(unsigned char *out, const unsigned char *in) {
//   ALIGN u128 s[4][2], tmp;

  u128 tmp;
  u128 s00 = LOAD(in);
  u128 s01 = LOAD(in + 16);
  u128 s10 = LOAD(in + 32);
  u128 s11 = LOAD(in + 48);
  u128 s20 = LOAD(in + 64);
  u128 s21 = LOAD(in + 80);
  u128 s30 = LOAD(in + 96);
  u128 s31 = LOAD(in + 112);

  // Round 1
  AES2_4x_my(0);
  MIX2(s00, s01);
  MIX2(s10, s11);
  MIX2(s20, s21);
  MIX2(s30, s31);

  // Round 2
  AES2_4x_my(4);
  MIX2(s00, s01);
  MIX2(s10, s11);
  MIX2(s20, s21);
  MIX2(s30, s31);

  // Round 3
  AES2_4x_my(8);
  MIX2(s00, s01);
  MIX2(s10, s11);
  MIX2(s20, s21);
  MIX2(s30, s31);

  // Round 4
  AES2_4x_my(12);
  MIX2(s00, s01);
  MIX2(s10, s11);
  MIX2(s20, s21);
  MIX2(s30, s31);

  // Round 5
  AES2_4x_my(16);
  MIX2(s00, s01);
  MIX2(s10, s11);
  MIX2(s20, s21);
  MIX2(s30, s31);

  // Feed Forward
  s00 = _mm_xor_si128(s00, LOAD(in));
  s01 = _mm_xor_si128(s01, LOAD(in + 16));
  s10 = _mm_xor_si128(s10, LOAD(in + 32));
  s11 = _mm_xor_si128(s11, LOAD(in + 48));
  s20 = _mm_xor_si128(s20, LOAD(in + 64));
  s21 = _mm_xor_si128(s21, LOAD(in + 80));
  s30 = _mm_xor_si128(s30, LOAD(in + 96));
  s31 = _mm_xor_si128(s31, LOAD(in + 112));

  STORE(out +  00, s00);
  STORE(out +  16, s01);
  STORE(out +  32, s10);
  STORE(out +  48, s11);
  STORE(out +  64, s20);
  STORE(out +  80, s21);
  STORE(out +  96, s30);
  STORE(out + 112, s31);
}

void haraka256_8x(unsigned char *out, const unsigned char *in) {
  // This is faster on Skylake, the code below is faster on Haswell.
  haraka256_4x(out, in);
  haraka256_4x(out + 128, in + 128);
  return;
  // __m128i s[8][2], tmp;
  //
  // int i;
  //
  // s[0][0] = LOAD(in);
  // s[0][1] = LOAD(in + 16);
  // s[1][0] = LOAD(in + 32);
  // s[1][1] = LOAD(in + 48);
  // s[2][0] = LOAD(in + 64);
  // s[2][1] = LOAD(in + 80);
  // s[3][0] = LOAD(in + 96);
  // s[3][1] = LOAD(in + 112);
  // s[4][0] = LOAD(in + 128);
  // s[4][1] = LOAD(in + 144);
  // s[5][0] = LOAD(in + 160);
  // s[5][1] = LOAD(in + 176);
  // s[6][0] = LOAD(in + 192);
  // s[6][1] = LOAD(in + 208);
  // s[7][0] = LOAD(in + 224);
  // s[7][1] = LOAD(in + 240);
  //
  // // Round 1
  // AES2_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 0);
  //
  // MIX2(s[0][0], s[0][1]);
  // MIX2(s[1][0], s[1][1]);
  // MIX2(s[2][0], s[2][1]);
  // MIX2(s[3][0], s[3][1]);
  // MIX2(s[4][0], s[4][1]);
  // MIX2(s[5][0], s[5][1]);
  // MIX2(s[6][0], s[6][1]);
  // MIX2(s[7][0], s[7][1]);
  //
  //
  // // Round 2
  // AES2_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 4);
  //
  // MIX2(s[0][0], s[0][1]);
  // MIX2(s[1][0], s[1][1]);
  // MIX2(s[2][0], s[2][1]);
  // MIX2(s[3][0], s[3][1]);
  // MIX2(s[4][0], s[4][1]);
  // MIX2(s[5][0], s[5][1]);
  // MIX2(s[6][0], s[6][1]);
  // MIX2(s[7][0], s[7][1]);
  //
  // // Round 3
  // AES2_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 8);
  //
  // MIX2(s[0][0], s[0][1]);
  // MIX2(s[1][0], s[1][1]);
  // MIX2(s[2][0], s[2][1]);
  // MIX2(s[3][0], s[3][1]);
  // MIX2(s[4][0], s[4][1]);
  // MIX2(s[5][0], s[5][1]);
  // MIX2(s[6][0], s[6][1]);
  // MIX2(s[7][0], s[7][1]);
  //
  // // Round 4
  // AES2_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 12);
  //
  // MIX2(s[0][0], s[0][1]);
  // MIX2(s[1][0], s[1][1]);
  // MIX2(s[2][0], s[2][1]);
  // MIX2(s[3][0], s[3][1]);
  // MIX2(s[4][0], s[4][1]);
  // MIX2(s[5][0], s[5][1]);
  // MIX2(s[6][0], s[6][1]);
  // MIX2(s[7][0], s[7][1]);
  //
  // // Round 5
  // AES2_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 16);
  //
  // MIX2(s[0][0], s[0][1]);
  // MIX2(s[1][0], s[1][1]);
  // MIX2(s[2][0], s[2][1]);
  // MIX2(s[3][0], s[3][1]);
  // MIX2(s[4][0], s[4][1]);
  // MIX2(s[5][0], s[5][1]);
  // MIX2(s[6][0], s[6][1]);
  // MIX2(s[7][0], s[7][1]);
  //
  // // Feed Forward
  // s[0][0] = _mm_xor_si128(s[0][0], LOAD(in));
  // s[0][1] = _mm_xor_si128(s[0][1], LOAD(in + 16));
  // s[1][0] = _mm_xor_si128(s[1][0], LOAD(in + 32));
  // s[1][1] = _mm_xor_si128(s[1][1], LOAD(in + 48));
  // s[2][0] = _mm_xor_si128(s[2][0], LOAD(in + 64));
  // s[2][1] = _mm_xor_si128(s[2][1], LOAD(in + 80));
  // s[3][0] = _mm_xor_si128(s[3][0], LOAD(in + 96));
  // s[3][1] = _mm_xor_si128(s[3][1], LOAD(in + 112));
  // s[4][0] = _mm_xor_si128(s[4][0], LOAD(in + 128));
  // s[4][1] = _mm_xor_si128(s[4][1], LOAD(in + 144));
  // s[5][0] = _mm_xor_si128(s[5][0], LOAD(in + 160));
  // s[5][1] = _mm_xor_si128(s[5][1], LOAD(in + 176));
  // s[6][0] = _mm_xor_si128(s[6][0], LOAD(in + 192));
  // s[6][1] = _mm_xor_si128(s[6][1], LOAD(in + 208));
  // s[7][0] = _mm_xor_si128(s[7][0], LOAD(in + 224));
  // s[7][1] = _mm_xor_si128(s[7][1], LOAD(in + 240));
  //
  // STORE(out, s[0][0]);
  // STORE(out + 16, s[0][1]);
  // STORE(out + 32, s[1][0]);
  // STORE(out + 48, s[1][1]);
  // STORE(out + 64, s[2][0]);
  // STORE(out + 80, s[2][1]);
  // STORE(out + 96, s[3][0]);
  // STORE(out + 112, s[3][1]);
  // STORE(out + 128, s[4][0]);
  // STORE(out + 144, s[4][1]);
  // STORE(out + 160, s[5][0]);
  // STORE(out + 176, s[5][1]);
  // STORE(out + 192, s[6][0]);
  // STORE(out + 208, s[6][1]);
  // STORE(out + 224, s[7][0]);
  // STORE(out + 240, s[7][1]);
}

void haraka512(unsigned char *out, const unsigned char *in) {
  u128 s[4], tmp;

  s[0] = LOAD(in);
  s[1] = LOAD(in + 16);
  s[2] = LOAD(in + 32);
  s[3] = LOAD(in + 48);

  AES4(s[0], s[1], s[2], s[3], 0);
  MIX4(s[0], s[1], s[2], s[3]);

  AES4(s[0], s[1], s[2], s[3], 8);
  MIX4(s[0], s[1], s[2], s[3]);

  AES4(s[0], s[1], s[2], s[3], 16);
  MIX4(s[0], s[1], s[2], s[3]);

  AES4(s[0], s[1], s[2], s[3], 24);
  MIX4(s[0], s[1], s[2], s[3]);

  AES4(s[0], s[1], s[2], s[3], 32);
  MIX4(s[0], s[1], s[2], s[3]);

  s[0] = _mm_xor_si128(s[0], LOAD(in));
  s[1] = _mm_xor_si128(s[1], LOAD(in + 16));
  s[2] = _mm_xor_si128(s[2], LOAD(in + 32));
  s[3] = _mm_xor_si128(s[3], LOAD(in + 48));

  TRUNCSTORE(out, s[0], s[1], s[2], s[3]);
}

void haraka512_4x(unsigned char *out, const unsigned char *in) {
  //ALIGN u128 s[4][4], tmp;
  u128 tmp;
  u128 t0,t1,t2,t3;
  u128 s00 = LOAD(in);
  u128 s01 = LOAD(in + 16);
  u128 s02 = LOAD(in + 32);
  u128 s03 = LOAD(in + 48);
  u128 s10 = LOAD(in + 64);
  u128 s11 = LOAD(in + 80);
  u128 s12 = LOAD(in + 96);
  u128 s13 = LOAD(in + 112);
  u128 s20 = LOAD(in + 128);
  u128 s21 = LOAD(in + 144);
  u128 s22 = LOAD(in + 160);
  u128 s23 = LOAD(in + 176);
  u128 s30 = LOAD(in + 192);
  u128 s31 = LOAD(in + 208);
  u128 s32 = LOAD(in + 224);
  u128 s33 = LOAD(in + 240);
    
  AES4_4x_my( 0);  MIX4_4x_my();
  AES4_4x_my( 8);  MIX4_4x_my();
  AES4_4x_my(16);  MIX4_4x_my();
  AES4_4x_my(24);  MIX4_4x_my();
  AES4_4x_my(32);  MIX4_4x_my();
  
  s00 = _mm_xor_si128(s00, LOAD(in));
  s01 = _mm_xor_si128(s01, LOAD(in + 16));
  s02 = _mm_xor_si128(s02, LOAD(in + 32));
  s03 = _mm_xor_si128(s03, LOAD(in + 48));
  s10 = _mm_xor_si128(s10, LOAD(in + 64));
  s11 = _mm_xor_si128(s11, LOAD(in + 80));
  s12 = _mm_xor_si128(s12, LOAD(in + 96));
  s13 = _mm_xor_si128(s13, LOAD(in + 112));
  s20 = _mm_xor_si128(s20, LOAD(in + 128));
  s21 = _mm_xor_si128(s21, LOAD(in + 144));
  s22 = _mm_xor_si128(s22, LOAD(in + 160));
  s23 = _mm_xor_si128(s23, LOAD(in + 176));
  s30 = _mm_xor_si128(s30, LOAD(in + 192));
  s31 = _mm_xor_si128(s31, LOAD(in + 208));
  s32 = _mm_xor_si128(s32, LOAD(in + 224));
  s33 = _mm_xor_si128(s33, LOAD(in + 240));

  TRUNCSTORE(out + 00, s00, s01, s02, s03);
  TRUNCSTORE(out + 32, s10, s11, s12, s13);
  TRUNCSTORE(out + 64, s20, s21, s22, s23);
  TRUNCSTORE(out + 96, s30, s31, s32, s33);
}

void haraka512_8x(unsigned char *out, const unsigned char *in) {
  // This is faster on Skylake, the code below is faster on Haswell.
//  haraka512_4x(out, in);
//  haraka512_4x(out + 128, in + 256);
//return;
//   u128 s[8][4];

    u128 tmp;
    u128 t0,t1,t2,t3;

   u128 s00 = LOAD(in);
   u128 s01 = LOAD(in + 16);
   u128 s02 = LOAD(in + 32);
   u128 s03 = LOAD(in + 48);
   u128 s10 = LOAD(in + 64);
   u128 s11 = LOAD(in + 80);
   u128 s12 = LOAD(in + 96);
   u128 s13 = LOAD(in + 112);
   u128 s20 = LOAD(in + 128);
   u128 s21 = LOAD(in + 144);
   u128 s22 = LOAD(in + 160);
   u128 s23 = LOAD(in + 176);
   u128 s30 = LOAD(in + 192);
   u128 s31 = LOAD(in + 208);
   u128 s32 = LOAD(in + 224);
   u128 s33 = LOAD(in + 240);
   u128 s40 = LOAD(in + 256);
   u128 s41 = LOAD(in + 272);
   u128 s42 = LOAD(in + 288);
   u128 s43 = LOAD(in + 304);
   u128 s50 = LOAD(in + 320);
   u128 s51 = LOAD(in + 336);
   u128 s52 = LOAD(in + 352);
   u128 s53 = LOAD(in + 368);
   u128 s60 = LOAD(in + 384);
   u128 s61 = LOAD(in + 400);
   u128 s62 = LOAD(in + 416);
   u128 s63 = LOAD(in + 432);
   u128 s70 = LOAD(in + 448);
   u128 s71 = LOAD(in + 464);
   u128 s72 = LOAD(in + 480);
   u128 s73 = LOAD(in + 496);

    int i=0;
    for(i=0;i<5;i++)
    {
        AES4_8x_my(8*i);
    }
//    AES4_8x_my(0);
//    MIX4(s00, s01, s02, s03);
//    MIX4(s10, s11, s12, s13);
//    MIX4(s20, s21, s22, s23);
//    MIX4(s30, s31, s32, s33);
//    MIX4(s40, s41, s42, s43);
//    MIX4(s50, s51, s52, s53);
//    MIX4(s60, s61, s62, s63);
//    MIX4(s70, s71, s72, s73);

//    AES4_8x_my(8);
//    MIX4(s00, s01, s02, s03);
//    MIX4(s10, s11, s12, s13);
//    MIX4(s20, s21, s22, s23);
//    MIX4(s30, s31, s32, s33);
//    MIX4(s40, s41, s42, s43);
//    MIX4(s50, s51, s52, s53);
//    MIX4(s60, s61, s62, s63);
//    MIX4(s70, s71, s72, s73);

//    AES4_8x_my(16);
//    MIX4(s00, s01, s02, s03);
//    MIX4(s10, s11, s12, s13);
//    MIX4(s20, s21, s22, s23);
//    MIX4(s30, s31, s32, s33);
//    MIX4(s40, s41, s42, s43);
//    MIX4(s50, s51, s52, s53);
//    MIX4(s60, s61, s62, s63);
//    MIX4(s70, s71, s72, s73);

//    AES4_8x_my(24);
//    MIX4(s00, s01, s02, s03);
//    MIX4(s10, s11, s12, s13);
//    MIX4(s20, s21, s22, s23);
//    MIX4(s30, s31, s32, s33);
//    MIX4(s40, s41, s42, s43);
//    MIX4(s50, s51, s52, s53);
//    MIX4(s60, s61, s62, s63);
//    MIX4(s70, s71, s72, s73);

//    AES4_8x_my(32);
//    MIX4(s00, s01, s02, s03);
//    MIX4(s10, s11, s12, s13);
//    MIX4(s20, s21, s22, s23);
//    MIX4(s30, s31, s32, s33);
//    MIX4(s40, s41, s42, s43);
//    MIX4(s50, s51, s52, s53);
//    MIX4(s60, s61, s62, s63);
//    MIX4(s70, s71, s72, s73);
/*
   AES4_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 8);
   MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
   MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
   MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
   MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);
   MIX4(s[4][0], s[4][1], s[4][2], s[4][3]);
   MIX4(s[5][0], s[5][1], s[5][2], s[5][3]);
   MIX4(s[6][0], s[6][1], s[6][2], s[6][3]);
   MIX4(s[7][0], s[7][1], s[7][2], s[7][3]);

   AES4_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 16);
   MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
   MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
   MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
   MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);
   MIX4(s[4][0], s[4][1], s[4][2], s[4][3]);
   MIX4(s[5][0], s[5][1], s[5][2], s[5][3]);
   MIX4(s[6][0], s[6][1], s[6][2], s[6][3]);
   MIX4(s[7][0], s[7][1], s[7][2], s[7][3]);

   AES4_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 24);
   MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
   MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
   MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
   MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);
   MIX4(s[4][0], s[4][1], s[4][2], s[4][3]);
   MIX4(s[5][0], s[5][1], s[5][2], s[5][3]);
   MIX4(s[6][0], s[6][1], s[6][2], s[6][3]);
   MIX4(s[7][0], s[7][1], s[7][2], s[7][3]);

   AES4_8x(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 32);
   MIX4(s[0][0], s[0][1], s[0][2], s[0][3]);
   MIX4(s[1][0], s[1][1], s[1][2], s[1][3]);
   MIX4(s[2][0], s[2][1], s[2][2], s[2][3]);
   MIX4(s[3][0], s[3][1], s[3][2], s[3][3]);
   MIX4(s[4][0], s[4][1], s[4][2], s[4][3]);
   MIX4(s[5][0], s[5][1], s[5][2], s[5][3]);
   MIX4(s[6][0], s[6][1], s[6][2], s[6][3]);
   MIX4(s[7][0], s[7][1], s[7][2], s[7][3]);
*/

   s00 = _mm_xor_si128(s00, LOAD(in));
   s01 = _mm_xor_si128(s01, LOAD(in + 16));
   s02 = _mm_xor_si128(s02, LOAD(in + 32));
   s03 = _mm_xor_si128(s03, LOAD(in + 48));
   s10 = _mm_xor_si128(s10, LOAD(in + 64));
   s11 = _mm_xor_si128(s11, LOAD(in + 80));
   s12 = _mm_xor_si128(s12, LOAD(in + 96));
   s13 = _mm_xor_si128(s13, LOAD(in + 112));
   s20 = _mm_xor_si128(s20, LOAD(in + 128));
   s21 = _mm_xor_si128(s21, LOAD(in + 144));
   s22 = _mm_xor_si128(s22, LOAD(in + 160));
   s23 = _mm_xor_si128(s23, LOAD(in + 176));
   s30 = _mm_xor_si128(s30, LOAD(in + 192));
   s31 = _mm_xor_si128(s31, LOAD(in + 208));
   s32 = _mm_xor_si128(s32, LOAD(in + 224));
   s33 = _mm_xor_si128(s33, LOAD(in + 240));
   s40 = _mm_xor_si128(s40, LOAD(in + 256));
   s41 = _mm_xor_si128(s41, LOAD(in + 272));
   s42 = _mm_xor_si128(s42, LOAD(in + 288));
   s43 = _mm_xor_si128(s43, LOAD(in + 304));
   s50 = _mm_xor_si128(s50, LOAD(in + 320));
   s51 = _mm_xor_si128(s51, LOAD(in + 336));
   s52 = _mm_xor_si128(s52, LOAD(in + 352));
   s53 = _mm_xor_si128(s53, LOAD(in + 368));
   s60 = _mm_xor_si128(s60, LOAD(in + 384));
   s61 = _mm_xor_si128(s61, LOAD(in + 400));
   s62 = _mm_xor_si128(s62, LOAD(in + 416));
   s63 = _mm_xor_si128(s63, LOAD(in + 432));
   s70 = _mm_xor_si128(s70, LOAD(in + 448));
   s71 = _mm_xor_si128(s71, LOAD(in + 464));
   s72 = _mm_xor_si128(s72, LOAD(in + 480));
   s73 = _mm_xor_si128(s73, LOAD(in + 496));

   TRUNCSTORE(out +   0, s00, s01, s02, s03);
   TRUNCSTORE(out +  32, s10, s11, s12, s13);
   TRUNCSTORE(out +  64, s20, s21, s22, s23);
   TRUNCSTORE(out +  96, s30, s31, s32, s33);
   TRUNCSTORE(out + 128, s40, s41, s42, s43);
   TRUNCSTORE(out + 160, s50, s51, s52, s53);
   TRUNCSTORE(out + 192, s60, s61, s62, s63);
   TRUNCSTORE(out + 224, s70, s71, s72, s73);
}
