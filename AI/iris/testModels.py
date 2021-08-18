'''
Test a bunch of different models on the Iris Dataset
Output to results file
Chase Brown
'''

from pathlib import Path								# Cross platform pathing
import pickle											# Saving trained models
from sklearn.neighbors import KNeighborsClassifier		# Specific models
from sklearn.naive_bayes import GaussianNB
from sklearn.linear_model import LogisticRegression
from sklearn.svm import SVC
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import train_test_split	# Shuffle, split data
from sklearn.metrics import classification_report		# Compare and report models
from sklearn.datasets import load_iris					# Iris dataset

from keras.models import Sequential, save				# Neural net stuff
from keras.layers.core import Dense
from keras.optimizers import SGD
from sklearn.preprocessing import LabelBinarizer

# Dict of all the different models to test
models = {
	'knn': KNeighborsClassifier(n_neighbors=1),
	'naive_bayes': GaussianNB(),
	'logit': LogisticRegression(solver='lbfgs', multi_class='auto'),
	'svm': SVC(kernel='rbf', gamma='auto'),
	'decision_tree': DecisionTreeClassifier(),
	'random_forest': RandomForestClassifier(n_estimators=100),
	'mlp': MLPClassifier()
}

print('Loading data...')
dataset = load_iris()																				# Get iris data (comes with sklearn)
trainX, testX, trainY, testY = train_test_split(dataset.data, dataset.target, random_state=3)		# Split and shuffle data (75% for training, 25% for testing)

with open(Path('iris/results.txt'), 'w') as file:
	for model in models:																			# Normal machine learing models
		print(f'Training using {model}...')
		m = models[model]
		m.fit(trainX, trainY)																		# Train the model using training data

		print(f'Evaluating {model}... ')
		predictions = m.predict(testX)																# Predict y data using model and testX
		file.write(f'\n\n{model} report:\n')
		file.write(classification_report(testY, predictions, target_names=dataset.target_names))	# Compare prediction with actual testY data, write report
		pickle.dump(m, open(Path(f'iris/models/{model}.sav'), 'wb'))													# Save model


	# Deep Neural Network model (I don't totally understand this one yet, lots of stuff happening in the background with TensorFlow and such)
	lb = LabelBinarizer()		# Encode the labels as 1-hot vectors
	trainY = lb.fit_transform(trainY)
	testY = lb.transform(testY)

	model = Sequential()		# Define the 4-3-3-3 architecture using Keras
	model.add(Dense(3, input_shape=(4,), activation='sigmoid'))
	model.add(Dense(3, activation='sigmoid'))
	model.add(Dense(3, activation='softmax'))

	print(f'Training using deep learning...')
	opt = SGD(lr=0.1, momentum=0.9, decay=0.1 / 250)
	model.compile(loss='categorical_crossentropy', optimizer=opt, metrics=['accuracy'])				# Make the model
	H = model.fit(trainX, trainY, validation_data=(testX, testY), epochs=250, batch_size=16)		# Train the model

	print('Evaluating network...')
	predictions = model.predict(testX, batch_size=16)
	file.write(f'\n\nDeep Neural Network report:\n')
	file.write(classification_report(testY.argmax(axis=1), predictions.argmax(axis=1), target_names=dataset.target_names))
	model.save(Path('iris/models/dnn'))