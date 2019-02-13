#ifndef __SLEEP_H__
#define __SLEEP_H__

// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.

#ifdef __cplusplus
extern "C"
{
#endif

//Functions exported from sleep.c
extern void sleep(int n);


//Mark the end of the C binding section for C++ compilers
#ifdef _cplusplus
}
#endif

//Prototypes for the globals exported by this driver.

#endif //__SLEEP_H__