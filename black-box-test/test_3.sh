#!/bin/bash

###	black box testning av olika testfall	### 
###	för electrotest-standalone genom	###
###	iteration				###
###	'Test' 					###
###	jgaforsberg gufo0047 gusfor-1 gufr22	###
###	2022-12-13				###


# deklarera förutbestämda testfall till en array
declare -a correct_testcases=("testcase1.txt" "testcase2.txt" "testcase3.txt")
declare -a error_testcases=("testcase_error1.txt" "testcase_error3.txt" "testcase_error3.txt")

# iterera genom förutbestämda korrekta testfall
for testcase in ${correct_testcases[@]};
do
	# kör med korrekt input och spara output för varje testfall
	./electrotest-standalone < $testcase > output.txt
	cp output.txt output_$testcase
	# jämför output med förväntad output för varje testfall
	if diff output.txt expected_output_$testcase;
	then
		echo -e "Test PASSED: correct output for $testcase\n"
	else
		echo -e "Test FAILED: incorrect output for $testcase\n"
	fi
done

# iterera genom förutbestämda felaktiga testfall
for testcase in ${error_testcases[@]};
do
	# kör med felaktig input och spara output för varje testfall
	./electrotest-standalone < $testcase > output.txt
	# kontrollera exitkoden för electrotest, 0 är lyckad exekvering
	if [ $? > 0 ];
	then
		echo "Test PASSED: faulty input handled without application crash for $testcase"
	else
		echo "Test FAILED: faulty input cause application crash for $testcase"
	fi
done

# rensar outputfiler
rm output.txt

