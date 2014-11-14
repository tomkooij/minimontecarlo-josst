      subroutine putpar(parv,n)
      integer n
      real parv(n)
      common/pawpar/par(4)
      print *,(parv(i),i=1,n)
      do i=1,4
      if(i.le.n) par(i)=parv(i)
      if(i.gt.n) par(i)=0.0
      enddo
      return
      end
