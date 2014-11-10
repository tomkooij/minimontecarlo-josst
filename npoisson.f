      integer function npoisson(mean)
      real mean
c
c Generates a random integer N according to a Poisson law.
c Coded from Los Alamos report LA-5061-MS
c Prob(N) = exp(-mean)*mean^N/Factorial(N)
c
c
      integer n
      real    x, expmean, pir, sigma

      npoisson=0
      if(mean.le.0.0)   return

      sigma=sqrt(mean)
      expmean=exp(-mean)

c use a gaussian approximation for large values of mean
c as yet not available

      if(mean.ge.88.0)   then
         print *,'the poisson distribution can safely be approximated by
     1 a gaussian'
         return
      endif

      pir=1.0
      n=-1

  100 continue
      n=n+1
      pir=pir*rndm()
      if(pir.le.expmean) goto 101
      goto 100
  101 continue

      npoisson=n
      return
      end
