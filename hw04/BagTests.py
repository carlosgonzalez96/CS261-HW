#########################################################################################
# Here are some basic tests to make sure your Bag implementation runs correctly
# You can run them by running 'python BagTests.py' from the command line
#########################################################################################

from Bag import *

bag = Bag()

checkVal1 = 1;
checkVal2 = 2;

print "Checking basic variable initializations..."
assert bag.is_empty();
# TODO: check that your inits are ok

bag.print_bag()
print "done\n"

###################################

print "Checking add, contains, functions..."

#TODO: check that your add and contains operate as expected
bag.add(checkVal1);
bag.add(checkVal2);

assert bag.contains(checkVal1) == 1;
assert bag.contains(checkVal2) == 1;
bag.print_bag()
print "done\n"

###################################

print "Checking remove, function(s)..."

#TODO: check that your remove operates as expected
bag.remove(checkVal1);
bag.remove(checkVal2);

assert bag.contains(checkVal1) == 0;
assert bag.contains(checkVal2) == 0;

bag.print_bag()
print "done\n"

###################################

print "Checking that all of the above didn't break things"

#TODO: check that everything works and that the order in which you call your
# functions doesn't break things

bag.is_empty();
bag.add(5);
bag.add(6);
bag.add(7);
bag.add(7);
assert bag.size() == 3;

bag.remove(7);

assert bag.size() == 2;
assert bag.contains(5);
assert bag.contains(6);

bag.print_bag()
print "All checks passed"
