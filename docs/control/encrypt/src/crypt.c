#include <sys/types.h> 
#include <sys/stat.h>

#ifdef _WINDOWS
#define _CRT_SECURE_NO_WARNINGS

#define FOPEN		fopen
#define FCLOSE		fclose
#define FREAD		fread
#define FWRITE		fwrite
#define FSEEK		_fseeki64
#define FTELL		ftell
#define FRENAME		rename
#define FSTAT		_stat64
#define T_FILE		FILE
#define T_STAT		__stat64 
#define STAT_SIZE   st_size
#define BIGALLOC(x)	malloc(x)
#define BIGFREE		free

#else

#define FOPEN		fopen
#define FCLOSE		fclose
#define FREAD		fread
#define FWRITE		fwrite
#define FSEEK		fseeko
#define FTELL		ftell
#define FRENAME		rename
#define FSTAT		stat
#define T_FILE		FILE
#define T_STAT		stat 
#define STAT_SIZE   st_size
#define BIGALLOC(x)	malloc(x)
#define BIGFREE		free

#endif

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ENABLE_AES 1

#ifdef ENABLE_AES


// Source : https://github.com/kokke/tiny-AES-c
// License: The Unlicense 

// #define the macros below to 1/0 to enable/disable the mode of operation.
//
// CBC enables AES encryption in CBC-mode of operation.
// CTR enables encryption in counter-mode.
// ECB enables the basic ECB 16-byte block algorithm. All can be enabled simultaneously.

// The #ifndef-guard allows it to be configured before #include'ing or at compile time.
#ifndef CBC
  #define CBC 1
#endif

#ifndef ECB
  #define ECB 1
#endif

#ifndef CTR
  #define CTR 1
#endif


#define AES128 1
//#define AES192 1
//#define AES256 1

#define AES_BLOCKLEN 16 //Block length in bytes AES is 128b block only

#if defined(AES256) && (AES256 == 1)
    #define AES_KEYLEN 32
    #define AES_keyExpSize 240
#elif defined(AES192) && (AES192 == 1)
    #define AES_KEYLEN 24
    #define AES_keyExpSize 208
#else
    #define AES_KEYLEN 16   // Key length in bytes
    #define AES_keyExpSize 176
#endif

struct AES_ctx
{
  uint8_t RoundKey[AES_keyExpSize];
#if (defined(CBC) && (CBC == 1)) || (defined(CTR) && (CTR == 1))
  uint8_t Iv[AES_BLOCKLEN];
#endif
};

void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key);
#if (defined(CBC) && (CBC == 1)) || (defined(CTR) && (CTR == 1))
void AES_init_ctx_iv(struct AES_ctx* ctx, const uint8_t* key, const uint8_t* iv);
void AES_ctx_set_iv(struct AES_ctx* ctx, const uint8_t* iv);
#endif

#if defined(ECB) && (ECB == 1)
// buffer size is exactly AES_BLOCKLEN bytes; 
// you need only AES_init_ctx as IV is not used in ECB 
// NB: ECB is considered insecure for most uses
void AES_ECB_encrypt(struct AES_ctx* ctx, const uint8_t* buf);
void AES_ECB_decrypt(struct AES_ctx* ctx, const uint8_t* buf);

#endif // #if defined(ECB) && (ECB == !)


#if defined(CBC) && (CBC == 1)
// buffer size MUST be mutile of AES_BLOCKLEN;
// Suggest https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
// NOTES: you need to set IV in ctx via AES_init_ctx_iv() or AES_ctx_set_iv()
//        no IV should ever be reused with the same key 
void AES_CBC_encrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);
void AES_CBC_decrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);

#endif // #if defined(CBC) && (CBC == 1)


#if defined(CTR) && (CTR == 1)

// Same function for encrypting as for decrypting. 
// IV is incremented for every block, and used after encryption as XOR-compliment for output
// Suggesting https://en.wikipedia.org/wiki/Padding_(cryptography)#PKCS7 for padding scheme
// NOTES: you need to set IV in ctx with AES_init_ctx_iv() or AES_ctx_set_iv()
//        no IV should ever be reused with the same key 
void AES_CTR_xcrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length);

#endif // #if defined(CTR) && (CTR == 1)




/*

This is an implementation of the AES algorithm, specifically ECB, CTR and CBC mode.
Block size can be chosen in aes.h - available choices are AES128, AES192, AES256.

The implementation is verified against the test vectors in:
  National Institute of Standards and Technology Special Publication 800-38A 2001 ED

ECB-AES128
----------

  plain-text:
    6bc1bee22e409f96e93d7e117393172a
    ae2d8a571e03ac9c9eb76fac45af8e51
    30c81c46a35ce411e5fbc1191a0a52ef
    f69f2445df4f9b17ad2b417be66c3710

  key:
    2b7e151628aed2a6abf7158809cf4f3c

  resulting cipher
    3ad77bb40d7a3660a89ecaf32466ef97 
    f5d3d58503b9699de785895a96fdbaaf 
    43b1cd7f598ece23881b00e3ed030688 
    7b0c785e27e8ad3f8223207104725dd4 


NOTE:   String length must be evenly divisible by 16byte (str_len % 16 == 0)
        You should pad the end of the string with zeros if this is not the case.
        For AES192/256 the key size is proportionally larger.

*/


/*****************************************************************************/
/* Includes:                                                                 */
/*****************************************************************************/
#include <stdint.h>
#include <string.h> // CBC mode, for memset
//#include "aes.h"

/*****************************************************************************/
/* Defines:                                                                  */
/*****************************************************************************/
// The number of columns comprising a state in AES. This is a constant in AES. Value=4
#define Nb 4

#if defined(AES256) && (AES256 == 1)
    #define Nk 8
    #define Nr 14
#elif defined(AES192) && (AES192 == 1)
    #define Nk 6
    #define Nr 12
#else
    #define Nk 4        // The number of 32 bit words in a key.
    #define Nr 10       // The number of rounds in AES Cipher.
#endif

// jcallan@github points out that declaring Multiply as a function 
// reduces code size considerably with the Keil ARM compiler.
// See this link for more information: https://github.com/kokke/tiny-AES-C/pull/3
#ifndef MULTIPLY_AS_A_FUNCTION
  #define MULTIPLY_AS_A_FUNCTION 0
#endif




/*****************************************************************************/
/* Private variables:                                                        */
/*****************************************************************************/
// state - array holding the intermediate results during decryption.
typedef uint8_t state_t[4][4];



