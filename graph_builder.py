import matplotlib.pyplot as plt

# open the file so you can read from it
with open("cmake-build-debug/out.txt") as inf:
    # for each line in the file,
    # split it on commas (results in a list of strings)
    # then convert each string to a float (results in a list of floats)
    items = (map(float, line.split(" ")) for line in inf)
    # transpose (convert columns to rows),
    # then assign each row to a variable)
    x, y = zip(*items)

    fig = plt.figure()
    plt.xlabel('size, elements', fontsize=10)
    plt.ylabel('time, s', fontsize=10)
    fig.suptitle('test add', fontsize=10)
    plt.plot(x, y, '+', color='blue');
    plt.show()
    fig.savefig('add_1024_10x1024.jpg')