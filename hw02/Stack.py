from DynamicArray import DynamicArray

# The Stack Class
# Python has all kinds of powerful stuff that does what your Stack needs to do
# No, you CAN'T use any of that
# You need to use your Dynamic Array implementation instead
class Stack(object):

    # The __init__ function is run when you instantiate an instance of this object
    def __init__(self):
        self._size = 0
        self._dynamic_array = DynamicArray()

    #################################
    ## DO YOUR WORK BELOW THIS LINE #
    #################################

    # Return whether or not the stack is empty
    def is_empty(self):
        #TODO: return True or False to answer if the stack is empty
        if self._size == 0:
            return True

    # Return the size on the stack
    def size(self):
        #TODO: return the current size of the stack
        return self._size

    # look at the top of the stack (but don't remove)
    def top(self):
        #TODO: return the current top of the stack
        return self._dynamic_array.get(self._size - 1)

    # Push a value on to the top of the stack
    def push(self, value):
        #TODO: push the pased value onto the stack
        self._dynamic_array.add(value)
        self._size += 1

    # take the top value off of the stack and return it to the user
    def pop(self):
        #TODO: pop the top value off the stack
        self._dynamic_array.remove(self._size - 1)
        self._size -= 1
        return 1

    # DO NOT MODIFY THIS PRINT
    def print_stack(self):
        print '====\n' + '\n----\n'.join([str(v) for v in self._dynamic_array._data[:self._size]]) + '\n^^^^'