// The lookup-tables are marked const so they can be placed in read-only storage instead of RAM
// The numbers below can be computed dynamically trading ROM for RAM - 
// This can be useful in (embedded) bootloader applications, where ROM is often limited.
static const uint8_t sbox[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

static const uint8_t rsbox[256] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

// The round constant word array, Rcon[i], contains the values given by 
// x to the power (i-1) being powers of x (x is denoted as {02}) in the field GF(2^8)
static const uint8_t Rcon[11] = {
  0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36 };

/*
 * Jordan Goulder points out in PR #12 (https://github.com/kokke/tiny-AES-C/pull/12),
 * that you can remove most of the elements in the Rcon array, because they are unused.
 *
 * From Wikipedia's article on the Rijndael key schedule @ https://en.wikipedia.org/wiki/Rijndael_key_schedule#Rcon
 * 
 * "Only the first some of these constants are actually used – up to rcon[10] for AES-128 (as 11 round keys are needed), 
 *  up to rcon[8] for AES-192, up to rcon[7] for AES-256. rcon[0] is not used in AES algorithm."
 */


/*****************************************************************************/
/* Private functions:                                                        */
/*****************************************************************************/
/*
static uint8_t getSBoxValue(uint8_t num)
{
  return sbox[num];
}
*/
#define getSBoxValue(num) (sbox[(num)])
/*
static uint8_t getSBoxInvert(uint8_t num)
{
  return rsbox[num];
}
*/
#define getSBoxInvert(num) (rsbox[(num)])

// This function produces Nb(Nr+1) round keys. The round keys are used in each round to decrypt the states. 
static void KeyExpansion(uint8_t* RoundKey, const uint8_t* Key)
{
  unsigned i, j, k;
  uint8_t tempa[4]; // Used for the column/row operations
  
  // The first round key is the key itself.
  for (i = 0; i < Nk; ++i)
  {
    RoundKey[(i * 4) + 0] = Key[(i * 4) + 0];
    RoundKey[(i * 4) + 1] = Key[(i * 4) + 1];
    RoundKey[(i * 4) + 2] = Key[(i * 4) + 2];
    RoundKey[(i * 4) + 3] = Key[(i * 4) + 3];
  }

  // All other round keys are found from the previous round keys.
  for (i = Nk; i < Nb * (Nr + 1); ++i)
  {
    {
      k = (i - 1) * 4;
      tempa[0]=RoundKey[k + 0];
      tempa[1]=RoundKey[k + 1];
      tempa[2]=RoundKey[k + 2];
      tempa[3]=RoundKey[k + 3];

    }

    if (i % Nk == 0)
    {
      // This function shifts the 4 bytes in a word to the left once.
      // [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

      // Function RotWord()
      {
        k = tempa[0];
        tempa[0] = tempa[1];
        tempa[1] = tempa[2];
        tempa[2] = tempa[3];
        tempa[3] = k;
      }

      // SubWord() is a function that takes a four-byte input word and 
      // applies the S-box to each of the four bytes to produce an output word.

      // Function Subword()
      {
        tempa[0] = getSBoxValue(tempa[0]);
        tempa[1] = getSBoxValue(tempa[1]);
        tempa[2] = getSBoxValue(tempa[2]);
        tempa[3] = getSBoxValue(tempa[3]);
      }

      tempa[0] = tempa[0] ^ Rcon[i/Nk];
    }
#if defined(AES256) && (AES256 == 1)
    if (i % Nk == 4)
    {
      // Function Subword()
      {
        tempa[0] = getSBoxValue(tempa[0]);
        tempa[1] = getSBoxValue(tempa[1]);
        tempa[2] = getSBoxValue(tempa[2]);
        tempa[3] = getSBoxValue(tempa[3]);
      }
    }
#endif
    j = i * 4; k=(i - Nk) * 4;
    RoundKey[j + 0] = RoundKey[k + 0] ^ tempa[0];
    RoundKey[j + 1] = RoundKey[k + 1] ^ tempa[1];
    RoundKey[j + 2] = RoundKey[k + 2] ^ tempa[2];
    RoundKey[j + 3] = RoundKey[k + 3] ^ tempa[3];
  }
}

void AES_init_ctx(struct AES_ctx* ctx, const uint8_t* key)
{
  KeyExpansion(ctx->RoundKey, key);
}
#if (defined(CBC) && (CBC == 1)) || (defined(CTR) && (CTR == 1))
void AES_init_ctx_iv(struct AES_ctx* ctx, const uint8_t* key, const uint8_t* iv)
{
  KeyExpansion(ctx->RoundKey, key);
  memcpy (ctx->Iv, iv, AES_BLOCKLEN);
}
void AES_ctx_set_iv(struct AES_ctx* ctx, const uint8_t* iv)
{
  memcpy (ctx->Iv, iv, AES_BLOCKLEN);
}
#endif

// This function adds the round key to state.
// The round key is added to the state by an XOR function.
static void AddRoundKey(uint8_t round,state_t* state,uint8_t* RoundKey)
{
  uint8_t i,j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      (*state)[i][j] ^= RoundKey[(round * Nb * 4) + (i * Nb) + j];
    }
  }
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
static void SubBytes(state_t* state)
{
  uint8_t i, j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      (*state)[j][i] = getSBoxValue((*state)[j][i]);
    }
  }
}

// The ShiftRows() function shifts the rows in the state to the left.
// Each row is shifted with different offset.
// Offset = Row number. So the first row is not shifted.
static void ShiftRows(state_t* state)
{
  uint8_t temp;

  // Rotate first row 1 columns to left  
  temp           = (*state)[0][1];
  (*state)[0][1] = (*state)[1][1];
  (*state)[1][1] = (*state)[2][1];
  (*state)[2][1] = (*state)[3][1];
  (*state)[3][1] = temp;

  // Rotate second row 2 columns to left  
  temp           = (*state)[0][2];
  (*state)[0][2] = (*state)[2][2];
  (*state)[2][2] = temp;

  temp           = (*state)[1][2];
  (*state)[1][2] = (*state)[3][2];
  (*state)[3][2] = temp;

  // Rotate third row 3 columns to left
  temp           = (*state)[0][3];
  (*state)[0][3] = (*state)[3][3];
  (*state)[3][3] = (*state)[2][3];
  (*state)[2][3] = (*state)[1][3];
  (*state)[1][3] = temp;
}

static uint8_t xtime(uint8_t x)
{
  return ((x<<1) ^ (((x>>7) & 1) * 0x1b));
}

// MixColumns function mixes the columns of the state matrix
static void MixColumns(state_t* state)
{
  uint8_t i;
  uint8_t Tmp, Tm, t;
  for (i = 0; i < 4; ++i)
  {  
    t   = (*state)[i][0];
    Tmp = (*state)[i][0] ^ (*state)[i][1] ^ (*state)[i][2] ^ (*state)[i][3] ;
    Tm  = (*state)[i][0] ^ (*state)[i][1] ; Tm = xtime(Tm);  (*state)[i][0] ^= Tm ^ Tmp ;
    Tm  = (*state)[i][1] ^ (*state)[i][2] ; Tm = xtime(Tm);  (*state)[i][1] ^= Tm ^ Tmp ;
    Tm  = (*state)[i][2] ^ (*state)[i][3] ; Tm = xtime(Tm);  (*state)[i][2] ^= Tm ^ Tmp ;
    Tm  = (*state)[i][3] ^ t ;              Tm = xtime(Tm);  (*state)[i][3] ^= Tm ^ Tmp ;
  }
}

// Multiply is used to multiply numbers in the field GF(2^8)
#if MULTIPLY_AS_A_FUNCTION
static uint8_t Multiply(uint8_t x, uint8_t y)
{
  return (((y & 1) * x) ^
       ((y>>1 & 1) * xtime(x)) ^
       ((y>>2 & 1) * xtime(xtime(x))) ^
       ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^
       ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))));
  }
#else
#define Multiply(x, y)                                \
      (  ((y & 1) * x) ^                              \
      ((y>>1 & 1) * xtime(x)) ^                       \
      ((y>>2 & 1) * xtime(xtime(x))) ^                \
      ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^         \
      ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))   \

#endif

// MixColumns function mixes the columns of the state matrix.
// The method used to multiply may be difficult to understand for the inexperienced.
// Please use the references to gain more information.
/*
static void InvMixColumns(state_t* state)
{
  int i;
  uint8_t a, b, c, d;
  for (i = 0; i < 4; ++i)
  { 
    a = (*state)[i][0];
    b = (*state)[i][1];
    c = (*state)[i][2];
    d = (*state)[i][3];

    (*state)[i][0] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
    (*state)[i][1] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
    (*state)[i][2] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
    (*state)[i][3] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
  }
}

// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
static void InvSubBytes(state_t* state)
{
  uint8_t i, j;
  for (i = 0; i < 4; ++i)
  {
    for (j = 0; j < 4; ++j)
    {
      (*state)[j][i] = getSBoxInvert((*state)[j][i]);
    }
  }
}

static void InvShiftRows(state_t* state)
{
  uint8_t temp;

  // Rotate first row 1 columns to right  
  temp = (*state)[3][1];
  (*state)[3][1] = (*state)[2][1];
  (*state)[2][1] = (*state)[1][1];
  (*state)[1][1] = (*state)[0][1];
  (*state)[0][1] = temp;

  // Rotate second row 2 columns to right 
  temp = (*state)[0][2];
  (*state)[0][2] = (*state)[2][2];
  (*state)[2][2] = temp;

  temp = (*state)[1][2];
  (*state)[1][2] = (*state)[3][2];
  (*state)[3][2] = temp;

  // Rotate third row 3 columns to right
  temp = (*state)[0][3];
  (*state)[0][3] = (*state)[1][3];
  (*state)[1][3] = (*state)[2][3];
  (*state)[2][3] = (*state)[3][3];
  (*state)[3][3] = temp;
}
*/

// Cipher is the main function that encrypts the PlainText.
static void Cipher(state_t* state, uint8_t* RoundKey)
{
  uint8_t round = 0;

  // Add the First round key to the state before starting the rounds.
  AddRoundKey(0, state, RoundKey); 
  
  // There will be Nr rounds.
  // The first Nr-1 rounds are identical.
  // These Nr-1 rounds are executed in the loop below.
  for (round = 1; round < Nr; ++round)
  {
    SubBytes(state);
    ShiftRows(state);
    MixColumns(state);
    AddRoundKey(round, state, RoundKey);
  }
  
  // The last round is given below.
  // The MixColumns function is not here in the last round.
  SubBytes(state);
  ShiftRows(state);
  AddRoundKey(Nr, state, RoundKey);
}

