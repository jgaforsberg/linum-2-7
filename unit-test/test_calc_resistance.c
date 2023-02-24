#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
/*
###	enhetstestning av olika testfall	### 
###	för calc_resistance i CUnit för  	###
###	electrotest-standalone			###
###	'Test' 					###
###	jgaforsberg gufo0047 gusfor-1 gufr22	###
###	2022-12-13				###
*/
// tagen från electrotest-standalone.c
float calc_resistance(int count, char conn, float *array){

	float resistance;

	if (conn == 'S' || conn == 's'){
 		for(int i = 0; i < count; i++){
			resistance += array[i];
		}
	} else if (conn == 'P' || conn == 'p'){
		float resBuffert = 0;

		for(int i = 0; i < count; i++){
			resBuffert += (1/array[i]);
			if(array[i] == 0){
				return 0;
			}
		}
		resistance = 1/resBuffert;
	} else {
		return -1;
	}

	return resistance;

}

void test_calc_resistance_assert_equal(void)
{
	/*
	redovisar två exempeltestfall
	*/
	// count = 2, conn = 'P'
	float array[] = {25, 125};
	float expected_output = 20.833334;
	float actual_output = calc_resistance(2, 'P', array);
	printf("\nactual: %f\n", actual_output);
	CU_ASSERT_EQUAL(expected_output, actual_output);

	// count = 2, conn = 'S'
	expected_output = 150;
	actual_output = calc_resistance(2, 'S', array);
	printf("\nactual: %f\n", actual_output);
	CU_ASSERT_EQUAL(expected_output, actual_output);
}
void test_calc_resistance_assert_true(void)
{
	/*
	redovisar två exempelfall
	*/
	// count -2, conn = 'P'
	float array[] = {25, 125};
	float actual_output = calc_resistance(-2, 'P', array); 
	printf("\nactual: %f\n", actual_output);
	CU_ASSERT_TRUE(actual_output > 0);
	// count = 2, conn = 'G'
	actual_output = calc_resistance(2, 'G', array);
	printf("\nactual: %f\n", actual_output);
	CU_ASSERT_TRUE(actual_output == -1);
}

/*
main() är modifierad från exemplet i dokumentationen för CUnit
https://cunit.sourceforge.net/example.html
*/
int main()
{
	CU_pSuite pSuite = NULL;
	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	pSuite = CU_add_suite("calc_resistance_test_suite", 0, 0);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	if ((NULL == CU_add_test(pSuite, "test_calc_resistance_assert_equal", test_calc_resistance_assert_equal)) || (NULL == CU_add_test(pSuite, "test_calc_resistance_assert_true", test_calc_resistance_assert_true))) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
