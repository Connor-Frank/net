""" See LICENSE file for copyright and license details. """

import numpy as np
from tqdm import trange


def magic_proc(x):
    return np.tanh(x)


def magic_eval(x):
    return x * (1 - x)


N_STEPS = 1e4
PRINT_INTERVAL = N_STEPS / 10

# input data
x = np.array([[0, 0, 0], [1, 1, 1], [1, 1, 0], [0, 0, 1]])
x1 = np.array([[0, 1, 0], [1, 0, 1], [1, 0, 0], [0, 1, 1]])

# output data
y = np.array([[0], [1], [1], [0]])

print(f"inputs:\n{x}\n{x1}\n")

np.random.seed(1)

hid0 = 2 * np.random.random((3, 4)) - 1
hid1 = 2 * np.random.random((4, 1)) - 1

for i in (t := trange(int(N_STEPS))):
    l0 = x if i % 2 == 0 else x1

    # get layer results one after the other
    l1 = magic_proc(np.dot(l0, hid0))
    l2 = magic_proc(np.dot(l1, hid1))

    l2_error = y - l2
    t.set_description("error: %f" % np.mean(np.abs(l2_error)))

    # get deltas and errors
    l2_delta = l2_error * magic_eval(l2)
    l1_error = l2_delta.dot(hid1.T)
    l1_delta = l1_error * magic_eval(l1)

    # update weights
    hid1 += l1.T.dot(l2_delta)
    hid0 += l0.T.dot(l1_delta)

print("\noutput after training:")
l0 = x
l1 = magic_proc(np.dot(l0, hid0))
l2 = magic_proc(np.dot(l1, hid1))
print(f"{l0}\n{l2}\n")
l0 = x1
l1 = magic_proc(np.dot(l0, hid0))
l2 = magic_proc(np.dot(l1, hid1))
print(f"{l0}\n{l2}")
