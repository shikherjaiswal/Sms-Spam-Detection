----------------------------------------------------------------------------
Table Of Contents:

Directory Structure:

	$2015csb1019_2015csb116_project
	   |---- Report.pdf
	   |---- /code
			|--preprocessing
			|--NBC
					|-- naiye_bayes.m
			|--SVM
				|-- matlab_inbuilt_svm
					|-- svm_main.m
				|-- my_svm
					|-- main.m
			|--KNN
					|-- knn_main.m
					|-- knnPlot.m
			|--RANDOM_FOREST
					|-- random_forest.cpp
					|-- randomForestPlot.m					
	   |---- Readme
	   
----------------------------------------------------------------------------

How to run the code ?

All working scripts is in "code" folder.

"preprocessing" folder contains code to extract raw data from UCI dataset and pre-process it to make usable data for our classifiers.

Testing Naiye Bayes classifier code:
run naiye_bayes.m code in matlab
After running this we will get plot , that we have attached in the report.

Testing SVM classifier code :
run svm_main.m code in matlab
After running this we will get plot , that we have attached in the report.

Testing KNN classifier code:
run knn_main.m code in matlab 
Note : In this code you have to expicitely give "k" parameter for each run of the code.

Testing Random Forest code :
run random_forest.cpp code in terminal
Note : This classifier code is in c++ .So Follow c++ code of conduct for compilation.

Eg :
$g++ random_forest.cpp
$./a.out
Note :This program will give confusion matrix for a given forest size . So for different forest size we have to explicitely change in the code , for that variable.

For plot of  KNN and Random Forest data :
We have mannually run the code and recorded the confusion matrix  , which was used to find the accuracy on the test and train sets. 

For KNN plot :
run matlab script knnPlot.m

For Random forest plot :
run matlab script randomForestPlot.m