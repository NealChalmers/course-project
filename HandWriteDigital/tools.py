from matplotlib import pyplot
import numpy as np

num_input = 400
num_hidden = 50
num_labels = 10


# 手写数字展示函数，可略过
def displaydata(X, example_width=None, figsize=(10, 10)):
    """
    Displays 2D data stored in X in a nice grid.
    """
    # Compute rows, cols
    if X.ndim == 2:
        m, n = X.shape
    elif X.ndim == 1:
        n = X.size
        m = 1
        X = X[None]  # Promote to a 2 dimensional array
    else:
        raise IndexError('Input X should be 1 or 2 dimensional.')

    example_width = example_width or int(np.round(np.sqrt(n)))
    example_height = n / example_width

    # Compute number of items to display
    display_rows = int(np.floor(np.sqrt(m)))
    display_cols = int(np.ceil(m / display_rows))

    fig, ax_array = pyplot.subplots(display_rows, display_cols, figsize=figsize)
    fig.subplots_adjust(wspace=0.025, hspace=0.025)

    ax_array = [ax_array] if m == 1 else ax_array.ravel()

    for i, ax in enumerate(ax_array):
        ax.imshow(X[i].reshape(example_width, example_width, order='F'),
                  cmap='Greys', extent=[0, 1, 0, 1])
        ax.axis('off')
    pyplot.show()


# sigmoid函数
def sigmoid(z):
    return 1.0 / (1.0 + np.exp(-z))


def sigmoidgradient(z):
    g = 1 / (1 + np.exp(-z)) * (1 - 1 / (1 + np.exp(-z)))
    return g


# 神经网络预测模型，是一个三层神经网络（两层具有权重节点），各层节点数分别为  400（20*20像素）、50、10
def getresult(theta1, theta2, data):  # for 400*50 50*10 two layers' neural network
    if data.ndim == 1:
        data = data[None]

    data_size = data.shape[0]
    # num_labels = 10
    result = np.zeros(data_size)

    data = np.concatenate([np.ones((data_size, 1)), data], axis=1)
    out1 = sigmoid(np.dot(data, theta1.T))
    out1 = np.concatenate([np.ones((data_size, 1)), out1], axis=1)
    out2 = sigmoid(np.dot(out1, theta2.T))
    result = np.argmax(out2, axis=1)

    return result


def costfunction(nn_params, data_size, data, y, lambda_=0.0):
    # 展开参数
    theta1 = np.reshape(nn_params[:num_hidden * (num_input + 1)],
                        (num_hidden, (num_input + 1)))

    theta2 = np.reshape(nn_params[(num_hidden * (num_input + 1)):],
                        (num_labels, (num_hidden + 1)))

    J = 0  # cost function result
    # 处理好结果集
    set_y = np.zeros((data_size, num_labels))
    for i in range(num_labels):
        ind = np.where(y == i)
        for j in ind:
            set_y[j, i] = 1

    # a1为首层输入数据, a2 a3 为各层处理完毕输出数据
    # z2 z3 为中间数据
    a1 = np.ones((data_size, num_input + 1))
    a2 = np.ones((data_size, num_hidden + 1))
    a3 = np.ones((data_size, num_labels))
    z2 = np.zeros((data_size, num_hidden))
    z3 = np.ones((data_size, num_labels))

    # 各参数斜率
    theta1_grad = np.zeros(theta1.shape)
    theta2_grad = np.zeros(theta2.shape)

    a1[:, 1:] = data
    # 正向求解 Feedforward,每一轮迭代计算一次中间值
    for i in range(data_size):
        z2[i, :] = np.dot(a1[i, :], theta1.T)
        a2[i, 1:] = sigmoid(z2[i, :])
        z3[i, :] = np.dot(a2[i, :], theta2.T)
        a3[i, :] = sigmoid(z3[i, :])

        # 反向传播算法 backpropagation algorithm

        # 计算中间值
        delta_3 = np.ones(num_labels)
        delta_3 = a3[i] - set_y[i, :]
        delta_2 = np.zeros(num_hidden)
        delta_2 = np.dot(theta2[:, 1:].T, delta_3) * sigmoidgradient(z2[i])
        # 每一轮迭代积累斜率
        theta2_grad += np.dot(delta_3.reshape(1, -1).T, a2[i].reshape(1, -1))
        theta1_grad += np.dot(delta_2.reshape(1, -1).T, a1[i].reshape(1, -1))

    theta2_grad /= data_size
    theta1_grad /= data_size

    # 累计斜率值,去除偏差项bias term
    temp_theta2 = theta2.copy()
    temp_theta1 = theta1.copy()
    temp_theta2[:, 0] = np.zeros(num_labels)
    temp_theta1[:, 0] = np.zeros(num_hidden)

    # 正则化斜率
    theta2_grad += lambda_ * temp_theta2 / data_size
    theta1_grad += lambda_ * temp_theta1 / data_size

    # 计算cost funtion值
    temp_j = 0
    for i in range(data_size):
        for j in range(num_labels):
            temp_j += set_y[i, j] * np.log(a3[i, j]) + (1 - set_y[i, j]) * (np.log(1 - a3[i, j]))

    # 正则化
    temp_r = 0  # regularization
    for i in range(num_hidden):
        temp_r += sum(theta1[i, 1:] * theta1[i, 1:])
    for i in range(num_labels):
        temp_r += sum(theta2[i, 1:] * theta2[i, 1:])

    J = -1 / num_hidden * temp_j + lambda_ / (2 * num_hidden) * temp_r

    # 拼接斜率值
    grad = np.concatenate([theta1_grad.ravel(), theta2_grad.ravel()])

    return J, grad


# 梯度下降训练函数
def graddescend(theta, lrate, data_size, data, y):
    cost_history = []
    cost = 999
    i = 0
    while (cost > 10):
        cost, grad = costfunction(theta, data_size, data, y, lambda_=1)
        cost_history.append(cost)
        theta -= grad * lrate
        print(i, ':', cost)
        i += 1
    return theta