/*
static void InvCipher(state_t* state,uint8_t* RoundKey)
{
  uint8_t round = 0;

  // Add the First round key to the state before starting the rounds.
  AddRoundKey(Nr, state, RoundKey); 

  // There will be Nr rounds.
  // The first Nr-1 rounds are identical.
  // These Nr-1 rounds are executed in the loop below.
  for (round = (Nr - 1); round > 0; --round)
  {
    InvShiftRows(state);
    InvSubBytes(state);
    AddRoundKey(round, state, RoundKey);
    InvMixColumns(state);
  }
  
  // The last round is given below.
  // The MixColumns function is not here in the last round.
  InvShiftRows(state);
  InvSubBytes(state);
  AddRoundKey(0, state, RoundKey);
}
*/

/*****************************************************************************/
/* Public functions:                                                         */
/*****************************************************************************/
#if defined(ECB) && (ECB == 1)

/*
static void AES_ECB_encrypt(struct AES_ctx *ctx,const uint8_t* buf)
{
  // The next function call encrypts the PlainText with the Key using AES algorithm.
  Cipher((state_t*)buf, ctx->RoundKey);
}

static void AES_ECB_decrypt(struct AES_ctx* ctx,const uint8_t* buf)
{
  // The next function call decrypts the PlainText with the Key using AES algorithm.
  InvCipher((state_t*)buf, ctx->RoundKey);
}
*/

#endif // #if defined(ECB) && (ECB == 1)





#if defined(CBC) && (CBC == 1)

/*
static void XorWithIv(uint8_t* buf, uint8_t* Iv)
{
  uint8_t i;
  for (i = 0; i < AES_BLOCKLEN; ++i) // The block in AES is always 128bit no matter the key size
  {
    buf[i] ^= Iv[i];
  }
}

static void AES_CBC_encrypt_buffer(struct AES_ctx *ctx,uint8_t* buf, uint32_t length)
{
  uintptr_t i;
  uint8_t *Iv = ctx->Iv;
  for (i = 0; i < length; i += AES_BLOCKLEN)
  {
    XorWithIv(buf, Iv);
    Cipher((state_t*)buf, ctx->RoundKey);
    Iv = buf;
    buf += AES_BLOCKLEN;
    //printf("Step %d - %d", i/16, i);
  }
  // store Iv in ctx for next call 
  memcpy(ctx->Iv, Iv, AES_BLOCKLEN);
}

static void AES_CBC_decrypt_buffer(struct AES_ctx* ctx, uint8_t* buf,  uint32_t length)
{
  uintptr_t i;
  uint8_t storeNextIv[AES_BLOCKLEN];
  for (i = 0; i < length; i += AES_BLOCKLEN)
  {
    memcpy(storeNextIv, buf, AES_BLOCKLEN);
    InvCipher((state_t*)buf, ctx->RoundKey);
    XorWithIv(buf, ctx->Iv);
    memcpy(ctx->Iv, storeNextIv, AES_BLOCKLEN);
    buf += AES_BLOCKLEN;
  }
}
*/ 
#endif // #if defined(CBC) && (CBC == 1)



#if defined(CTR) && (CTR == 1)

/* Symmetrical operation: same function for encrypting as for decrypting. Note any IV/nonce should never be reused with the same key */
void AES_CTR_xcrypt_buffer(struct AES_ctx* ctx, uint8_t* buf, uint32_t length)
{
  uint8_t buffer[AES_BLOCKLEN];
  
  unsigned i;
  int bi;
  for (i = 0, bi = AES_BLOCKLEN; i < length; ++i, ++bi)
  {
    if (bi == AES_BLOCKLEN) // we need to regen xor compliment in buffer
    {
      
      memcpy(buffer, ctx->Iv, AES_BLOCKLEN);
      Cipher((state_t*)buffer,ctx->RoundKey);

      // Increment Iv and handle overflow 
      for (bi = (AES_BLOCKLEN - 1); bi >= 0; --bi)
      {
		//inc will owerflow 
        if (ctx->Iv[bi] == 255)
		{
          ctx->Iv[bi] = 0;
          continue;
        } 
        ctx->Iv[bi] += 1;
        break;   
      }
      bi = 0;
    }

    buf[i] = (buf[i] ^ buffer[bi]);
  }
}

#endif // #if defined(CTR) && (CTR == 1)





#endif 



extern uint8_t g_seckey[16];
extern uint8_t g_dekey[16];

typedef struct media_header
{
	uint8_t version_flags[4];
	uint32_t creation_time;
	uint32_t modification_time;
	uint32_t time_scale;
	uint32_t duration;
	uint16_t language;
	uint16_t quality;
} media_header;


typedef struct SampleToChunk
{
	uint32_t chunk_num;
	uint32_t samples;
	uint32_t id;
} SampleToChunk;


#define MAX_TRACKS	16
typedef struct mp4object
{
	uint32_t *metasizes;
	uint32_t metasize_count;
	uint64_t *metaoffsets;
	uint32_t metastco_count;
	SampleToChunk *metastsc;
	uint32_t metastsc_count;
	uint32_t indexcount;
	double videolength;
	double metadatalength;
	int32_t metadataoffset_clockcount;
	uint32_t clockdemon, clockcount;
	uint32_t trak_clockdemon, trak_clockcount;
	uint32_t meta_clockdemon, meta_clockcount;
	uint32_t video_framerate_numerator;
	uint32_t video_framerate_denominator;
	uint32_t video_frames;
	double basemetadataduration;
	int32_t trak_edit_list_offsets[MAX_TRACKS];
	uint32_t trak_num;
	T_FILE *mediafp;
	uint64_t filesize;
	uint64_t filepos;
} mp4object;

#define MAKEID(a,b,c,d)			(((d&0xff)<<24)|((c&0xff)<<16)|((b&0xff)<<8)|(a&0xff))
#define STR2FOURCC(s)			((s[0]<<0)|(s[1]<<8)|(s[2]<<16)|(s[3]<<24))

#define BYTESWAP64(a)			(((a&0xff)<<56)|((a&0xff00)<<40)|((a&0xff0000)<<24)|((a&0xff000000)<<8) | ((a>>56)&0xff)|((a>>40)&0xff00)|((a>>24)&0xff0000)|((a>>8)&0xff000000) )
#define BYTESWAP32(a)			(((a&0xff)<<24)|((a&0xff00)<<8)|((a>>8)&0xff00)|((a>>24)&0xff))
#define BYTESWAP16(a)			((((a)>>8)&0xff)|(((a)<<8)&0xff00))
#define NOSWAP8(a)				(a)

#define MOV_VIDE_TRAK_TYPE		MAKEID('v', 'i', 'd', 'e')		// MP4 track for video
#define MOV_SOUN_TRAK_TYPE		MAKEID('s', 'o', 'u', 'n')		// MP4 track for audio
#define MOV_AVC1_SUBTYPE		MAKEID('a', 'v', 'c', '1')		// subtype H264
#define MOV_HVC1_SUBTYPE		MAKEID('h', 'v', 'c', '1')		// subtype H265
#define MOV_MP4A_SUBTYPE		MAKEID('m', 'p', '4', 'a')		// subtype for audio
#define MOV_CFHD_SUBTYPE		MAKEID('C', 'F', 'H', 'D')		// subtype is CineForm HD
#define AVI_VIDS_TRAK_TYPE		MAKEID('v', 'i', 'd', 's')		// track is the type for video
#define AVI_CFHD_SUBTYPE		MAKEID('c', 'f', 'h', 'd')		// subtype is CineForm HD

#define NESTSIZE(x) { int i = nest; while (i > 0 && nestsize[i] > 0) { nestsize[i] -= x; if(nestsize[i]>=0 && nestsize[i] <= 8) { nestsize[i]=0; nest--; } i--; } }

