from sklearn.datasets import fetch_openml
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier as KNN
from sklearn import metrics as m
import numpy as np

X, y = fetch_openml('mnist_784', return_X_y=True)
x_train, x_test, y_train, y_test = train_test_split(X, y, test_size=10000, shuffle=False)
model = KNN(n_neighbors=1)
model.fit(x_train[:100], y_train[:100]) # use only the first 100 (too slow)
err_1000 = 1 - m.accuracy_score(model.predict(x_test[:1000]), y_test[:1000])
err = 1 - m.accuracy_score(model.predict(x_test), y_test)
print('Normal features')
print('Error: {}: '.format(err_1000))
print('Error: {}: '.format(err))

p = np.random.permutation(x_train.shape[1])
x_train_p = x_train[:, p]
x_test_p = x_test[:, p]
model_p = KNN(n_neighbors=1)
model_p.fit(x_train_p[:100], y_train[:100])
err_1000_p = 1 - m.accuracy_score(model_p.predict(x_test_p[:1000]), y_test[:1000])
err_p = 1 - m.accuracy_score(model_p.predict(x_test_p), y_test)
print
print('Permuted features')
print('Error (expect {}): {}: '.format(err_1000, err_1000_p))
print('Error (expect {}): {}: '.format(err, err_p))
