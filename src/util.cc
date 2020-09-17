// cesun, 9/13/20 2:35 AM.

#include <iostream>

#ifdef __GLIBC__

#include <stdio_ext.h>

#endif

void fast_io() {
    using namespace std;
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#ifdef __GLIBC__
    __fsetlocking(stdin, FSETLOCKING_BYCALLER);
    __fsetlocking(stdout, FSETLOCKING_BYCALLER);
#endif
}