#define VALID_FOURCC(a)	(((((a>>24)&0xff)>='a'&&((a>>24)&0xff)<='z') || (((a>>24)&0xff)>='A'&&((a>>24)&0xff)<='Z') || (((a>>24)&0xff)>='0'&&((a>>24)&0xff)<='9') || (((a>>24)&0xff)==' ') ) && \
						( (((a>>16)&0xff)>='a'&&((a>>24)&0xff)<='z') || (((a>>16)&0xff)>='A'&&((a>>16)&0xff)<='Z') || (((a>>16)&0xff)>='0'&&((a>>16)&0xff)<='9') || (((a>>16)&0xff)==' ') ) && \
						( (((a>>8)&0xff)>='a'&&((a>>24)&0xff)<='z') || (((a>>8)&0xff)>='A'&&((a>>8)&0xff)<='Z') || (((a>>8)&0xff)>='0'&&((a>>8)&0xff)<='9') || (((a>>8)&0xff)==' ') ) && \
						( (((a>>0)&0xff)>='a'&&((a>>24)&0xff)<='z') || (((a>>0)&0xff)>='A'&&((a>>0)&0xff)<='Z') || (((a>>0)&0xff)>='0'&&((a>>0)&0xff)<='9') || (((a>>0)&0xff)==' ') )) 



static uint32_t GetNumberPayloads(size_t handle)
{
	mp4object *mp4 = (mp4object *)handle;

	if (mp4)
	{
		return mp4->indexcount;
	}

	return 0;
}


static uint32_t *GetPayload(size_t handle, uint32_t *lastpayload, uint32_t index)
{
	mp4object *mp4 = (mp4object *)handle;
	if (mp4 == NULL) return NULL;

	uint32_t *MP4buffer = NULL;
	if (index < mp4->indexcount && mp4->mediafp)
	{
		if (lastpayload == NULL)
		{
			uint32_t maxsize = 0;
			for (uint32_t i = 0; i < mp4->indexcount; i++)
				if (mp4->metasizes[i] > maxsize)
					maxsize = mp4->metasizes[i];

			if (maxsize)
				MP4buffer = (uint32_t*)BIGALLOC(maxsize);
		}
		else
			MP4buffer = lastpayload;

		if (MP4buffer)
		{
			FSEEK(mp4->mediafp, mp4->metaoffsets[index], SEEK_SET);
			FREAD(MP4buffer, 1, mp4->metasizes[index], mp4->mediafp);
			return MP4buffer;
		}
	}
	return NULL;
}


static void SavePayload(size_t handle, uint32_t *payload, uint32_t index)
{
	mp4object *mp4 = (mp4object *)handle;
	if (mp4 == NULL) return;

	if (index < mp4->indexcount && mp4->mediafp && payload)
	{
		FSEEK(mp4->mediafp, mp4->metaoffsets[index], SEEK_SET);
		FWRITE(payload, 1, mp4->metasizes[index], mp4->mediafp);
	}
	return;
}



static void FreePayload(uint32_t *lastpayload)
{
	if (lastpayload)
		BIGFREE(lastpayload);
}


static uint32_t GetPayloadSize(size_t handle, uint32_t index)
{
	mp4object *mp4 = (mp4object *)handle;
	if (mp4 == NULL) return 0;

	if (mp4->metasizes && mp4->metasize_count > index)
		return mp4->metasizes[index];

	return 0;
}



static void CloseSource(size_t handle)
{
	mp4object *mp4 = (mp4object *)handle;
	if (mp4 == NULL) return;

	if (mp4->mediafp) FCLOSE(mp4->mediafp), mp4->mediafp = NULL;
	if (mp4->metasizes) free(mp4->metasizes), mp4->metasizes = 0;
	if (mp4->metaoffsets) free(mp4->metaoffsets), mp4->metaoffsets = 0;

	free(mp4);
}

#define MAX_NEST_LEVEL	20

void LongSeek(mp4object *mp4, int64_t offset)
{
	if (mp4 && offset)
	{
		if (mp4->filepos + offset < mp4->filesize)
		{
			FSEEK(mp4->mediafp, offset, SEEK_CUR);  //TODO fix offset for 64-bit on camera
			mp4->filepos += offset;
		}
		else
		{
			mp4->filepos = mp4->filesize;
		}
	}
}


