      real function compscat( opt , Egam )
      integer opt
      real Egam
************************************************************************
      double precision Me, re, pi, kinfac, A, B, C, D, E, F, gam, sigma,
     1 sigmas, sigmac

C     energies in MeV; distances in cm;
      Me=0.510998902
      re=2.817940285e-13
      pi=3.141592653590
C     this factor makes cm^2 into barn
      kinfac=2.0e24*pi*(re**2)

      gam=Egam/Me
      A=(1.0+gam)/(gam**2)
      B=1.0+2.0*gam
      C=2.0*(1.0+gam)/B
      D=dlog(B)/gam
      E=2.0*(1.0+gam)*(2.0*gam**2-2.0*gam-1.0)
      E=E/((gam**2)*(B**2))
      F=8.0*gam**2/(3.0*B**3)

      sigmac=kinfac*(A*(C-D)+0.5*D-(1.0+3.0*gam)/(B**2))

      sigmas=(kinfac/2.0)*(D/(gam**2)+E+F)

      sigma=sigmac-sigmas

      if(opt.eq.0) then
         compscat = sigmac
      elseif(opt.eq.1) then
         compscat = sigmas
      elseif(opt.eq.-1) then
         compscat = sigma
      else
         compscat = 0.0
         print *,'Invalid option in compscat.f ',opt
      endif
      return
      end
