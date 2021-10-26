using Random
using Printf

rng = Random.MersenneTwister(0)

r = rand(rng, 3)

@printf("%f %f %f", r[1], r[2], r[3])