static size_t OpenMP4Source(char *filename, uint32_t traktype, uint32_t traksubtype, int channel, uint64_t filesize)  //RAW or within MP4
{
	mp4object *mp4 = (mp4object *)malloc(sizeof(mp4object));
	if (mp4 == NULL) return 0;

	memset(mp4, 0, sizeof(mp4object));

	mp4->mediafp = FOPEN(filename, "rb+");
	mp4->filesize = (uint64_t)filesize; 

	if (mp4->mediafp)
	{
		uint32_t qttag, qtsize32, skip, type = 0, subtype = 0, num;
		size_t len;
		int32_t nest = 0;
		uint64_t nestsize[MAX_NEST_LEVEL] = { 0 };
		uint64_t qtsize;
		int moovfound = 0;
		int chn = 0;

		do
		{
			len = FREAD(&qtsize32, 1, 4, mp4->mediafp);
			len += FREAD(&qttag, 1, 4, mp4->mediafp);
			mp4->filepos += len;
			if (len == 8 && mp4->filepos < mp4->filesize)
			{
				if (mp4->filepos == 8 && qttag != MAKEID('f', 't', 'y', 'p'))
				{
					CloseSource((size_t)mp4);
					mp4 = NULL;
					break;
				}
				
				if (!VALID_FOURCC(qttag) && (qttag & 0xff) != 0xa9) // ©xyz and ©swr are allowed
				{
					if (moovfound == 1 && nest == 0) //read beyond the moov atom
						break;

					CloseSource((size_t)mp4);
					mp4 = NULL;
					break;
				}

				qtsize32 = BYTESWAP32(qtsize32);

				if (qtsize32 == 1) // 64-bit Atom
				{
					len = FREAD(&qtsize, 1, 8, mp4->mediafp);
					mp4->filepos += len;
					qtsize = BYTESWAP64(qtsize) - 8;
				}
				else
					qtsize = qtsize32;

				if(qtsize-len > (mp4->filesize - mp4->filepos))  // not parser truncated files.
				{
					CloseSource((size_t)mp4);
					mp4 = NULL;
					break;
				}
				
				nest++;
				
				if (qtsize < 8) break;
				if (nest >= MAX_NEST_LEVEL) break;
				if (nest > 1 && qtsize > nestsize[nest - 1]) break;

				nestsize[nest] = qtsize;

				if (qttag != MAKEID('m', 'o', 'o', 'v') && //skip over all but these atoms
					qttag != MAKEID('m', 'v', 'h', 'd') &&
					qttag != MAKEID('t', 'r', 'a', 'k') &&
					qttag != MAKEID('m', 'd', 'i', 'a') &&
					qttag != MAKEID('m', 'd', 'h', 'd') &&
					qttag != MAKEID('m', 'i', 'n', 'f') &&
					qttag != MAKEID('g', 'm', 'i', 'n') &&
					qttag != MAKEID('d', 'i', 'n', 'f') &&
					qttag != MAKEID('a', 'l', 'i', 's') &&
					qttag != MAKEID('s', 't', 's', 'd') &&
					qttag != MAKEID('a', 'l', 'i', 's') &&
					qttag != MAKEID('s', 't', 'b', 'l') &&
					qttag != MAKEID('s', 't', 't', 's') &&
					qttag != MAKEID('s', 't', 's', 'c') &&
					qttag != MAKEID('s', 't', 's', 'z') &&
					qttag != MAKEID('s', 't', 'c', 'o') &&
					qttag != MAKEID('c', 'o', '6', '4') &&
					qttag != MAKEID('h', 'd', 'l', 'r'))
				{
					LongSeek(mp4, qtsize - 8);

					NESTSIZE(qtsize);
				}
				else
				{
					if (qttag == MAKEID('m', 'o', 'o', 'v')) //trak header
					{
						moovfound = 1;
						NESTSIZE(8);
					}
					else if (qttag == MAKEID('m', 'v', 'h', 'd')) //mvhd  movie header
					{
						len = FREAD(&skip, 1, 4, mp4->mediafp);
						len += FREAD(&skip, 1, 4, mp4->mediafp);
						len += FREAD(&skip, 1, 4, mp4->mediafp);
						len += FREAD(&mp4->clockdemon, 1, 4, mp4->mediafp); mp4->clockdemon = BYTESWAP32(mp4->clockdemon);
						len += FREAD(&mp4->clockcount, 1, 4, mp4->mediafp); mp4->clockcount = BYTESWAP32(mp4->clockcount);

						mp4->filepos += len;
						LongSeek(mp4, qtsize - 8 - len); // skip over mvhd

						NESTSIZE(qtsize);
					}
					else if (qttag == MAKEID('t', 'r', 'a', 'k')) //trak header
					{

						if (mp4->trak_num+1 < MAX_TRACKS)
							mp4->trak_num++;

						NESTSIZE(8);
					}
					else if (qttag == MAKEID('m', 'd', 'h', 'd')) //mdhd  media header
					{
						media_header md;
						len = FREAD(&md, 1, sizeof(md), mp4->mediafp);
						if (len == sizeof(md))
						{
							md.creation_time = BYTESWAP32(md.creation_time);
							md.modification_time = BYTESWAP32(md.modification_time);
							md.time_scale = BYTESWAP32(md.time_scale);
							md.duration = BYTESWAP32(md.duration);

							mp4->trak_clockdemon = md.time_scale;
							mp4->trak_clockcount = md.duration;

							if (mp4->trak_clockdemon == 0 || mp4->trak_clockcount == 0)
							{
								CloseSource((size_t)mp4);
								mp4 = NULL;
								break;
							}

							if (mp4->videolength == 0.0) // Get the video length from the first track
							{
								mp4->videolength = (float)((double)mp4->trak_clockcount / (double)mp4->trak_clockdemon);
							}
						}

						mp4->filepos += len;
						LongSeek(mp4, qtsize - 8 - len); // skip over mvhd

						NESTSIZE(qtsize);
					}
					else if (qttag == MAKEID('h', 'd', 'l', 'r')) //hldr
					{
						uint32_t temp;
						len = FREAD(&skip, 1, 4, mp4->mediafp);
						len += FREAD(&skip, 1, 4, mp4->mediafp);
						len += FREAD(&temp, 1, 4, mp4->mediafp);  // type will be 'meta' for the correct trak.

						if (temp != MAKEID('a', 'l', 'i', 's') && temp != MAKEID('u', 'r', 'l', ' '))
							type = temp;

						mp4->filepos += len;
						LongSeek(mp4, qtsize - 8 - len); // skip over hldr

						NESTSIZE(qtsize);

					}
					else if (qttag == MAKEID('e', 'd', 't', 's')) //edit list
					{
						uint32_t elst,temp,readnum,i;
						len = FREAD(&skip, 1, 4, mp4->mediafp);
						len += FREAD(&elst, 1, 4, mp4->mediafp);
						if (elst == MAKEID('e', 'l', 's', 't'))
						{
							len += FREAD(&temp, 1, 4, mp4->mediafp);
							if (temp == 0)
							{
								len += FREAD(&readnum, 1, 4, mp4->mediafp);
								readnum = BYTESWAP32(readnum);
								if (readnum <= (qtsize / 12) && mp4->trak_clockdemon)
								{
									uint32_t segment_duration; //integer that specifies the duration of this edit segment in units of the movie's time scale.
									uint32_t segment_mediaTime; //integer containing the starting time within the media of this edit segment(in media timescale units).If this field is set to 1, it is an empty edit.The last edit in a track should never be an empty edit.Any difference between the movie's duration and the track's duration is expressed as an implicit empty edit.
									uint32_t segment_mediaRate; //point number that specifies the relative rate at which to play the media corresponding to this edit segment.This rate value cannot be 0 or negative.
									for (i = 0; i < readnum; i++)
									{
										len += FREAD(&segment_duration, 1, 4, mp4->mediafp);
										len += FREAD(&segment_mediaTime, 1, 4, mp4->mediafp);
										len += FREAD(&segment_mediaRate, 1, 4, mp4->mediafp);

										segment_duration = BYTESWAP32(segment_duration);  // in MP4 clock base
										segment_mediaTime = BYTESWAP32(segment_mediaTime); // in trak clock base
										segment_mediaRate = BYTESWAP32(segment_mediaRate); // Fixed-point 65536 = 1.0X

										if (segment_mediaTime == 0xffffffff) // the segment_duration for blanked time
											mp4->trak_edit_list_offsets[mp4->trak_num] += (int32_t)segment_duration;  //samples are delay, data starts after presentation time zero.
										else if (i == 0) // If the first editlst starts after zero, the track is offset by this time (time before presentation time zero.)
											mp4->trak_edit_list_offsets[mp4->trak_num] -= (int32_t)((double)segment_mediaTime/(double)mp4->trak_clockdemon*(double)mp4->clockdemon); //convert to MP4 clock base.
									}
									if (type == traktype) // GPMF metadata 
									{
										mp4->metadataoffset_clockcount = mp4->trak_edit_list_offsets[mp4->trak_num]; //leave in MP4 clock base
									}
								}
							}
						}
						mp4->filepos += len;
						LongSeek(mp4, qtsize - 8 - len); // skip over edts

						NESTSIZE(qtsize);
					}
					else if (qttag == MAKEID('s', 't', 's', 'd')) //read the sample decription to determine the type of metadata
					{
						if (type == traktype) //like meta
						{
							len = FREAD(&skip, 1, 4, mp4->mediafp);
							len += FREAD(&skip, 1, 4, mp4->mediafp);
							len += FREAD(&skip, 1, 4, mp4->mediafp);
							len += FREAD(&subtype, 1, 4, mp4->mediafp);  // type will be 'meta' for the correct trak.
							if (len == 16)
							{
								if (subtype != traksubtype) // not MP4 metadata 
								{
									type = 0; // MP4
								}
								else if(chn != channel)
								{
									type = 0; 
								}
								chn++;
							}
							mp4->filepos += len;
							LongSeek(mp4, qtsize - 8 - len); // skip over stsd
						}
						else
							LongSeek(mp4, qtsize - 8);

						NESTSIZE(qtsize);
					}
					else if (qttag == MAKEID('s', 't', 's', 'c')) // metadata stsc - offset chunks
					{
						if (type == traktype) // meta
						{
							len = FREAD(&skip, 1, 4, mp4->mediafp);
							len += FREAD(&num, 1, 4, mp4->mediafp);

							num = BYTESWAP32(num);
							if (num <= (qtsize/sizeof(SampleToChunk)))
							{
								mp4->metastsc_count = num;
								if (mp4->metastsc)
								{
									free(mp4->metastsc);
									mp4->metastsc = 0;
								}
								if (num > 0 && qtsize > (num * sizeof(SampleToChunk)))
								{
									mp4->metastsc = (SampleToChunk *)malloc(num * sizeof(SampleToChunk));
									if (mp4->metastsc)
									{
										len += FREAD(mp4->metastsc, 1, num * sizeof(SampleToChunk), mp4->mediafp);

										do
										{
											num--;
											mp4->metastsc[num].chunk_num = BYTESWAP32(mp4->metastsc[num].chunk_num);
											mp4->metastsc[num].samples = BYTESWAP32(mp4->metastsc[num].samples);
											mp4->metastsc[num].id = BYTESWAP32(mp4->metastsc[num].id);
										} while (num > 0);
									}
								}
								else
								{
									//size of null
									CloseSource((size_t)mp4);
									mp4 = NULL;
									break;
								}
							}
							mp4->filepos += len;
							LongSeek(mp4, qtsize - 8 - len); // skip over stsx
						}
						else
							LongSeek(mp4, qtsize - 8);

						NESTSIZE(qtsize);
					}
					else if (qttag == MAKEID('s', 't', 's', 'z')) // metadata stsz - sizes
					{
						if (type == traktype) // meta
						{
							uint32_t equalsamplesize;

							len = FREAD(&skip, 1, 4, mp4->mediafp);
							len += FREAD(&equalsamplesize, 1, 4, mp4->mediafp);
							len += FREAD(&num, 1, 4, mp4->mediafp);

							num = BYTESWAP32(num);
							// if equalsamplesize != 0, it is the size of all the samples and the length should be 20 (size,fourcc,flags,samplesize,samplecount)
                            if (qtsize >= (20 + (num * sizeof(uint32_t))) || (equalsamplesize != 0 && qtsize == 20))
							{
								if (mp4->metasizes)
								{
									free(mp4->metasizes);
									mp4->metasizes = 0;
								}
								//either the samples are different sizes or they are all the same size
								if(num > 0)
								{
									mp4->metasize_count = num;
									mp4->metasizes = (uint32_t *)malloc(num * 4);
									if (mp4->metasizes)
									{
										if (equalsamplesize == 0)
										{
											len += FREAD(mp4->metasizes, 1, num * 4, mp4->mediafp);
											do
											{
												num--;
												mp4->metasizes[num] = BYTESWAP32(mp4->metasizes[num]);
											} while (num > 0);
										}
										else
										{
											equalsamplesize = BYTESWAP32(equalsamplesize);
											do
											{
												num--;
												mp4->metasizes[num] = equalsamplesize;
											} while (num > 0);
										}
									}
								}
								else
								{
									//size of null
									CloseSource((size_t)mp4);
									mp4 = NULL;
									break;
								}
							}
							mp4->filepos += len;
							LongSeek(mp4, qtsize - 8 - len); // skip over stsz
						}
						else
							LongSeek(mp4, qtsize - 8);

						NESTSIZE(qtsize);
					}
					else if (qttag == MAKEID('s', 't', 'c', 'o')) // metadata stco - offsets
					{
						if (type == traktype) // meta
						{

							len = FREAD(&skip, 1, 4, mp4->mediafp);
							len += FREAD(&num, 1, 4, mp4->mediafp);
							num = BYTESWAP32(num);
							if (num <= ((qtsize - 8 - len) / sizeof(uint32_t)))
							{
								mp4->metastco_count = num;

								if (mp4->metastsc_count > 0 && num != mp4->metasize_count)
								{
									if (mp4->metaoffsets)
									{
										free(mp4->metaoffsets);
										mp4->metaoffsets = 0;
									}
									if (mp4->metastco_count && qtsize > (num * 4))
									{
										mp4->metaoffsets = (uint64_t*)malloc(mp4->metasize_count * 8);
										if (mp4->metaoffsets)
										{
											uint32_t* metaoffsets32 = NULL;
											metaoffsets32 = (uint32_t*)malloc(num * 4);
											if (metaoffsets32)
											{
												uint64_t fileoffset = 0;
												int stsc_pos = 0;
												int stco_pos = 0;
												len += FREAD(metaoffsets32, 1, num * 4, mp4->mediafp);
												do
												{
													num--;
													metaoffsets32[num] = BYTESWAP32(metaoffsets32[num]);
												} while (num > 0);

												fileoffset = metaoffsets32[stco_pos];
												mp4->metaoffsets[0] = fileoffset;

												num = 1;
												while (num < mp4->metasize_count)
												{
													if (num != mp4->metastsc[stsc_pos].chunk_num - 1 && 0 == (num - (mp4->metastsc[stsc_pos].chunk_num - 1)) % mp4->metastsc[stsc_pos].samples)
													{
														stco_pos++;
														fileoffset = (uint64_t)metaoffsets32[stco_pos];
													}
													else
													{
														fileoffset += (uint64_t)mp4->metasizes[num - 1];
													}

													mp4->metaoffsets[num] = fileoffset;
													//int delta = metaoffsets[num] - metaoffsets[num - 1];
													//printf("%3d:%08x, delta = %08x\n", num, (int)fileoffset, delta);

													num++;
												}

												if (mp4->metastsc) free(mp4->metastsc);
												mp4->metastsc = NULL;
												mp4->metastsc_count = 0;

												free(metaoffsets32);
											}
										}
									}
									else
									{
										//size of null
										CloseSource((size_t)mp4);
										mp4 = NULL;
										break;
									}
								}
								else
								{
									if (mp4->metaoffsets)
									{
										free(mp4->metaoffsets);
										mp4->metaoffsets = 0;
									}
									if (num > 0 && mp4->metasize_count && mp4->metasizes && qtsize > (num*4))
									{
										mp4->metaoffsets = (uint64_t*)malloc(num * 8);
										if (mp4->metaoffsets)
										{
											uint32_t* metaoffsets32 = NULL;
											metaoffsets32 = (uint32_t*)malloc(num * 4);
											if (metaoffsets32)
											{
												size_t readlen = FREAD(metaoffsets32, 1, num * 4, mp4->mediafp);
												len += readlen;
												do
												{
													num--;
													mp4->metaoffsets[num] = BYTESWAP32(metaoffsets32[num]);
												} while (num > 0);

												free(metaoffsets32);
											}
										}
									}
									else
									{
										//size of null
										CloseSource((size_t)mp4);
										mp4 = NULL;
										break;
									}
								}
							}
							mp4->filepos += len;
							LongSeek(mp4, qtsize - 8 - len); // skip over stco
						}
						else
							LongSeek(mp4, qtsize - 8);

						NESTSIZE(qtsize);
					}
					else if (qttag == MAKEID('c', 'o', '6', '4')) // metadata stco - offsets
					{
						if (type == traktype) // meta
						{
							len = FREAD(&skip, 1, 4, mp4->mediafp);
							len += FREAD(&num, 1, 4, mp4->mediafp);
							num = BYTESWAP32(num);

							if(num == 0)
							{
								//size of null
								CloseSource((size_t)mp4);
								mp4 = NULL;
								break;
							}

							if (num <= ((qtsize - 8 - len) / sizeof(uint64_t)))
							{
								mp4->metastco_count = num;

								if (mp4->metastsc_count > 0 && num != mp4->metasize_count)
								{
									if (mp4->metaoffsets)
									{
										free(mp4->metaoffsets);
										mp4->metaoffsets = 0;
									}
									if (mp4->metasize_count && mp4->metasizes && qtsize > (num*8))
									{
										mp4->metaoffsets = (uint64_t*)malloc(mp4->metasize_count * 8);
										if (mp4->metaoffsets)
										{
											uint64_t* metaoffsets64 = NULL;
											metaoffsets64 = (uint64_t*)malloc(num * 8);
											if (metaoffsets64)
											{
												uint64_t fileoffset = 0;
												int stsc_pos = 0;
												int stco_pos = 0;
												len += FREAD(metaoffsets64, 1, num * 8, mp4->mediafp);
												do
												{
													num--;
													metaoffsets64[num] = BYTESWAP64(metaoffsets64[num]);
												} while (num > 0);

												fileoffset = metaoffsets64[0];
												mp4->metaoffsets[0] = fileoffset;

												num = 1;
												while (num < mp4->metasize_count)
												{
													if (num != mp4->metastsc[stsc_pos].chunk_num - 1 && 0 == (num - (mp4->metastsc[stsc_pos].chunk_num - 1)) % mp4->metastsc[stsc_pos].samples)
													{
														stco_pos++;
														fileoffset = (uint64_t)metaoffsets64[stco_pos];
													}
													else
													{
														fileoffset += (uint64_t)mp4->metasizes[num - 1];
													}

													mp4->metaoffsets[num] = fileoffset;
													//int delta = metaoffsets[num] - metaoffsets[num - 1];
													//printf("%3d:%08x, delta = %08x\n", num, (int)fileoffset, delta);

													num++;
												}

												if (mp4->metastsc) free(mp4->metastsc);
												mp4->metastsc = NULL;
												mp4->metastsc_count = 0;

												free(metaoffsets64);
											}
										}
									}
									else
									{
										//size of null
										CloseSource((size_t)mp4);
										mp4 = NULL;
										break;
									}
								}
								else
								{
									if (mp4->metaoffsets)
									{
										free(mp4->metaoffsets);
										mp4->metaoffsets = 0;
									}
									if (num > 0 && mp4->metasize_count && mp4->metasizes && qtsize > (num*8))
									{
										mp4->metaoffsets = (uint64_t*)malloc(num * 8);
										if (mp4->metaoffsets)
										{
											len += FREAD(mp4->metaoffsets, 1, num * 8, mp4->mediafp);
											do
											{
												num--;
												mp4->metaoffsets[num] = BYTESWAP64(mp4->metaoffsets[num]);
											} while (num > 0);
										}
									}
								}
							}
							mp4->filepos += len;
							LongSeek(mp4, qtsize - 8 - len); // skip over stco
						}
						else
							LongSeek(mp4, qtsize - 8);

						NESTSIZE(qtsize);
					}
					else if (qttag == MAKEID('s', 't', 't', 's')) // time to samples
					{
						if (type == traktype || type == MAKEID('v','i','d','e')) // meta 
						{
							uint32_t totaldur = 0, samples = 0;
							uint32_t entries = 0;
							len = FREAD(&skip, 1, 4, mp4->mediafp);
							len += FREAD(&num, 1, 4, mp4->mediafp);
							num = BYTESWAP32(num);
							if (num <= (qtsize / 8))
							{
								entries = num;

								if (type == traktype)
								{
									mp4->meta_clockdemon = mp4->trak_clockdemon;
									mp4->meta_clockcount = mp4->trak_clockcount;

									if (mp4->meta_clockdemon == 0)
									{
										//prevent divide by zero
										CloseSource((size_t)mp4);
										mp4 = NULL;
										break;
									}
								}

								while (entries > 0)
								{
									uint32_t samplecount;
									uint32_t duration;
									len += FREAD(&samplecount, 1, 4, mp4->mediafp);
									samplecount = BYTESWAP32(samplecount);
									len += FREAD(&duration, 1, 4, mp4->mediafp);
									duration = BYTESWAP32(duration);

									samples += samplecount;
									entries--;

									if (type == MAKEID('v','i','d','e') && mp4->video_framerate_numerator == 0)
									{
										mp4->video_framerate_numerator = mp4->trak_clockdemon;
										mp4->video_framerate_denominator = duration;
									}

									if (type == traktype)
									{
										totaldur += duration;

										mp4->metadatalength += (double)((double)samplecount * (double)duration / (double)mp4->meta_clockdemon);
										if (samplecount > 1 || num == 1)
											mp4->basemetadataduration = mp4->metadatalength * (double)mp4->meta_clockdemon / (double)samples;
									}
								}
								if(type == MAKEID('v', 'i', 'd', 'e'))
									mp4->video_frames = samples;
							}
							mp4->filepos += len;
							LongSeek(mp4, qtsize - 8 - len); // skip over stts
						}
						else
							LongSeek(mp4, qtsize - 8);

						NESTSIZE(qtsize);
					}
					else
					{
						NESTSIZE(8);
					}
				}
			}
			else
			{
				break;
			}
		} while (len > 0);
		
		
		if (mp4)
		{
			if (mp4->metasizes == NULL || mp4->metaoffsets == NULL)
			{
				CloseSource((size_t)mp4);
				mp4 = NULL;
			}
			
			// set the numbers of payload with both size and offset
			if (mp4 != NULL)
			{
				mp4->indexcount = mp4->metasize_count;
			}
		}
	}
	else
	{	
		free(mp4);
		mp4 = NULL;
	}

	return (size_t)mp4;
}


