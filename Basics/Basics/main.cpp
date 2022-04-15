#include <atomic>                                                                
#include <stdio.h>
#include "core/RingBuff.h"
#include "headers.h"
#include "template.h"

int main()
{	
	testthread::testThread();
    core_log_error("ssss");
    CRingBuff buff(12);
    system("pause");
    return 0;
}