unordered_map helps with .find() because it being O(1)

all_roads could have been way simpler and faster if i just added all the new roads to a separate vector and then just return it
but it would make remove_road way slower because finding road from a vector is O(log n) and removal from it is O(n)

