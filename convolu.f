      SUBROUTINE CONVOLU(N,W)
      INTEGER N
      REAL W
      VECTOR FX
      VECTOR GX
      INTEGER I,J,K,L
      REAL LF,XF,XR,XW,XS
      DO I=1,N
c XS is temp storage for "convolution" sum
      XS = 0.0
      L=4.*W
c loop over region around X
      DO J=-L,L
        XG = J
c XW (weigth) is value of gaussian at XG
        XW = 1./sqrt(6.283)*exp(-0.5*(XG/W)**2)/w
c convolution
        K=I-J
	IF(K.LT.1) K=J-I
	IF(K.EQ.0) K=1
        IF(K.GT.N) K=N
        XS = XS + FX(K)*XW
      ENDDO
      GX(I)=XS
      ENDDO
      RETURN
      END