static float GetDuration(size_t handle)
{
	mp4object *mp4 = (mp4object *)handle;
	if (mp4 == NULL) return 0.0;

	return (float)mp4->metadatalength;
}

/*
static uint32_t GetPayloadTime(size_t handle, uint32_t index, float *in, float *out)
{
	mp4object *mp4 = (mp4object *)handle;
	if (mp4 == NULL) return 0;

	if (mp4->metaoffsets == 0 || mp4->basemetadataduration == 0 || mp4->meta_clockdemon == 0 || in == NULL || out == NULL) return 1;

	*in = (float)((double)index * (double)mp4->basemetadataduration / (double)mp4->meta_clockdemon);
	*out = (float)((double)(index + 1) * (double)mp4->basemetadataduration / (double)mp4->meta_clockdemon);
	return 0;
}
*/




#define CRYPTBUF 65536
static uint8_t buff[CRYPTBUF];
static uint32_t pos = 0;

void crypt_chunk(uint8_t* b8, int localsize, int skipblks, uint8_t key[16])
{
	uint8_t iv[16];
	if (localsize > 0)
	{
		int32_t len128 = localsize & 0xfffffff0;
		int32_t ii, skip;
		struct AES_ctx ctx;

		skip = skipblks * 16;// skip in blocks of 128-bit AES

		memcpy(iv, &b8[16], 16);
#ifdef ENABLE_AES
		AES_init_ctx_iv(&ctx, key, iv);
#endif
		pos = 0;

		for (ii = 0; ii < len128; ii += skip)
		{
#ifdef ENABLE_AES
			AES_CTR_xcrypt_buffer(&ctx, (uint8_t*)b8, 16);
#endif
			//memset(b8, 'P', 16);
			b8 += skip;
		}
	}
}


