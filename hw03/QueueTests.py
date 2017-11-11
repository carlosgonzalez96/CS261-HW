#########################################################################################
# Here you need to write some basic tests to make sure your Queue implementation runs correctly
# You can run them by running 'python QueueTests.py' from the command line
#########################################################################################

from Queue import Queue

queue = Queue()

print "Checking basic variable initializations..."

# TODO: tests here

queue.print_queue()
print "done\n"

###################################

print "Checking is_empty and size..."

# TODO: tests here

queue.is_empty()
queue.print_queue()
print "done\n"

###################################

print "Checking front, removeFront..."

# TODO: tests here
queue.removeFront()
queue.front()
queue.print_queue()
print "done\n"

###################################

print "Checking back, addBack..."

# TODO: tests here
queue.removeFront()
queue.addBack()
queue.print_queue()
print "done\n"

###################################

queue.print_queue()
print "All checks passed"