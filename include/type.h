#ifndef		__INCLUDE_TYPE_H__
#define		__INCLUDE_TYPE_H__


#ifndef		NULL
#define		NULL				((void *) 0)
#endif

typedef		char				int8_t;
typedef		short				int16_t;
typedef		int					int32_t;
typedef		long long			int64_t;

typedef		unsigned char		uint8_t;
typedef		unsigned short		uint16_t;
typedef		unsigned int		uint32_t;
typedef		unsigned long long	uint64_t;


#undef size_t
typedef		unsigned int		addr_t;
typedef		unsigned int		size_t;


#endif		//__INCLUDE_TYPE_H__

