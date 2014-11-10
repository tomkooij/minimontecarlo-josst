      real function compabs( T , Egam )
      real T, Egam
************************************************************************
      double precision Me, re, pi, A, B, C, D, s, sigma, gam, edge, 
     1 kinfac

C     energies in MeV; distances in cm;
      Me=0.510998902
      re=2.817940285e-13
      pi=3.141592653590

      gam=(Egam/Me)
      A=(1.0+2.0*gam)
      edge=(Egam*2.0*gam/A)
      if(T.gt.edge) then
         compabs=0.0
         return
      endif

      kinfac=1.0e24*pi*(re**2)/Me/(gam**2)

      s=T/Egam
      B=1.0-s
      C=(s**2)/(gam**2)/(B**2)
      D=(s/B)*(s-2.0/gam)

      sigma=kinfac*(2.0+C+D)

      compabs=sigma
      return
      end
