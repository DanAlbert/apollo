#ifndef __APOLLO_H__
#define __APOLLO_H__

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN

#ifndef WINVER
#define WINVER 0x0502
#endif // WINVER

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0502
#endif // _WIN32_WINNT

#ifdef APOLLO_EXPORTS
#define APOLLO_API __declspec(dllexport)
#else
#define APOLLO_API __declspec(dllimport)
#endif // APOLLO_EXPORTS

#endif // WIN32

#endif // __APOLLO_H__