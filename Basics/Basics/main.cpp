#include <atomic>                                                                
#include <stdio.h>
#include "core/RingBuff.h"
#include "headers.h"
#include "template.h"

int main()
{	
	const int32& f = 12;
    core_log_error("ssss", &f);
    system("pause");
    return 0;
}