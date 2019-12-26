import numpy as np
import os
import sys
import tools
from scipy import optimize
from scipy.io import loadmat

data = loadmat(os.path.join('Data', 'data1.mat'))  # 读取手写数字数据
X, y = data['X'], data['y'].ravel()  # 预处理数据
y[y == 10] = 0
m = y.size  # 数据大小(5000)

# 随机选取100张图片展示
rand_indices = np.random.choice(m, 100, replace=False)
sel = X[rand_indices, :]

np.set_printoptions(threshold=sys.maxsize)

# 随机初始化参数在 -0.12 - 0.12 之间
epsilon_init = 0.12
initial_theta1 = np.random.rand(50, 400 + 1) * 2 * epsilon_init - epsilon_init
initial_theta2 = np.random.rand(10, 50 + 1) * 2 * epsilon_init - epsilon_init
initial_nn_params = np.concatenate([initial_theta1.ravel(), initial_theta2.ravel()], axis=0)

# nn_params = tools.graddescend(initial_nn_params, lrate=1, data_size=5000, data=X, y=y)

options = {'maxiter': 100}
costFunction = lambda p: tools.costfunction(p, X.shape[0], X, y, lambda_=1)
res = optimize.minimize(costFunction,
                        initial_nn_params,
                        jac=True,
                        method='TNC',
                        options=options)
nn_params = res.x

theta1 = np.reshape(nn_params[:50 * (400 + 1)],
                    (50, (400 + 1)))
theta2 = np.reshape(nn_params[(50 * (400 + 1)):],
                    (10, (50 + 1)))

pred = tools.getresult(theta1, theta2, X)
for i in range(5000):
    print(pred[i], ' ', y[i])

print('Training Set Accuracy: %f' % (np.mean(pred == y) * 100))


tools.displaydata(sel[0], figsize=(4, 4))

for i in range(20):
    for j in range(20):
        print('{:f}'.format(sel[0, j * 20 + i]), end=' ')
    print()

'''
# 读取已训练好的节点权重值
weights = loadmat(os.path.join('Data', 'ex3weights.mat'))

# 利用已有权重值进行识别
Theta1, Theta2 = weights['Theta1'], weights['Theta2']
Theta2 = np.roll(Theta2, 1, axis=0)

print(tools.getresult(Theta1, Theta2, X))
'''
