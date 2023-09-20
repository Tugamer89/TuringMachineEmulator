#-------------
#	Instruction:
#	[current status] [current value] [new state] [new value] [move]
#
#	Initialization instruction:
#	[current status] [memory index] -
#
#	status = every letter
#	value = 0  1 or _
#	move = > (right)  < (left) or - (stay)
#
#-------------
#
#	Example (not bit per bit for each number separated by blank):

a 1 -

a 0 a 1 >
a 1 a 0 >
a _ b _ >
b 0 a 0 -
b 1 a 1 -

#-------------
