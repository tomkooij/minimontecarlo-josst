      FUNCTION CONVLAN(X)
      REAL	X
* X is pulseheight in any unit
* Fit parameters sit in common/pawpar/
      COMMON/PAWPAR/PAR(4)
*	PAR(1)	scaling needed to turtn pulseheight units into MeV
*	PAR(2)	vertical scaling 
*	PAR(3)	resolution gaussian (unit: pulseheight)
c     VECTOR PAR(4)
* Remaining (mostly physical) constants in vector phys
*	phys(1)	ksi
*	phys(2)	log(epsilon)
*	phys(3)	delta (density parameter)
      VECTOR PHYS(3)
* Landau parameter Lambda
      REAL LF
      DOUBLE PRECISION CONV,XF,XR,XW,XS,EULER,PI,LF0
      DATA EULER,PI /0.577215664901532861D0,3.141592589793238D0/
      CONV = 0.0D0
*	constant term in Landau parameter Lambda. Lambda is now
*	Delta (energyloss [MeV])/ksi [MeV] - LF0
      LF0=DLOG(PHYS(1)*1.0D0)-PHYS(2)+1.0D0-EULER-PHYS(3) 
*	convert to MeV
      X1=X*PAR(1)
      GW=PAR(3)*PAR(1)
*
*
* XS is temp storage for convolution sum
      XS = 0.0D0
* loop over region around X
      DO I=-40,40
         IF (PAR(1).EQ.0) THEN
            PRINT *,'ERROR: CALIBRATION CANNOT BE ZERO'
            CONVLAN=-1.0D0
	    RETURN
         ENDIF
* step through the gaussian in 0.1 sigma steps
* use the standard gaussian (mean = 0; sigma=1)
         XG = I/10.D0
* XW (weight) is value of standard gaussian at XG
         XW = (1.D0/DSQRT(2.0D0*PI))*DEXP(-0.5D0*XG*XG)
* go from standard gauss to actual (in the MeV scale)
* XF is "loop-point" around X (remember GW is the width o
* the Gauss in MeV units), X in MeV units is X1
         XF = GW*XG+X1
* LF is lambda (of landau dist.) at XF
         LF=(XF/PHYS(1))-LF0
* XR is value of landau at LF
         XR = DENLAN(LF)
* convolution
         XS = XS + XR*XW
      ENDDO
      CONV = XS*PAR(2)
      CONVLAN = CONV+PAR(4)
      RETURN
      END
