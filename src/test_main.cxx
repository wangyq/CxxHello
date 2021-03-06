
#include "func_map.h"

//call every module's start function here!
BEGIN_FUNC_MAP()
	RUN_FUNC_IF(false,test_gcd)
	RUN_FUNC_IF(false,test_icpc2014)
	RUN_FUNC_IF(false,test_const_ptr)
	RUN_FUNC_IF(false,test_autoptr)
	RUN_FUNC_IF(false,test_vfork)
	RUN_FUNC_IF(false,test_read)
	RUN_FUNC_IF(true,test_vector_sort)

END_FUNC_MAP()


static void init() {
	// call function map
	CALL_FUNC_MAP();
}

int main()
{
	//test_cases();// here run test cases!
	init();
	return 0;
}
