# Iris Classification
## Background
The iris dataset consists of 50 samples from each of three species of Iris (Iris setosa, Iris virginica and Iris versicolor). Four features were measured from each sample: the length and the width of the sepals and petals, in centimeters. This data set became a typical test case for many statistical classification techniques in machine learning such as support vector machines. It is well labeled, consistant, and isn't missing any data. It is also included in SKLearn.
## Project
Create and analyze multiple models for predicting iris species given the 4 features. the models used are: 
 - k-Nearest Neighbor (k-NN)
 - Naïve Bayes
 - Logistic Regression
 - Support Vector Machines (SVMs)
 - Decision Trees
 - Random Forests
 - Perceptrons (this model was ultimatly chosen for the app as it is the only one that reached 100% accuracy)
 - Deep Neural Net

`irisIdentifier.py` is the actual application to identify iris species given 4 features. Just run the file, insuring you have SKlearn installed (pip install sklearn).  
Some sample data to try is [5.1, 3.5, 1.4, 0.2] (a setosa), [6.7, 3.1, 4.4, 1.4] (a versicolor), and [5.9, 3.0, 5.1, 1.8] (a virginica).  
`testModels.py` is used to generate models and create reports.  
`results.txt` contains classification reports on all models.  
`\models` contains all the serialized trained models (Note: dnn can't be pickled, so it is saved using kera's model.save() function).  
