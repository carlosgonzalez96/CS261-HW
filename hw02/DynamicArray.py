# The Dynamic Array Class
# Python has all kinds of powerful stuff that does what your dynamic array needs to do
# No, you CAN'T use any of that


class DynamicArray(object):

    INIT_CAPACITY = 2 ^ 4
    RESIZE_MULTIPLIER = 2

    # The __init__ function is run when you instantiate an instance of this object
    def __init__(self):

        # variables beginning with the underscore can denote internal or self referential data
        # That isn't strictly enforced, but merely a nice convention for readability
        self._size = 0
        self._capacity = DynamicArray.INIT_CAPACITY
        self._data = [None] * self._capacity

    #################################
    # DO YOUR WORK BELOW THIS LINE #
    #################################

    # Return the size of the dynamic array
    def size(self):
        # TODO: return the size of the dynamic array this class represents
        return self._size

    # Return the capacity of the dynamic array
    def capacity(self):
        # TODO: return the capacity of the dynamic array this class represents
        return self._capacity

    # Add an element to the end of the dynamic array
    def add(self, value):
        # TODO: add the passed value to the dynamic array
        end_array = self._size

        if end_array == self._capacity:
            self._resize()

        self._data[end_array] = value
        self._size += 1

    # Get the value at the position passed in as a parameter
    def get(self, pos):
        # TODO: return the value currently stored at the passed position
        return self._data[pos]

    # Put a value into the dynamic array at the specified position, overwriting what was there
    def put(self, pos, value):
        # TODO: put the passed value into the dynamic array at the passed position
        self._data[pos] = value

    # Swap 2 specified values in the dynamic array
    def swap(self, pos1, pos2):
        # TODO: swap the values at the 2 passed positions with one another
        one = self._data[pos1]
        two = self._data[pos2]

        self._data[pos1] = one
        self._data[pos2] = two

    # Remove a value from the dynamic array (and return it)
    def remove(self, pos):
        # TODO: remove the value found at the passed pos and return it

        deleted = self._data[pos]

        for i in range(pos, self._size):
            self._data[i] = self._data[i + 1]

        self._size -= 1
        return deleted

    # Resize the underlying array to make room
    def _resize(self):
        # TODO: resize the underlying array according to certain rules to make room for more values
        self._capacity *= 2
        temporary = [None] * (self._capacity * 2)
        for i in range(0, self._size):
            temporary[i] = self._data[i]

        del self._data
        self._data = temporary

    # DO NOT MODIFY THIS PRINT
    # Print the data in a useful way
    def print_data(self):
        print "[ %s ]" % ' | '.join([str(v) for v in self._data])