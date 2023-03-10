#pragma once
#include <jni.h>
#include <dlfcn.h>
#include <cstdio>
#include <pthread.h>
#include <dlfcn.h>
#include <dobby.h>

#define HOOK(fname, ffunc, ffunc_o) DobbyHook(dlsym(dlopen("libcocos2dcpp.so", RTLD_LAZY), fname), (void *)ffunc, (void **)&ffunc_o);