int CryptAtJPEGHeader(uint8_t* b8, int size, uint8_t key[16])
{
	int ret = 0;
	int localsize = 0, jumpsize;
	if (b8[4] == 0x03 && b8[5] == 0x01 && b8[6] == 0x00 && b8[7] == 0x02)  // Encrpt
	{
		int i;
		for (i = 0; i < size; i++)
		{
			if (b8[i] == 0xff && b8[i + 1] == 0xd9) //end
			{
				localsize = i;
				break;
			}
		}

		if (localsize)
		{
			int storesize = localsize;
			b8[4] = storesize >> 24;  storesize <<= 8;
			b8[5] = storesize >> 24;  storesize <<= 8;
			b8[6] = storesize >> 24;  storesize <<= 8;
			b8[7] = storesize >> 24;

			ret = 1; //encrypting
		}
		else
			return 0;
	}
	else
	{
		localsize = (b8[4] << 24) + (b8[5] << 16) + (b8[6] << 8) + (b8[7]);
		b8[4] = 0x03;
		b8[5] = 0x01;
		b8[6] = 0x00;
		b8[7] = 0x02;

		ret = -1; //decrypting
	}

	jumpsize = localsize + 2;

	int skipblks;
	if (localsize < 65536) skipblks = 4; else skipblks = 16;
	{
		uint8_t *blob = b8;
		blob += 32;
		localsize -= 32;

		crypt_chunk(blob, localsize, skipblks, key);
	}

	return jumpsize * ret;
}

int crypt_photo_key(uint8_t* src, int size, uint8_t key[16])
{
	int ret = 0;

	if (src && size)
	{
		uint8_t* b8 = (uint8_t*)src;

		while (size)
		{
			if (b8[0] == 0xff && b8[1] == 0xd8) //start
			{
				b8 += 2;
				size -= 2;
			}

			while (b8[0] == 0xff && b8[1] != 0xda && size > 0)
			{
				int chunk = (b8[2] << 8) + b8[3] + 2;

				if (b8[1] == 0xe1) //EXIF
				{
					for (int i = 2; i < chunk - 4; i++)
					{
						if (b8[i] == 0xFF && b8[i + 1] == 0xDA && b8[i + 2] == 0x00 && b8[i + 3] == 0x0C) // thumbnail header
						{
							ret = CryptAtJPEGHeader(&b8[i], chunk-i, key);
							break;
						}
					}
				}

				b8 += chunk;
				size -= chunk;
			}

			if (b8[0] == 0xff && b8[1] == 0xda && b8[2] == 0x00 && b8[3] == 0x0C)
			{
				int jumpsize;

				ret = CryptAtJPEGHeader(b8, size, key);
				jumpsize = abs(ret);
				b8 = &b8[jumpsize];
				size -= jumpsize;
			}
		}
		return ret;
	}
	return 0;
}



int crypt_video_key(uint8_t* src, int size, uint8_t key[16], int flags)
{
	if (src && size)
	{
		uint8_t iv[16];
		int skipblks = 64;
		uint32_t* b32 = (uint32_t*)src;

		int32_t len128 = size & 0xfffffff0;
		int32_t ii, skip;
		struct AES_ctx ctx;
		
		int undo = flags & 1;
		int encrypt = (undo == 0) ? 1 : 0;
		int decrypt = flags & 2;

		skip = skipblks * 16;// skip in blocks of 128-bit AES
		
		int usebuf = 0;
		if(size < CRYPTBUF * skipblks)
			usebuf = 1;

		memcpy(iv, &src[16], 16);
#ifdef ENABLE_AES
		AES_init_ctx_iv(&ctx, key, iv);
#endif
		pos = 0;

		for (ii = 0; ii < len128; ii += skip)
		{			
			if(encrypt || decrypt)
			{
				if(usebuf && !decrypt) {
					memcpy(&buff[pos], b32, 16); 
					pos += 16;
				}
#ifdef ENABLE_AES
				AES_CTR_xcrypt_buffer(&ctx, (uint8_t*)b32, 16);
#endif
			}
			else // undo an encrypt using the buffer (faster)
			{
				if(usebuf) {
					memcpy(b32, &buff[pos], 16); 
					pos += 16;
				}
				else
				{
#ifdef ENABLE_AES
					AES_CTR_xcrypt_buffer(&ctx, (uint8_t*)b32, 16);
#endif
				}
			}
			b32 += skip >> 2;
		}

		return 1;
	}
	return 0;
}


