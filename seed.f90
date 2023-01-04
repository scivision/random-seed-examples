program seeder

implicit none

integer, allocatable :: seed(:)
integer :: n
real :: r(3)

call random_seed(size = n)
allocate(seed(n))
seed = 0

call random_seed(put=seed)

call random_number(r)

print '(3F9.6)', r

! Intel,IntelLLVM: 0.000000 0.025480 0.352516
! GNU: 0.471078 0.117346 0.884884


end program
