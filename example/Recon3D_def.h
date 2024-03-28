#ifndef _HEADER_RECON3D_DEF_H_
#define _HEADER_RECON3D_DEF_H_


#ifndef NR_EXPORTS
# if (defined _WIN32 || defined WINCE || defined __CYGWIN__) && defined(NR_API_EXPORTS)
#   define NR_EXPORTS __declspec(dllexport)
# elif defined __GNUC__ && __GNUC__ >= 4 && (defined(NR_API_EXPORTS) || defined(__APPLE__))
#   define NR_EXPORTS __attribute__ ((visibility ("default")))
# else
# define NR_EXPORTS 
# endif
#endif


#ifndef NR_EXTERN_C
#  ifdef __cplusplus
#    define NR_EXTERN_C extern "C"
#  else
#    define NR_EXTERN_C
#  endif
#endif

#if defined _WIN32
#  define NR_CDECL __cdecl
#  define NR_STDCALL __stdcall
#else
#  define NR_CDECL
#  define NR_STDCALL
#endif


#ifndef NR_API
#  define NR_API(rettype) NR_EXTERN_C NR_EXPORTS rettype NR_CDECL
#endif


#endif /* ifndef _HEADER_NRECON_SDK_DEF_H_ */
