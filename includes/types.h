#ifndef XE_TYPES_H
#define XE_TYPES_H
#ifdef CPLUSPLUS
#  define BOOL bool
#  define TRUE true
#  define FALSE false
#else
#  define BOOL char
#  define FALSE (0)
#  define TRUE  (! FALSE)
#endif

typedef unsigned char	uchar;
typedef unsigned char	u8_t;
typedef signed char	s8_t;
typedef signed char	schar;

typedef unsigned short	u16_t;
typedef signed short	s16_t;

typedef unsigned int	u32_t;
typedef signed int	s32_t;

typedef unsigned long long int u64_t;
typedef signed long long int   s64_t;

// standard names
typedef u16_t	uint16_t;
typedef u32_t	uint32_t;
typedef u64_t	uint64_t;
#endif
