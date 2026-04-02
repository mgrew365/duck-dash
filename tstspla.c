#include <osbind.h>
#include "sscreen.h"

int main()
{

    UINT32 *base = (UINT32 *)Physbase();
    initilizeSplashScreen(base);
    
    /* Wait for key press */
    while (!Cconis()) {
        /* do nothing */
    }

    return 0;
}
