directive default_rate Inf
directive stochasticity_absorption 1
process a 1
process c 1
process f 1
process fc 3

c 1 -> fc 2 3 @5.~1
f 0 -> fc 2 0 @0.100000001~1
fc 2 -> c 0 1 @0.5~50
c 0 -> fc 1 0 @10.~1
f 1 -> fc 1 3 @10.~1
c 1 -> a 1 0 @1.~50
c 1 -> c 1 0 @0.5~50
f 0 -> c 1 0 @0.100000001~1
c 1 -> fc 0 1 @5.~1
f 1 -> fc 0 2 @10.~1
f 1 -> f 1 0 @0.0340000018~100
c 0 -> fc 3 2 @5.~1
f 0 -> fc 3 1 @0.100000001~1
fc 2 -> a 0 1 @1.~50

initial_state a 0, c 0, f 1, fc 0
