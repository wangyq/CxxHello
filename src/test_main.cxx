
#include "func_map.h"

//call every module's start function here!
BEGIN_FUNC_MAP()
	FUNC_ITEM_IF(false,test_gcd)
	FUNC_ITEM_IF(true,test_icpc2014)
	FUNC_ITEM_IF(true,test_const_ptr)
	FUNC_ITEM_IF(true,test_autoptr)
	FUNC_ITEM_IF(true,test_vfork)
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