int crypt_audio_key(uint8_t* src, int size, uint8_t key[16], int flags)
{
	if (src && size)
	{
		uint8_t iv[16];
		int skipblks = 2;
		uint8_t* b8 = src;
		int32_t len128 = size & 0xfffffff0;
		int32_t ii, skip;
		struct AES_ctx ctx;
		
		int undo = flags & 1;
		int encrypt = (undo == 0) ? 1 : 0;
		int decrypt = flags & 2;

		int same = 1;
		skip = skipblks * 16;
		int usebuf = 0;
		if(size < CRYPTBUF * skipblks)
			usebuf = 1;

		memcpy(iv, &b8[16], 16);

		for (ii = 1; ii < 16; ii++)
		{
			if (iv[0] != iv[ii])
			{
				same = 0;
				break;
			}
		}

		if (!same)
		{
#ifdef ENABLE_AES
			AES_init_ctx_iv(&ctx, key, iv);
#endif
			pos = 0;

			for (ii = 0; ii < len128; ii += skip)
			{
				if(encrypt || decrypt) 
				{
					if(usebuf && !decrypt) {
						memcpy(&buff[pos], b8, 16); 
						pos += 16;
					}
#ifdef ENABLE_AES
					AES_CTR_xcrypt_buffer(&ctx, b8, 16);
#endif
				}
				else // undo an encrypt using the buffer (faster)
				{
					if(usebuf) { 
						memcpy(b8, &buff[pos], 16); 
						pos += 16;
					}
					else
					{
#ifdef ENABLE_AES
						AES_CTR_xcrypt_buffer(&ctx, b8, 16);
#endif
					}
				}				
				b8 += skip;
			}
		}
		return 1;
	}
	return 0;
}

int encrypt_video(uint8_t* src, int size, int flags)
{
	return crypt_video_key(src, size, g_seckey, flags);
}
int encrypt_audio(uint8_t* src, int size, int flags)
{
	return crypt_audio_key(src, size, g_seckey, flags);
}
int encrypt_photo(uint8_t* src, int size)
{
	return crypt_photo_key(src, size, g_seckey);
}

int decrypt_video(uint8_t* src, int size)
{
	return crypt_video_key(src, size, g_dekey, 0);
}
int decrypt_audio(uint8_t* src, int size)
{
	return crypt_audio_key(src, size, g_dekey, 0);
}
int decrypt_photo(uint8_t* src, int size)
{
	return crypt_photo_key(src, size, g_dekey);
}

int decryptFile(char* path, char* name)
{
	int ret = 0;
	char filename[256];
	if (path && strlen(path) > 0 && strlen(path)+strlen(name)<255)
		sprintf(filename, "%s\\%s", path, name);
	else
		strcpy(filename, name);	

	int first_basename_pos = -1;
	int len = (int)strlen(filename);
	if (len >= 12 && (
	   (0 == strncmp(&filename[len - 4], ".MP4", 4)) ||
	   (0 == strncmp(&filename[len - 4], ".LRV", 4)) ||
	   (0 == strncmp(&filename[len - 4], ".JPG", 4)) ||
	   (0 == strncmp(&filename[len - 4], ".THM", 4)) ||
	   (0 == strncmp(&filename[len - 4], ".360", 4)) ) )
		first_basename_pos = len - 12;
	else
		return 0;

	uint64_t filesize = 0;
	struct T_STAT fs;
	if (0 == FSTAT(filename, &fs))
		filesize = fs.STAT_SIZE;

	if (filesize == 0) return 0;

	if ((0 == strncmp(&filename[len - 4], ".JPG", 4)) || (0 == strncmp(&filename[len - 4], ".THM", 4)))
	{
		T_FILE* fp = FOPEN(filename, "rb+");
		if (fp)
		{
			uint8_t* mem = (uint8_t *)BIGALLOC((size_t)filesize);				
			if (mem)
			{
				FREAD(mem, 1, (size_t)filesize, fp);
				ret = decrypt_photo(mem, (int)filesize);

				FSEEK(fp, 0, SEEK_SET);
				FWRITE(mem, 1, (size_t)filesize, fp);
				BIGFREE(mem);	
			}
			FCLOSE(fp);

			if (ret == 0) return 0;
		}		
	}
	else if ((0 == strncmp(&filename[len - 4], ".MP4", 4)) || (0 == strncmp(&filename[len - 4], ".LRV", 4)) || (0 == strncmp(&filename[len - 4], ".360", 4)))
	{

		// Do Video track
		int channel = 0;
		int vid_ok = 0;
		size_t handle = OpenMP4Source(filename, MOV_VIDE_TRAK_TYPE, MOV_AVC1_SUBTYPE, channel, filesize); //H264 track
		
		float length = GetDuration(handle);
		if (handle == 0 || length == 0.0) // try HEVC
		{
			if (handle) CloseSource(handle);
			handle = OpenMP4Source(filename, MOV_VIDE_TRAK_TYPE, MOV_HVC1_SUBTYPE, channel, filesize); //HEVC track
			length = GetDuration(handle);
		}

		do
		{
			if (length > 0.0)
			{
				uint32_t* payload = NULL;
				uint32_t index, payloads = GetNumberPayloads(handle);
	
				for (index = 0; index < payloads; index++)
				{
					uint32_t payloadsize = GetPayloadSize(handle, index);
					payload = GetPayload(handle, payload, index);

					uint8_t* src = (uint8_t*)payload;
					int size = payloadsize;
					// skip NALU header
					while (src[0] == 0 && src[1] == 0 && src[2] == 0)
					{
						src += 2;
						size -= 2;
					}
					src += 8;
					size -= 8;

					int bytes = decrypt_video(src, size);
					if (bytes)
					{
						vid_ok = 1;
						
						if ((index & 127) == 0 || index >= payloads - 127)
						{
							if (payloads < 100000)
							{
								fprintf(stderr, "\b\b\b\b\b\b\b\b\b\b\b\b\b");
								fprintf(stderr,  "V:%5d/%5d", (int)index, (int)payloads - 1);
							}
							else
							{
								fprintf(stderr, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
								fprintf(stderr, "V:%7d/%7d", (int)index, (int)payloads - 1);
							}
						}

						SavePayload(handle, payload, index);
					}

					if (payload == NULL)
						goto cleanupv;
				}
			cleanupv:
				if (payload) FreePayload(payload); payload = NULL;
				if (handle) CloseSource(handle); handle = 0;
			}

			channel++;
			if (channel <= 1 && (0 == strncmp(&filename[len - 4], ".360", 4)))
			{
				handle = OpenMP4Source(filename, MOV_VIDE_TRAK_TYPE, MOV_HVC1_SUBTYPE, channel, filesize); //2nd HEVC track
			}
			else
				break;
		} while (handle);

		if (!vid_ok) return 0;


		// Do Audio track
		handle = OpenMP4Source(filename, MOV_SOUN_TRAK_TYPE, MOV_MP4A_SUBTYPE, 0, filesize); //AAC track
		if (handle)
		{
			uint32_t* payload = NULL;
			if (GetDuration(handle) > 0.0)
			{
				uint32_t index, payloads = GetNumberPayloads(handle);

				for (index = 0; index < payloads; index++)
				{
					uint32_t payloadsize = GetPayloadSize(handle, index);
					payload = GetPayload(handle, payload, index);

					int bytes = decrypt_audio((uint8_t*)payload, payloadsize);
					if (bytes)
					{
						if ((index & 127) == 0 || index >= payloads - 127)
						{
							if (payloads < 100000)
							{
								fprintf(stderr, "\b\b\b\b\b\b\b\b\b\b\b\b\b");
								fprintf(stderr, "A:%5d/%5d", (int)index, (int)payloads - 1);
							}
							else
							{
								fprintf(stderr, "\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
								fprintf(stderr, "A:%7d/%7d", (int)index, (int)payloads - 1);
							}
						}
						SavePayload(handle, payload, index);
					}

					if (payload == NULL)
						goto cleanupa;
				}
			}

		cleanupa:
			if (payload) FreePayload(payload); payload = NULL;
			if (handle) CloseSource(handle); handle = 0;
		}
	}
	printf("\n");

	//rename: Decrypting from 'S' to 'G' or 	encrypting from 'G' to 'S'
	char newfilename[256];
	if (first_basename_pos >= 0)
	{
		if (filename[first_basename_pos] == 'S')
		{
			strcpy(newfilename, filename);
			newfilename[first_basename_pos] = 'G';
			FRENAME(filename, newfilename);

			printf("renamed to %s\n", newfilename);
			ret = -1;
		}
		else if (filename[first_basename_pos] == 'G')
		{
			strcpy(newfilename, filename);
			newfilename[first_basename_pos] = 'S';
			FRENAME(filename, newfilename);

			printf("renamed to %s\n", newfilename);
			ret = 1;
		}
	}

	return ret;
}