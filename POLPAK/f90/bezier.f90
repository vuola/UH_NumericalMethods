program bezier
implicit none
integer,parameter ::&
& rk=selected_real_kind(12,100)
real(rk),allocatable :: b(:),xa(:),ya(:)
real(rk) :: x,y,t,dt
integer :: iargc,n,mt,i,m,k
character(len=80) :: argu,file1,file2
if (iargc()/=2) then
write(0,'(a)') 'usage: bezier n dt'
stop
end if
call getarg(1,argu); read(argu,*) n
call getarg(2,argu); read(argu,*) dt
n=n-1
allocate(b(0:n),xa(0:n),ya(0:n))
do i=0,n
read(5,*) xa(i),ya(i)
end do

mt=1.0/dt
do m=0,mt
t=dt*m
x=0.0
y=0.0
call bernstein_poly(n,t,b)
do i=0,n
y=y+ya(i)*b(i)
end do
call bernstein_poly(n,t,b)
do i=0,n
x=x+xa(i)*b(i)
end do
write(6,'(2g18.10)') x,y
end do
stop
end program bezier