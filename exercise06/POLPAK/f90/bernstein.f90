program bernstein
implicit none
integer,parameter :: &
rk=selected_real_kind(12,100)
real(rk),allocatable :: b(:),p(:)
real(rk) :: x,y,dx
integer :: iargc,n,mx,i,m,k
character(len=80) :: argu,file1,file2
if (iargc()<5) then
write(0,'(a,a)') 'usage: bernstein ‘,&
‘cpointfile interpfile dx n p0 p2 p3 .. pn'
stop
end if
call getarg(1,file1)
call getarg(2,file2)
open(100,file=file1,status='new')
open(200,file=file2,status='new')
call getarg(3,argu); read(argu,*) dx
call getarg(4,argu); read(argu,*) n
allocate(b(0:n),p(0:n))
do i=0,n
call getarg(i+5,argu); read(argu,*) p(i)
write(100,'(2g18.10)') &
real(i,rk)/real(n,rk),p(i)
end do

mx=1.0/dx
do m=0,mx
x=dx*m
y=0.0
call bernstein_poly(n,x,b)
do i=0,n
write(i+10,'(2g18.10)') x,b(i)
y=y+p(i)*b(i)
end do
write(200,'(2g18.10)') x,y
end do
close(100)
close(200)
stop
end program bernstein
